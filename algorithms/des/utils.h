#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QDateTime>
#include <QTime>
#include <QList>


#define GET_BIN_CODE(x) (x == 1 ? "1" : "0")
class Utils
{
private:
    Utils();

public:
    static QString getBinString(QList<ushort>);
    static QString getBinString(QString);
    static QString getBinString(QList<QByteArray>);
    static QString getOtcString(QString);
    static QString getHexString(QString);
    static QString getHexString(QList<QByteArray>);
    static QString fromUtf8(QList<ushort>);
    static QList<ushort> byteToUshort(QList<QByteArray>);
    static QList<ushort> byteToUshort(QByteArray);
    static QList<QByteArray> getWords(QList<QByteArray>);
    /** time **/
    static QString getCurrentStringTime();
    static QByteArray getBytes(QString);

};

#endif // UTILS_H
