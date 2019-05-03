#ifndef SDES_H
#define SDES_H

#include <QFile>
#include <QIODevice>
#include <QList>
#include <QByteArray>

#include "utils.h"

struct _SDesS{
    /** file flag **/

    // sdes file flag {0x97, 0x53, 0x44, 0x45, 0x53}

    QByteArray *qflag; // 4 bytes


    /** the orginal file name **/
    int nameLen; // the name length 2 bytes
    QByteArray *name;

    /** the file created time **/
    int timeLen;  // the time length 2 bytes
    QByteArray *time; //

    /** the orginal file hash **/
    int m; // the hash method  1 byte  0: md5, others: reserved
    int hashLen; // the hash bytes  4 bytes
    QByteArray *hash;

    uchar len; // 0 - 7
    /** encrypted data list **/
    QList<QByteArray> encrypted;
};

typedef  struct _SDesS SDesS;
class SDes
{
public:
    SDes();

    static bool isSDes(QString);
    static QByteArray createSDesFileHead(QString, QString, int);
    static SDesS* unpackSDesFile(uchar *&);
};

#endif // SDES_H
