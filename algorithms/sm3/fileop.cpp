#include "fileop.h"

FileOp::FileOp(QObject *parent)
{

}

FileOp::FileOp(QString path){
    this->path = path;
}

/**
 * start thread
 * @brief FileOp::start
 */
void FileOp::opStart(){
    start();
}
void FileOp::run(){
    QFile file(this->path);
    if(!file.open(QIODevice::ReadOnly)){
        emit onFinish(0, "Error: IO error!");
        return;
    }
    emit onStart("s", file.size());

    clock_t f0 = std::clock();
    /*
    for (int i = 0; i < file.size() / 64; i++) {
        file.seek(i * 64);
        char *buf = new char[64];

        if(file.read(buf, 64) != 0){
            qDebug()<< buf[0];
        }
        emit onProcess(i * 64);

    }
    */
    qint64 fileSize = file.size();
    const qint64 bufferSize = 64;
    char buffer[bufferSize];
    qint64 bytesRead;
    int i = 0;
    qint64 readSize = qMin(fileSize, bufferSize);
    SM3 *sm3 = new SM3();
    while (readSize > 0 & (bytesRead = file.read(buffer, bufferSize)) > 0) {
        fileSize -= bytesRead;
        emit onProcess(bufferSize * i);
        QByteArray bytes(buffer, int(bytesRead));
        sm3->addData(bytes);
        i++;
        readSize = qMin(fileSize, bufferSize);
    }
    clock_t f1 = clock();
    qDebug("s2: %lu", (f1 -  f0));
    emit onFinish(file.size(), QString(sm3->toByte()));
    delete sm3;
}
