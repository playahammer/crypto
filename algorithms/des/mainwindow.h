/***
 *
 *  Copyright (c) 2019 Play a hammer && magbone
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:

 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.

 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 */


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>


#include "des.h"
#include "utils.h"
#include "log.h"
#include "fileop.h"

enum format{
  BIN,
  OTC,
  HEX,
  UTF8
};

enum op{
    ENCRYPT,
    DECRYPT
};

enum speed{
    NORMAL,
    FAST,
    FASTEST
};

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
    /** string **/
    void clearOnClick();
    void decryptOnClick();
    void encryptOnClick();

    void plaintextCurrentChanged(int index);
    void plaintext1CurrentChanged(int index);

    void plaintextChanged();
    void privateKeyChanged();

    void stringKeyGenerator();
    /** file **/
    void logSaveOnClick();
    void selectInFileOnClick();
    void selectOutFileOnClick();

    void opCurrentChanged(int index);
    void opSpeedCurrentChanged(int index);

    void opStartOnClick();
    void opPauseOnClick();

    void fileEncryptStart(QString, QString, qint64);
    void fileDecryptStart(QString, QString, QString, qint64);
    void fileOnProcess(int);
    void fileOpError(QString);
    void fileFinished();

    void fileKeyGenerator();
    void fileKeyResidue(QString);


protected:
    void updateLog();

private:
    Ui::MainWindow *ui;

    Des *des;
    QList<QByteArray> encrypted;
    QList<QByteArray> afterDecrypted;

    //format flag

    enum format plainTextFlag = BIN;
    enum format plainText1Flag = BIN;

    /** file **/
    //op and speed flag
    enum op op = ENCRYPT;
    enum speed sp = NORMAL;

    //log
    QString logs;

    //op values
    QString inputFilePath;
    QString outputFilePath;


    FileOp *fp;
    qint64 size;


    QString randomKeyGenerator();

    // orginal file md5
    QString md5;
};

#endif // MAINWINDOW_H
