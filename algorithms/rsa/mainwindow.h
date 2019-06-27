#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>
#include <QString>

#include "rsa.h"
#include "../sm3/fileop.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void randomGenerateClick();
    void encryptClick();
    void decryptClick();
    void fileSelectClick();

    void fileStart(QString, qint64);
    void fileProcess(qint64);
    void fileFinished(qint64, QString);

    void makeSignature();
private:
    Ui::MainWindow *ui;

    QString path;
    std::string byteToString(QByteArray);
    QByteArray stringToByte(std::string);

    BigInt hexToBigInt(QString);
};

#endif // MAINWINDOW_H
