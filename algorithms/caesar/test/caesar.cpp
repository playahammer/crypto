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
           u_int8_t code = (int(byte.at(i)) + key.toInt()) % 128;
           this->encryptedWords->append(ascii[GET_INDEX(code)]);
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
            int code = GET_MOD(int(byte.at(i)), key.toInt());
            this->decryptedWords->append(ascii[GET_INDEX(code)]);
        }

    }
    return *(this->decryptedWords);
}
