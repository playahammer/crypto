#ifndef FILEOP_H
#define FILEOP_H

#include <QObject>
#include <QString>
#include <QThread>
#include <QFile>
#include <QIODevice>
#include <QDateTime>
#include <QDebug>

#include "sm3.h"

class FileOp : public QThread
{
    Q_OBJECT
public:
    explicit FileOp(QObject *parent = nullptr);
    FileOp(QString path);
    void opStart();
signals:
    void onStart(QString, qint64);
    void onProcess(qint64);
    void onFinish(qint64, QString);
public slots:

protected:
    virtual void run();


private:
    QString path;
};

#endif // FILEOP_H
