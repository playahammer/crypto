#ifndef FILEOP_H
#define FILEOP_H

#include <QString>
#include <QPlainTextEdit>
#include <QProgressBar>
#include <QIODevice>
#include <QFileInfo>
#include <QCryptographicHash>
#include <QMessageBox>
#include <QThread>
#include <QDebug>

#include "des.h"
#include "sdes.h"
#include "log.h"

enum fileop{
  FILE_ENCRYPT,
  FILE_DECRYPT
};

#define GET_BLOCK(x) (x % 8 == 0 ? x / 8 : x / 8 + 1)

class FileOp :public QThread
{

Q_OBJECT

signals :
    void onEncryptStart(QString, QString, qint64);
    void onDecryptStart(QString, QString, QString, qint64);
    void onProcess(int);
    void finished();
    void error(QString err);

public:
    FileOp(QObject *parent);
    ~FileOp();
    void setKey(QString);

    void encryptFile(QString, QString);
    void decryptFile(QString, QString);

    void _encryptFile();
    void _decryptFile();

    static QString fileMd5(QString);
protected:
    virtual void run();

private:
    QString privateKey;
    QString inPath;
    QString outPath;
    enum fileop op;
};

#endif // FILEOP_H
