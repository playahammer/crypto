#ifndef CAESAR_H
#define CAESAR_H

#include <QString>
#include <QDebug>
#include <QByteArray>


#define GET_INDEX(x) (x == 127 ? 0 : x - 32) //split ascii console characters
#define GET_MOD(x, k) (x - k < 0 ?  (x - k + 128) : (x - k))
class Caesar
{
public:
    Caesar(QString);
    ~Caesar();
    QString encrypt(QString);
    QString decrypt(QString);
private:
    Caesar();
    QString key = "";
    QString *encryptedWords;
    QString *decryptedWords;
    const char ascii[128] = {' ','!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/'
                            , '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ':', '<', '=', '>', '?'
                            , '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O'
                            , 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '[', '\\', ']', '^', '_'
                            , '`', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o'
                            , 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}', '~'};
};


#endif // CAESAR_H
