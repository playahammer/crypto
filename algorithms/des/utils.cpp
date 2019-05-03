#include "utils.h"

Utils::Utils()
{

}



QString Utils::getBinString(QList<ushort> q){
     QString s;
     QList<ushort>::const_iterator iter;
     for (iter = q.constBegin(); iter != q.constEnd(); iter++) {
        ushort us = *iter;
        for (int i = 0; i < 16; i++) {
            int c = (us >> (15 - i)) & 1;
            s.append(GET_BIN_CODE(c));
        }
     }
     return s;
}


QString Utils::getBinString(QString s){
    QString sS;
    for (int i = 0; i < s.length(); i++) {
        ushort unicode = s.at(i).unicode();
        for (int i = 0; i < 16; i++) {
            int c = (unicode >> (15 - i)) & 1;
            sS.append(GET_BIN_CODE(c));
        }
    }
    return sS;
}

QString Utils::getBinString(QList<QByteArray> qq){
    QString s;
    QList<QByteArray>::const_iterator iter;
    for (iter = qq.constBegin(); iter != qq.constEnd(); iter++) {
        QByteArray arr = *iter;
        for (int i = 0; i < arr.size(); i++) {
            s.append(GET_BIN_CODE(arr.at(i)));
        }
    }
    return s;
}
QString Utils::getOtcString(QString s){
    return s;
}

QString Utils::getHexString(QString s){
    QString sS;
    QStringList l = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F"};
    for (int i = 0; i < s.length(); i++) {
        ushort unicode = s.at(i).unicode();
        for (int i = 0; i < 4; i++) {
            int s = (unicode >> (12 -  i * 4)) & 0x0f;
            sS.append(l[s]);
        }
    }
    return sS;
}

QString Utils::getHexString(QList<QByteArray> qq){
    QList<QByteArray>::const_iterator iter;
    QString s;
    QStringList l = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F"};
    for (iter = qq.constBegin(); iter != qq.constEnd(); iter++) {
        QByteArray qb = *iter;
        for (int i = 0; i < 16; i++) {
            ushort u = 0;
            for (int j = 0; j < 4; j++) {
                u += (qb.at(i * 4 + j) << (3 - j));
            }
            u = u & 0x0f;
            s.append(l[u]);
        }
    }
    return s;
}
QList<ushort> Utils::byteToUshort(QList<QByteArray> qb){
    QList<ushort> qu;
    QList<QByteArray>::const_iterator iter;

    for (iter = qb.constBegin(); iter != qb.constEnd(); iter++) {
        QByteArray b = *iter;

        for (int i = 0; i < 4; i++) {
            ushort u = 0;
            for (int j = 0; j < 16; j++) {
                   u += (b[i * 16 + j] << (15 - j));
            }
            if(u == 0) continue;
             qu.append(u);
        }

    }
    return qu;
}

QList<ushort> Utils::byteToUshort(QByteArray q){
    QList<ushort> qu;
    for (int i = 0; i < q.size(); i += 2) {
        ushort s1 = static_cast<ushort>(q[i] << 8);
        uchar s2 = static_cast<uchar>(q[i + 1]);
        qu.append(s1 + s2);
    }
    return qu;
}
QString Utils::fromUtf8(QList<ushort> qu){
    QString s;
    QList<ushort>::const_iterator iter;
    for (iter = qu.constBegin(); iter != qu.constEnd(); iter++) {
        ushort codes[1] = {*iter};
        s.append(QString().setUtf16(codes, 1));
    }
    return s;
}



QString Utils::getCurrentStringTime(){
    QDateTime time(QDateTime::currentDateTime());
    QString s = QTime(QTime::currentTime()).toString("hh:mm:ss");
    return s.append(time.date().toString());
}


QByteArray Utils::getBytes(QString s){
    QByteArray qb;
    for(int i = 0; i < s.length(); i++){
        ushort unicode = s.at(i).unicode();
        qb.append(static_cast<char>((unicode >> 8) & 0xff));
        qb.append(static_cast<char>(unicode & 0xff));
    }
    return qb;
}

QList<QByteArray> Utils::getWords(QList<QByteArray> lu){
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
