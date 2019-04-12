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

#include "caesar.h"

Caesar::Caesar(QString key)
{
    this->key = key;
}

Caesar::~Caesar(){
    delete this->encryptedWords;
    delete this->decryptedWords;
}
/**
 * encrypt the message
 * @brief Caesar::encrypt
 * @param s
 * @return
 */

QString Caesar::encrypt(QString s)
{
    this->encryptedWords = new QString();
    if(this->key.length() != 0){
        QByteArray byte = s.toLatin1();
        for(int i = 0; i < byte.length(); i++){
           u_int8_t code = (int(byte.at(i)) + key.toInt() - 32) % 95;
           this->encryptedWords->append(ascii[code]);
        }
    }
    return *(this->encryptedWords);
}

/**
 * decrypt the message
 * @brief Caesar::decrypt
 * @param s
 * @return
 */

QString Caesar::decrypt(QString s)
{
    this->decryptedWords = new QString();
    if(this->key.length() != 0){
        QByteArray byte = s.toLatin1();
        for (int i = 0; i < byte.length(); i++) {
            int code = GET_MOD(int(byte.at(i)), this->key.toInt());
            this->decryptedWords->append(ascii[code]);
        }

    }
    qDebug()<<this->decryptedWords;
    return *(this->decryptedWords);
}
