#include "fileop.h"


FileOp::FileOp(QObject *parnet): QThread (parnet){

}

void FileOp::setKey(QString key){
    this->privateKey = key;
}

FileOp::~FileOp(){

}

void FileOp::encryptFile(QString inputPath, QString outputPath){
    inPath = inputPath;
    outPath = outputPath;
    op = FILE_ENCRYPT;
    start();
}

void FileOp::decryptFile(QString inputPath, QString outputPath){
    inPath = inputPath;
    outPath = outputPath;
    op = FILE_DECRYPT;
    start();
}

void FileOp::run(){
    if (op == FILE_ENCRYPT) _encryptFile();
    else _decryptFile();
}

void FileOp::_encryptFile(){

    QString name = QFileInfo(inPath).fileName();

    QString md5 = fileMd5(inPath);

    QFile in(inPath);
    in.open(QIODevice::ReadOnly);
    qint64 size = in.size();

    emit onEncryptStart(name, md5, size);

    Des *des;
    try {
        des = new Des(this->privateKey);
    } catch (IllegalKeyException e) {
        in.close();
        emit error(e.what());
        return;
    }

    QByteArray outHead = SDes::createSDesFileHead(name, md5, in.size() % 8);

    uchar *uptr = in.map(0, in.size());

    QFile out(outPath);
    out.open(QIODevice::ReadWrite);
    out.resize(outHead.size() + in.size());
    uchar *iptr = out.map(0,  out.size());
    //wirte header
    for (int i = 0; i < out.size(); i++) {
        *iptr++ = static_cast<uchar>(outHead[i]);
    }
    out.unmap(iptr);


    iptr = out.map(outHead.size(), out.size());
    for (int i = 0; i < in.size() / 8; i++) {

        //read
        QList<QByteArray> lq;
        QByteArray qb;
        qb.resize(8);
        for (int j = 0; j < 8; j++) {
            qb[j] = static_cast<char>(*uptr++);
        }
        lq.append(qb);
        QList<QByteArray> en = des->encrypt(lq);

        //write
        QList<QByteArray>::const_iterator iter = en.constBegin();
        for (; iter != en.constEnd(); iter++) {
            QByteArray enB = *iter;
            for (int j = 0; j < enB.size() / 8; j++) {
                char s = 0;
                for (int k = 0; k < 8; k++) {
                    s += (enB[j * 8 + k] << (7 - k));
                }
                *iptr++ = static_cast<uchar>(s) ;
            }
        }
        emit onProcess(8 * i);
    }

    if(in.size() % 8 != 0){
        QByteArray qb;
        qb.resize(64);
        int qbIndex = 0;
        while(qbIndex < in.size() % 8) qb[qbIndex++] = static_cast<char>(*uptr++);
        QList<QByteArray> qq;
        qq.append(qb);
        QList<QByteArray> en = des->encrypt(qq);

        QList<QByteArray>::const_iterator iter;

        for (iter = en.constBegin(); iter != en.constEnd(); iter++) {
            QByteArray enB = *iter;
            for (int j = 0; j < enB.size() / 8; j++) {
                char s = 0;
                for (int k = 0; k < 8; k++) {
                    s += (enB[j *8 + k] << (7 - k));
                }
                *iptr++ = static_cast<uchar>(s) ;
            }
        }
    }
    emit onProcess(int(in.size()));
    in.unmap(uptr);

    out.unmap(iptr);
    in.close();
    out.close();
    emit finished();
}

void FileOp::_decryptFile(){
    if(!SDes::isSDes(inPath)){
        emit error("不是标准的des文件");
    }

    QFile in(inPath);
    in.open(QIODevice::ReadOnly);
    qint64 size = in.size();
    uchar *uptr = in.map(0, in.size());

    SDesS * s = SDes::unpackSDesFile(uptr);

    QString name = Utils::fromUtf8(Utils::byteToUshort(*s->name)); //orginal file name
    QString time = Utils::fromUtf8(Utils::byteToUshort(*s->time)); //orginal created time
    QString hash = QString(*s->hash); //original hash value

    emit onDecryptStart(name, time, hash, size);

    Des *des;
    try {
        des = new Des(this->privateKey);
    } catch (IllegalKeyException e) {
        emit error(e.what());
        in.close();
        return;
    }

    QFile outFile(outPath);
    outFile.open(QIODevice::ReadWrite);

    /** This is ass, fix later. **/
    int headerLen =
            5 /** sdes file header flag **/ +
            s->nameLen * 2  + 2 /** the nameLen bytes and name bytes **/ +
            s->timeLen * 2  + 2 /** the timeLen bytes and time bytes **/ +
            s->hashLen + 1 + 2 /** the hashflag bytes, hashLen bytes and hash bytes **/
            + 1 /** the padding length byte **/;
    qint64 orginalFileSize = in.size() - headerLen ;//- (8 - s->len); //padding length
    emit onProcess(headerLen);
    outFile.resize(orginalFileSize);
    uchar *iptr = outFile.map(0, outFile.size());
    for (int i = 0; i < in.size() / 8; i++) {
        QList<QByteArray> qq;
        QByteArray qb;
        for (int j = 0; j < 8; j++) {
            qb.append(static_cast<char>(*(uptr + i *8 + j)));
        }
        qq.append(qb);

        QList<QByteArray> de = des->decrypt(Utils::getWords(qq));
        QList<QByteArray>::const_iterator iter;

        for (iter = de.constBegin(); iter != de.constEnd() ; iter++) {
            QByteArray enB = *iter;
            int end = (i == in.size() - 1) && (s->len != 0) ? s->len : enB.size() / 8;
            for (int j = 0; j < end; j++) {
                char s = 0;
                for (int k = 0; k < 8; k++) {
                    s += (enB[j *8 + k] << (7 - k));
                }
                *iptr++ = static_cast<uchar>(s) ;
            }
        }
        emit onProcess(8 * i + headerLen);

    }
    emit onProcess(int(in.size()));
    in.unmap(uptr);
    outFile.unmap(iptr);
    outFile.close();
    in.close();
    emit finished();
}

/**
 * @brief FileOp::fileMd5
 * @param path
 * @return
 */
QString FileOp::fileMd5(QString path){
    QFile src(path);
    qint64 fileSize = src.size();
    const qint64 bufferSize = 10240;

    if(src.open(QIODevice::ReadOnly)){
        char buffer[bufferSize];
        qint64 bytesRead;
        long long readSize = qMin(fileSize, bufferSize);

        QCryptographicHash hash(QCryptographicHash::Md5);

        while (readSize > 0 && (bytesRead = src.read(buffer, readSize)) > 0) {
            fileSize -= bytesRead;
            hash.addData(buffer, int(bytesRead));
            readSize = qMin(fileSize, bufferSize);
        }

        src.close();
        return QString(hash.result().toHex());
    }
    return QString();
}


