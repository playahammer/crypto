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

#include "des.h"

Des::Des(QString key){
    this->key = keyToChecksum(key);
    this->expandedKey = keyGenerate();
    this->sBoxes.append(QByteArray(s1, 64));
    this->sBoxes.append(QByteArray(s2, 64));
    this->sBoxes.append(QByteArray(s3, 64));
    this->sBoxes.append(QByteArray(s4, 64));
    this->sBoxes.append(QByteArray(s5, 64));
    this->sBoxes.append(QByteArray(s6, 64));
    this->sBoxes.append(QByteArray(s7, 64));
    this->sBoxes.append(QByteArray(s8, 64));

}

/**
 * encrypt the message.
 * @param s the plaintext
 * @brief Des::decrypt
 * @return after decypted message
 */

QList<QByteArray> Des::decrypt(QString s){
    QList<ushort> pl = getUShorts(s);
    QList<QByteArray> lc = getWords(pl);
    QList<QByteArray> ec;

    QList<QByteArray> keyRe;
    QList<QByteArray>::const_reverse_iterator keyIter;
    for (keyIter = this->expandedKey.rbegin(); keyIter != this->expandedKey.rend(); keyIter++)
        keyRe.append(*keyIter);
    this->expandedKey = keyRe;
    QList<QByteArray>::const_iterator iter;

    for (iter = lc.constBegin(); iter != lc.constEnd(); iter++) {
        QByteArray arr = *iter;
        arr = ciperToNIP(arr);
        arr = ciperLFuncs(arr);
        arr = ciperToIP(arr);
        ec.append(arr);
    }
    return ec;
}

QList<QByteArray> Des::decrypt(QList<QByteArray> qb){
    QList<QByteArray> ec;

    QList<QByteArray> keyRe;
    QList<QByteArray>::const_reverse_iterator keyIter;
    for (keyIter = this->expandedKey.rbegin(); keyIter != this->expandedKey.rend(); keyIter++)
        keyRe.append(*keyIter);
    this->expandedKey = keyRe;
    QList<QByteArray>::const_iterator iter;

    for (iter = qb.constBegin(); iter != qb.constEnd(); iter++) {
        QByteArray arr = *iter;
        arr = ciperToNIP(arr);
        arr = ciperLFuncs(arr);
        arr = ciperToIP(arr);
        ec.append(arr);
    }
    return ec;
}
/**
 * decrypt the message
 * @brief Des::encrypt
 * @param s the cipertext
 * @return after encypted message
 */
QList<QByteArray> Des::encrypt(QString s){
    QList<ushort> pl = getUShorts(s);
    QList<QByteArray> lc = getWords(pl);
    QList<QByteArray> ec;

    QList<QByteArray>::const_iterator iter;
    for (iter = lc.constBegin(); iter != lc.constEnd(); ++iter) {
        QByteArray arr = *iter;
        arr = wordsToIP(arr);
        arr = wordsLFuncs(arr);
        arr = wordsToNIP(arr);
        ec.append(arr);
    }
    return ec;
}

/**
 * @brief Des::encrypt.
 * @param qb
 * @return
 */
QList<QByteArray> Des::encrypt(QList<QByteArray> qb){
    QList<QByteArray> lc = getWords(qb);
    QList<QByteArray> ec;

    QList<QByteArray>::const_iterator iter;
    for (iter = lc.constBegin(); iter != lc.constEnd(); ++iter) {
        QByteArray arr = *iter;
        arr = wordsToIP(arr);
        arr = wordsLFuncs(arr);
        arr = wordsToNIP(arr);
        ec.append(arr);
    }
    return ec;
}

QList<ushort> Des::getUShorts(QString s){
    int lUShortsSize = s.length() % 4 == 0 ? s.length() : (s.length() / 4 + 1) * 4;
    QList<ushort> lUShorts;
    for(int i = 0; i < lUShortsSize; i++){
        if(i < s.length())
        lUShorts.append(s.at(i).unicode());
        else lUShorts.append(0x0000);
    }
    return lUShorts;
}

/**
 * unicode to bins.
 * @brief Des::getWords
 * @param lu
 * @return
 */
QList<QByteArray> Des::getWords(QList<ushort> lu){
    QList<QByteArray> qb;
    QList<ushort>::iterator iter = lu.begin();
    for(int i = 0; i < lu.size() / 4; i++){
        QByteArray arr;
        for(int j = 0; j < 4; j++){
            ushort us = *iter;
            for(int k = 0; k < 16; k++)
                arr.append((us >> (15 - k)) & 1);
            iter++;
        }
        qb.append(arr);
    }
    return qb;
}

/**
 * byte to bins
 * @brief Des::getWords
 * @param lu
 * @return
 */
QList<QByteArray> Des::getWords(QList<QByteArray> lu){
    QList<QByteArray> qb;
    QList<QByteArray>::const_iterator iter = lu.constBegin();
    for (; iter != lu.constEnd(); iter++) {
        QByteArray b = *iter;
        QByteArray q;
        for (int i = 0; i < b.size(); i++) {
            for (int j = 0; j < 8; j++) {
                q.append((b[i] >> (7 -j) & 1));
            }
        }
        qb.append(q);
    }
    return qb;
}

/**
 * calculate the key's checksum.
 * @brief Des::keyToChecksum
 * @param s
 * @return
 */
QByteArray Des::keyToChecksum(QString s){
    QByteArray key;
    key.resize(64);
    QByteArray kb = s.toLatin1();
    if(kb.length() != 56) throw IllegalKeyException(s, "the bits of key is not suitable");
    for(int i = 0; i < 7; i++){
        unsigned char checksum = 1;
        int j;
        for(j = 0; j < 7; j++){
            unsigned char it = static_cast<unsigned char>(kb.at(8 * i + j));
            if(int(it) !=  48 && int(it) != 49) throw IllegalKeyException(s, "is not binary");
            key.append(char(it));
            checksum ^= it;
        }
        checksum ^= 1;
        key.append(char(checksum));

    }
    return key;
}

/**
 * key to PC1.
 * @brief Des::keyToPC1
 * @param cs
 * @return
 */
QByteArray Des::keyToPC1(QByteArray cs){
    QByteArray pc1Key;
    pc1Key.resize(56);
    if(!cs.size()) return pc1Key;

    int PC_1[56] = {
        56, 48, 40, 32, 24, 16, 8, 0, 57, 49, 41, 33, 25, 17, 9, 1,
        58, 50, 42, 34, 26, 18, 10, 2, 59, 51, 43, 35, 62, 54, 46, 38,
        30, 22, 14, 6, 61, 53, 45, 37, 29, 21, 13, 5, 60, 52, 44, 36,
        28, 20, 12, 4, 27, 19, 11, 3};
    for (int i = 0; i < 56; i++)
        cs.append(cs[PC_1[i]]);
    return pc1Key;
}

/**
 * key shift.
 * @brief Des::keyToShift
 * @param cl
 * @param dl
 * @param l
 * @return
 */
QByteArray Des::keyToShift(QByteArray cl, QByteArray dl, int l){
    QByteArray shitfedKey;

    //shift the key
    if(l == 1 || l == 2 || l == 9 || l == 16){
        char firstCl = cl.at(0);
        char firstDl = dl.at(0);

        for (int i = 0; i < 26; i++) {
            cl[i] = cl[i + 1];
            dl[i] = dl[i + 1];
        }
        cl[27] = firstCl;
        dl[27] = firstDl;
    }else {
        char firstC0Arr[2] = {cl[0], cl[1]};
        char firstD0Arr[2] = {dl[0], dl[1]};

        for (int i = 0; i < 25; i+=2) {
            cl[i] = cl[l + 2];
            cl[i + 1] = cl[l + 3];

            dl[i] = dl[i + 2];
            dl[i + 1] = dl[i + 3];
        }

        cl[26] = firstC0Arr[0];
        cl[27] = firstC0Arr[1];
        dl[26] = firstD0Arr[0];
        dl[27] = firstD0Arr[1];
    }

    //combine cl and dl
    for(int i = 0; i < 56; i++){
        if(i < 28)
            shitfedKey[i] = cl[i];
        else
            shitfedKey[i] = cl[i - 28];

    }
    return shitfedKey;
}

/**
 * key to PC2.
 * @brief Des::keyToPC2
 * @param s
 * @return
 */
QByteArray Des::keyToPC2(QByteArray s){
    QByteArray pc2Key;
    int PC_2[48] = {
        13, 16, 10, 23, 0, 4, 2, 27, 14, 5, 20, 9, 22, 18, 11, 3,
        25, 7, 15, 6, 26, 19, 12, 1, 40, 51, 30, 36, 46, 54, 29, 39,
        50, 44, 32, 47, 43, 48, 38, 55, 33, 52, 45, 41, 49, 35, 28, 31
    };

    for (int i = 0; i < 48; i++)
        pc2Key.append(s[PC_2[i]]);

    return pc2Key;
}

/**
 * genterate key.
 * @brief Des::keyGenerate
 * @return
 */

QList<QByteArray> Des::keyGenerate(){
    QList<QByteArray> lc;
    QByteArray keyPC1 = keyToPC1(this->key);
    QByteArray l, r;
    wordSplit2(keyPC1, l, r, 28);
    for(int i = 0; i < 16; i++){
        QByteArray keySifted = keyToShift(l, r, i + 1);
        QByteArray keyPC2 = keyToPC2(keySifted);
        lc.append(keyPC2);
    }
    return lc;
}

/**
 * words to IP.
 * @brief Des::wordsToIP
 * @param s
 * @return
 */
QByteArray Des::wordsToIP(QByteArray s){
    QByteArray IPWords;
    IPWords.resize(64);
    for (int i = 0; i < 64; i++)
        IPWords[i] = s[IP[i]];
    return IPWords;
}

/**
 * words to expand.
 * @brief Des::wordsExpand
 * @param s
 * @return
 */
QByteArray Des::wordsExpand(QByteArray s){
    QByteArray expandedWords;

    int E[48] = {
        31, 0, 1, 2, 3, 4,
        3, 4, 5, 6, 7, 8,
        7, 8, 9, 10, 11, 12,
        11, 12, 13, 14, 15, 16,
        15, 16, 17, 18, 19, 20,
        19, 20, 21, 22, 23, 24,
        23, 25, 26, 27, 28, 29,
        27, 28, 29, 30, 31, 1
    };
    for (int i = 0; i < 48; i++)
        expandedWords.append(s[E[i]]);
    return expandedWords;
}

QByteArray Des::wordsKeyExc(QByteArray s, QByteArray key){
    QByteArray keyf;
    keyf.resize(48);
    for (int i = 0; i < 48; i++)
        keyf[i] = s[i] ^ key[i];

    return keyf;
}

/**
 * s box.
 * @brief Des::wordsSBox
 * @param s
 * @return
 */
QByteArray Des::wordsSBox(QByteArray s){
    QByteArray sS;
    sS.resize(32);
    QList<QByteArray>::const_iterator iter;
    iter = this->sBoxes.constBegin();
    for(int i = 0; i < 8; i++, iter++){
        int row = (BIN_INT(s[i * 6 + 0]) << 1) + BIN_INT(s[i * 6 + 5]);
        int col = (BIN_INT(s[i * 6 + 1]) << 3) + (BIN_INT(s[i * 6 + 2]) << 2) + (BIN_INT(s[i * 6 + 3]) << 1)  + BIN_INT(s[i * 6 + 4]);
        QByteArray sBox = *iter;
        int value = sBox[row * 16 + col];
        /** value to bin **/
        for (int j = 0; j < 4; j++)
            sS[i * 4 + j] = (value >> (3 - j)) & 1;

    }
    return sS;
}

/**
 *  p box.
 * @brief Des::wordsPBox
 * @param s
 * @return
 */
QByteArray Des::wordsPBox(QByteArray s){
    QByteArray pS;
    int P[32] = {
        15, 6, 19, 20, 28, 11, 27, 16, 0, 14, 22, 25, 4, 17, 30, 9,
        1, 7, 23, 13, 31, 26, 2, 8, 18, 12, 29, 5, 21, 10, 3, 24
    };
    for(int i = 0; i < 32; i++)
        pS.append(s[P[i]]);
    return pS;
}

/**
 * L function.
 * @brief Des::wordsLFuncs
 * @param s
 * @return
 */
QByteArray Des::wordsLFuncs(QByteArray s){
    QByteArray f;
    QByteArray left, right;
    wordSplit2(s, left, right, 32);
    QList<QByteArray>::const_iterator iter;
    iter = expandedKey.constBegin();
    // 16 times
    for(int i = 0; i < 16; i++){
        QByteArray temp1;
        temp1 = wordsExpand(right); // expand transform
        temp1 = wordsKeyExc(temp1, *iter); // xor with key
        temp1 = wordsSBox(temp1); // s box
        temp1 = wordsPBox(temp1); // p box
        for (int i = 0; i < 32;i++) {
           temp1[i] = temp1[i] ^ left[i]; // xor
        }
        temp1 = right;
        right = left;
        left = temp1;
    }

    f = wordCombine2(right, left, 32);
    return f;
}

/**
 * word to nip
 * @brief Des::wordsToNIP
 * @param s
 * @return
 */
QByteArray Des::wordsToNIP(QByteArray s){
    QByteArray nb;
    for(int i = 0; i < 64; i++)
        nb.append(s[NIP[i]]);
    return nb;
}

/**
 * ciper to nip
 * @brief Des::ciperToNIP
 * @param q
 * @return
 */
QByteArray Des::ciperToNIP(QByteArray q){
    QByteArray nip;
    nip.resize(64);
    for (int i = 0; i < 64; i++) {
        nip[NIP[i]] = q[i];
    }
    return nip;
}

/**
 * @brief Des::ciperLFuncs
 * @param q
 * @return
 */
QByteArray Des::ciperLFuncs(QByteArray q){
    QByteArray lf;

    QByteArray left, right;
    wordSplit2(q, right, left, 32);
    QList<QByteArray>::const_iterator iter;
    iter = expandedKey.constBegin();
    for(int i = 0; i < 16; i++){
        QByteArray temp1;
        temp1 = wordsExpand(right);
        temp1 = wordsKeyExc(temp1, *iter);
        temp1 = wordsSBox(temp1);
        temp1 = wordsPBox(temp1);
        for (int i = 0; i < 32;i++) {
           temp1[i] = temp1[i] ^ left[i];
        }
        temp1 = right;
        right = left;
        left = temp1;
    }
    lf = wordCombine2(left, right, 32);
    return lf;
}

/**
 * ciper to ip
 * @brief Des::ciperToIP
 * @param q
 * @return
 */
QByteArray Des::ciperToIP(QByteArray q){
    QByteArray ip;
    ip.resize(64);
    for (int i = 0; i < 64; i++) {
        ip[IP[i]] = q[i];
    }
    return ip;
}
/**
 * split an array to two arrs
 * @brief Des::wordSplit2
 * @param src
 * @param l
 * @param r
 * @param size
 */
void Des::wordSplit2(QByteArray src, QByteArray &l, QByteArray &r, int size){
    if(!src.size()) return;
    for(int i = 0; i < size * 2; i++){
        if(i < size) l.append(src[i]);
        else  r.append(src[i]);
    }
}


/**
 * combine two arrs
 * @brief Des::wordCombine2
 * @param l
 * @param r
 * @param size
 * @return
 */
QByteArray Des::wordCombine2(QByteArray l, QByteArray r, int size){
    QByteArray cob;
    cob.resize(size * 2);
    for (int i = 0; i < 2 * size; i++) {
        if(i < size) cob[i] = l[i];
        else cob[i] = r[i - size];
    }
    return cob;
}


