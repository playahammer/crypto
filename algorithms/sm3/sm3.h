#ifndef SM3_H
#define SM3_H


#include <QByteArray>
#include <QString>
#include <QList>
#include <QDebug>

#define GET_T(i) ((i <= 15) ? 0x79cc4519 : 0x7a879d8a)
#define CLS(s, p) ((s << p) | (s >> (32 - p)))
#define P0(x) (x ^ (CLS(x, 9)) ^ (CLS(x, 17)))
#define P1(x) (x ^ (CLS(x , 15)) ^ (CLS(x, 23)))
#define FF(x, y, z, i) ((i <= 15) ? (x ^ y ^ z) : ((x & y) | (x & z) | (y & z)))
#define GG(x, y, z, i) ((i <= 15) ? (x ^ y ^ z) : ((x & y) | (~x & z)))


class SM3
{
public:
    SM3(QString);
    SM3();
    QByteArray toByte();
    void addData(QByteArray);

protected:
    QList<QByteArray> padding(QByteArray);
    u_int32_t* compress(u_int32_t *, u_int32_t *);
    u_int32_t* messageExpand(u_int32_t *);
private:
    u_int64_t len = 0;
    u_int32_t *IV;

    QByteArray qb;


    u_int32_t* bytesToWords(QByteArray);

    char * _64toa(u_int64_t);
    u_int32_t mod32bits(u_int32_t, u_int32_t);
    bool isEnd = false;
};

#endif // SM3_H
