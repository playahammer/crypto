#include "sdes.h"

SDes::SDes()
{

}


bool SDes::isSDes(QString path){
    const uchar flags[5] = {0x97, 0x53, 0x44, 0x45, 0x53};
    if(!path.size()) return false;
    QFile file(path);
    file.open(QIODevice::ReadOnly);

    if(file.size() < 5) return false;
    uchar *ptr = file.map(0, file.size());
    bool flag = true;
    for(int i = 0; i < 5; i++){
        if(ptr[i] != flags[i]) {
            flag = false;
            break;
        }
    }
    file.unmap(ptr);
    file.close();
    return flag;
}

QByteArray SDes::createSDesFileHead(QString name, QString hash, int len){
    const uchar flags[5] = {0x97, 0x53, 0x44, 0x45, 0x53};
    QByteArray head;
    for (int i = 0; i < 5; i++) {
        head.append(static_cast<char>(flags[i]));
    }

    //name
    int nameLen = name.length();
    head.append(static_cast<char>((nameLen >> 8) & 0xff));
    head.append(static_cast<char>(nameLen & 0xff));
    QByteArray nameByte = Utils::getBytes(name);
    head.append(nameByte);

    //time
    QString createTime = Utils::getCurrentStringTime();
    QByteArray timeBytes = Utils::getBytes(createTime);
    int timeLen = createTime.length();
    head.append(static_cast<char>((timeLen >> 8) & 0xff));
    head.append(static_cast<char>(timeLen & 0xff));
    head.append(timeBytes);

    //hash
    int hashLen = hash.length();
    head.append(static_cast<char>(1));
    head.append(static_cast<char>((hashLen >> 8) & 0xff));
    head.append(static_cast<char>(hashLen & 0xff));
    QByteArray hashBytes = hash.toLatin1();
    head.append(hashBytes);

    //len
    head.append(static_cast<char>(len));
    return head;
}

SDesS* SDes::unpackSDesFile(uchar *&chars){
    SDesS *s = new SDesS;

    s->qflag = new QByteArray;
    for (int i = 0; i < 5; i++) {
        s->qflag->append(static_cast<char>(*chars++));
    }


    //name
    int nameLen = (*(chars) << 8) +  *(chars + 1);

    chars += 2;
    s->name = new QByteArray;
    for (int i = 0; i < nameLen * 2; i++) {
        s->name->append(static_cast<char>(*(chars + i)));
    }
    chars += nameLen * 2;
    s->nameLen = nameLen;


    //time
    int timeLen = (*(chars) << 8) + *(chars + 1);
    chars += 2;
    s->time = new QByteArray;
    for (int i = 0; i < timeLen * 2; i++) {
        s->time->append(static_cast<char>(*(chars + i)));
    }
    chars += timeLen * 2;

    s->timeLen = timeLen;



    //hash
    int hashType = *chars++;
    int hashLen = (*(chars) << 8) + *(chars + 1);
    chars += 2;
    s->hash = new QByteArray;
    for (int i = 0; i < hashLen ; i++) {
        s->hash->append(static_cast<char>(*(chars + i)));
    }
    chars += hashLen;

    s->m = hashType;
    s->hashLen = hashLen;

    s->len = *chars++;
    return s;
}
