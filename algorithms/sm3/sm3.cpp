/***
 *
 *  Copyright (c) 2019 Play a hammer && magbone
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:

 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.

 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 */

#include "sm3.h"

SM3::SM3(QString s){
    this->qb = s.toUtf8();
}

SM3::SM3(){
    IV = new u_int32_t[8];
    //init IV0
    IV[0] = 0x7380166f;
    IV[1] = 0x4914b2b9;
    IV[2] = 0x172442d7;
    IV[3] = 0xda8a0600;
    IV[4] = 0xa96f30bc;
    IV[5] = 0x163138aa;
    IV[6] = 0xe38dee4d;
    IV[7] = 0xb0fb0e4e;

}

QByteArray SM3::toByte(){
    // valid end
    if(!this->isEnd){ //padding
        QByteArray qb;
        qb.append(static_cast<char>(0x80));
        for (int i = qb.size(); i < 64; i++) {
            qb.append(static_cast<char>(0x00));
        }
        char *lenS = _64toa(len);
        for (int i = 0; i < 8; i++) {
            qb[63 - i] = lenS[i];
        }
        u_int32_t * words = bytesToWords(qb);
        /* debug
        for (int i = 0; i < 16; i++) {
            qDebug("%x", words[i]);
        }*/
        this->IV = compress(this->IV, words);
    }
    QByteArray qb;
    for (int i = 0; i < 8; i++) {
        qb.append(static_cast<char>((this->IV[i] >> 24) & 0xff));
        qb.append(static_cast<char>((this->IV[i] >> 16) & 0xff));
        qb.append(static_cast<char>((this->IV[i] >> 8) & 0xff));
        qb.append(static_cast<char>(this->IV[i] & 0xff));
    }
    return qb.toHex();
}


QList<QByteArray> SM3::padding(QByteArray q){
    QList<QByteArray> s;

    /** the end **/
    if(q.size() + 1 + 8 > 64){ //two blocks
        QByteArray b1 = q; // block 1
        b1.append(static_cast<char>(0x80)); // 0'b10000000
        for (int i = b1.size(); i < 64; i++)
            b1.append(static_cast<char>(0));
        s.append(b1);

        QByteArray b2; // block 2
        b2.resize(64);
        for (int i = 0; i < b2.size(); i++)
            b2[i] = 0x00;
        char *lenS = _64toa(this->len);
        for (int i = 0; i < 8; i++) {
            b2[63 - i] = lenS[i];
        }
        s.append(b2);

    }else if(q.size() + 1 + 8 <= 64){
        QByteArray b = q; // only one block
        b.append(static_cast<char>(0x80)); // 0'b100000000
        for (int i = b.size(); i < 64; i++) {
            b.append(static_cast<char>(0));
        }
        char *lenS = _64toa(len);
        for (int i = 0; i < 8; i++) {
            b[63 - i] = lenS[i];
        }
        s.append(b);

    }

    return s;
}

/**
 * @brief SM3::compress
 * @param v Vn-1
 * @param c value
 * @return
 */
u_int32_t* SM3::compress(u_int32_t *v, u_int32_t* c){
    u_int32_t *s = new u_int32_t[8];
    for (int i = 0; i < 8; i++) {
        s[i] = v[i];
    }
    u_int32_t *msgEx = messageExpand(c);
    for(int i = 0; i < 64; i++){
        //qDebug("s0;%x", CLS(s[0], 12));
        //qDebug("s1:%x", CLS(s[0], 12) + s[4]);
        //qDebug("s1-1:%x", (CLS(s[0], 12) + s[4]) % 0xffffffff);
        //qDebug("s2:%x", CLS((CLS(s[0] ,12)) + s[4] + (CLS(static_cast<u_int32_t>(GET_T(i)), i)), 7));
        u_int32_t ss1 = CLS(mod32bits(mod32bits((CLS(s[0] , 12)), s[4]), (CLS(static_cast<u_int32_t>(GET_T(i)), i))), 7);
        u_int32_t ss2 = ss1 ^ CLS(s[0], 12);
        //qDebug("tt1: %x", (FF(s[0], s[1], s[2], i) + s[3] + ss2 + msgEx[68 + i]));
        u_int32_t tt1 = mod32bits(mod32bits(mod32bits((FF(s[0], s[1], s[2], i)), s[3]), ss2) , msgEx[68 + i]);
        //qDebug("tt2: %x", (GG(s[4], s[5], s[6], i) + s[7] + ss1 + msgEx[i]));
        //u_int64_t tt2s = static_cast<u_int64_t>(0xffffffff) +static_cast<u_int64_t>(0xfff);
        //qDebug("tt2 %x", mod32bits(0xffffffff, 0xfff));
        //qDebug("s1 %x", mod32bits(GG(s[4], s[5], s[6], i), s[7]));
        u_int32_t tt2 = mod32bits(mod32bits(mod32bits((GG(s[4], s[5], s[6], i)), s[7]), ss1), msgEx[i]);
        qDebug("%d: ss1:%x, ss2:%x", i, ss1, ss2);
        //qDebug("tt1:%x, tt2:%x", tt1, tt2);
        s[3] = s[2];
        s[2] = CLS(s[1], 9);
        s[1] = s[0];
        s[0] = tt1;
        s[7] = s[6];
        s[6] = CLS(s[5], 19);
        s[5] = s[4];
        s[4] = P0(tt2);
        //qDebug("s22:%x", static_cast<u_int32_t>(0xe3890283+0xf0384993));
        //qDebug("s11:%x", mod32bits(0xe3890283, 0xf0384993));
        qDebug("%d:%x, %x, %x, %x, %x, %x, %x, %x", i, s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7]);
    }
    for (int i = 0; i < 8; i++) {
        s[i] ^= v[i];
    }
    return s;
}



/**
 * Expand 16 words data to 132 words
 * @brief SM3::messageExpand
 * @param b
 * @return
 */
u_int32_t* SM3::messageExpand(u_int32_t *b){
    u_int32_t * w = new u_int32_t[132];
    for (int i = 0; i < 16; i++) {
        w[i] = b[i];
    }
    for (int i = 16; i < 68; i++) {
        w[i] = P1((w[i - 16] ^ w[i - 9] ^ CLS(w[i - 3], 15))) ^ CLS(w[i - 13], 7) ^ w[i - 6];

    }
    for (int i = 0; i < 64; i++) {
        w[68 + i] = w[i] ^ w[ i + 4];
    }

    return w;
}
/**
 * @public
 * Add data. If data length is lower than 64 bytes, padding it. The data length max length is 64 bytes.
 * @brief SM3::addData
 * @param q
 */
void SM3::addData(QByteArray q){
    len += static_cast<u_int64_t>(q.size());
    if(q.size() < 64){ // padding
        QList<QByteArray> pd = padding(q);
        QList<QByteArray>::const_iterator iter;
        for (iter = pd.constBegin(); iter != pd.constEnd(); iter++) {
            u_int32_t *b = bytesToWords(*iter);
            //debug
            /*
            for (int i = 0; i < 16; i++) {
                u_int32_t s = b[i];
            }*/
            this->IV = compress(this->IV, b);
        }
        isEnd = true;
    }
    else{
        u_int32_t * b = bytesToWords(q);
        this->IV = compress(this->IV, b); // do compressing...

    }
}

/**
 * transform bytes to words
 * @brief SM3::bytesToWords
 * @param q
 * @return
 */
u_int32_t* SM3::bytesToWords(QByteArray q){
    u_int32_t *w = new u_int32_t[16];
    for (int j = 0; j < 16; j++) {
        w[j] = static_cast<u_int32_t>((q[j * 4] << 24)) + static_cast<u_int32_t>((q[j * 4 + 1] << 16)) + static_cast<u_int16_t>((q[j * 4 + 2] << 8)) + static_cast<u_int8_t>(q[j * 4 + 3]);
    }
    return w;
}

/**
 * 64 bits to char array
 * @brief SM3::_64toa
 * @param len
 * @return
 */
char * SM3::_64toa(u_int64_t len){
    char *s = new char[8];
    for(int i = 0; i < 8; i++){
        s[i] = static_cast<char>((len * 8 >> (i * 8)) & 0xff);
    }
    return s;
}

/**
 * mod 32bits add
 * @brief SM3::mod32bits
 * @param l
 * @param r
 * @return
 */
u_int32_t SM3::mod32bits(u_int32_t l, u_int32_t r){
    if((l + r  < l ) || (l + r < r)){
        u_int32_t ls = 0xffffffff - l;
        return r - ls - 1;
    }
    return l + r;
}
