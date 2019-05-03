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


#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("DES");
    /** tab **/
    // string tab
    ui->tabWidget->setTabText(0,"字符串");
    // file tab
    ui->tabWidget->setTabText(1, "文件");

    ui->tabWidget->setCurrentIndex(0);

    /** string **/
    //private key show model
    QStringList items = {"二进制", "八进制", "十六进制"};
    ui->plaintextComboBox->addItems(items);
    ui->plaintextComboBox_1->addItems(items);
    ui->plaintextComboBox_1->addItem("UTF-8");

    connect(ui->clear, SIGNAL(clicked()), this, SLOT(clearOnClick()));
    connect(ui->decrypt, SIGNAL(clicked()),this, SLOT(decryptOnClick()));
    connect(ui->encrypt, SIGNAL(clicked()), this, SLOT(encryptOnClick()));

    ui->plainTextFormatShow->setReadOnly(true);
    ui->ciphertext->setReadOnly(true);
    ui->plaintext_1->setReadOnly(true);

    //key generator
    connect(ui->stringKeyGer, SIGNAL(clicked()), this, SLOT(stringKeyGenerator()));

    //combobox
    connect(ui->plaintextComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(plaintextCurrentChanged(int)));
    connect(ui->plaintextComboBox_1, SIGNAL(currentIndexChanged(int)), this, SLOT(plaintext1CurrentChanged(int)));
    //textformat
    connect(ui->plaintext, SIGNAL(textChanged()), this, SLOT(plaintextChanged()));
    connect(ui->private_key, SIGNAL(textChanged()), this, SLOT(privateKeyChanged()));

    /** file **/
    ui->logs->setReadOnly(true);
    ui->inFileSelectedPath->setReadOnly(true);
    ui->outFileSelectedPath->setReadOnly(true);

    //operation comboBox
    ui->opComboBox->addItem("加密");
    ui->opComboBox->addItem("解密");
    //speed commboBox
    ui->speedComboBox->addItem("一般");
    ui->speedComboBox->addItem("较快");
    ui->speedComboBox->addItem("极快");
    //progressbar
    ui->progressBar->setValue(0);


    //button
    connect(ui->logsSave, SIGNAL(clicked()), this, SLOT(logSaveOnClick()));
    connect(ui->selectInFile, SIGNAL(clicked()), this, SLOT(selectInFileOnClick()));
    connect(ui->selectOutFile, SIGNAL(clicked()), this, SLOT(selectOutFileOnClick()));

    connect(ui->start, SIGNAL(clicked()), this, SLOT(opStartOnClick()));
    connect(ui->pause, SIGNAL(clicked()), this, SLOT(opPauseOnClick()));

    //commboBox
    connect(ui->opComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(opCurrentChanged(int)));
    connect(ui->speedComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(opSpeedCurrentChanged(int)));

    connect(ui->filePrivateKey, SIGNAL(textChanged(QString)), this, SLOT(fileKeyResidue(QString)));
    connect(ui->fileKeyGer, SIGNAL(clicked()), this, SLOT(fileKeyGenerator()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * clear all the text.
 * @brief MainWindow::clearOnClick
 */
void MainWindow::clearOnClick(){
    ui->plaintext->document()->setPlainText("");
    ui->plaintext_1->document()->setPlainText("");
    ui->ciphertext->document()->setPlainText("");
    ui->private_key->document()->setPlainText("");
}

/**
 * decrypt the ciper text.
 * @brief MainWindow::decryptOnClick
 */
void MainWindow::decryptOnClick(){
    try {
        this->des = new Des(ui->private_key->toPlainText());
        QList<QByteArray> qb = this->des->decrypt(encrypted);
        afterDecrypted = qb;
        switch (plainText1Flag) {
            case BIN:
                ui->plaintext_1->setPlainText(Utils::getBinString(qb));
                break;
            case OTC:
                break;
            case HEX:
                ui->plaintext_1->setPlainText(Utils::getHexString(qb));
                break;
            case UTF8:
                ui->plaintext_1->setPlainText(Utils::fromUtf8(Utils::byteToUshort(qb)));
            break;

        }


    } catch (IllegalKeyException e) {
        QMessageBox::critical(this,
                              "错误", e.what(), QMessageBox::YesAll);
    }

}

/**
 * encrypt the plain text.
 * @brief MainWindow::encryptOnClick
 */
void MainWindow::encryptOnClick(){
    try {
        this->des = new Des(ui->private_key->toPlainText());
        QList<QByteArray> qb = this->des->encrypt(this->ui->plaintext->toPlainText());
        encrypted = qb;
        ui->ciphertext->setPlainText(Utils::fromUtf8(Utils::byteToUshort(qb)));

    } catch (IllegalKeyException e) {
        QMessageBox::critical(this,
                              "错误", e.what(), QMessageBox::YesAll);
    }

}

/**
 * the slot of plaintext comobo
 * @brief MainWindow::plaintextCurrentChanged
 * @param index the plaintext format index {bin, otc, hex}
 */

void MainWindow::plaintextCurrentChanged(int index){
    switch (index) {
       case 0:
        plainTextFlag = BIN;
        ui->plainTextFormatShow->setPlainText(Utils::getBinString(ui->plaintext->toPlainText()));
        break;
       case 1:
        plainTextFlag = OTC;
        ui->plainTextFormatShow->setPlainText(Utils::getOtcString(ui->plaintext->toPlainText()));

        break;
       case 2:
        plainTextFlag = HEX;
        ui->plainTextFormatShow->setPlainText(Utils::getHexString(ui->plaintext->toPlainText()));
        break;
    }
}



/**
 * @brief MainWindow::plaintext1CurrentChanged
 * @param index
 */
void MainWindow::plaintext1CurrentChanged(int index){
    switch (index) {
       case 0:
        plainText1Flag = BIN;
        ui->plaintext_1->setPlainText(Utils::getBinString(afterDecrypted));
        break;
       case 1:
        plainText1Flag = OTC;

        break;
       case 2:
        plainText1Flag = HEX;
        ui->plaintext_1->setPlainText(Utils::getHexString(afterDecrypted));
        break;
       case 3:
        plainText1Flag = UTF8;
        ui->plaintext_1->setPlainText(Utils::fromUtf8(Utils::byteToUshort(afterDecrypted)));
        break;
    }
}
void MainWindow::plaintextChanged(){

    switch (plainTextFlag) {
        case BIN:
            ui->plainTextFormatShow->setPlainText(Utils::getBinString(ui->plaintext->toPlainText()));
            break;
        case OTC:
            break;
        case HEX:
            ui->plainTextFormatShow->setPlainText(Utils::getHexString(ui->plaintext->toPlainText()));
        break;
    default:
        break;
    }

}

/**
 * the slot of private key.
 * @brief MainWindow::privateKeyChanged
 */
void MainWindow::privateKeyChanged(){
    // show the length of private key you can enter.
    ui->privateKeyLen->setText(QString::number(56 - ui->private_key->toPlainText().length()));

}


/**
 * save the all log printed in screen as file.
 * @brief MainWindow::logSaveOnClick
 */
void MainWindow::logSaveOnClick(){
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle("保存文件");
    fileDialog->setAcceptMode(QFileDialog::AcceptSave);
    fileDialog->setFileMode(QFileDialog::AnyFile);
    fileDialog->setViewMode(QFileDialog::Detail);
    fileDialog->setDirectory(".");
    int execCode = fileDialog->exec();
    if(execCode == QDialog::Accepted){
        QString path = fileDialog->selectedFiles()[0];
        QFile logs(path);
        if(logs.open(QIODevice::WriteOnly | QIODevice::Text)){
            logs.write(this->logs.toUtf8());
        }
        logs.close();
        QMessageBox::information(this, "提示", "日志保存成功", QMessageBox::Ok);
    }
    delete  fileDialog;

}
/**
 * select a file as input .
 * @brief MainWindow::selectInFileOnClick
 */
void MainWindow::selectInFileOnClick(){
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle("打开文件");
    fileDialog->setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog->setFileMode(QFileDialog::AnyFile);
    fileDialog->setViewMode(QFileDialog::Detail);
    fileDialog->setDirectory(".");
    int execCode = fileDialog->exec();
    if(execCode == QDialog::Accepted){
        QString path = fileDialog->selectedFiles()[0];
        this->logs.append(Log::Info("输入文件", path));
        updateLog();
        this->ui->inFileSelectedPath->setText(path);
        this->inputFilePath = path;
    }
    delete fileDialog;
}

/**
 * select a file as output.
 * @brief MainWindow::selectOutFileOnClick
 */
void MainWindow::selectOutFileOnClick(){
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle("保存文件");
    fileDialog->setAcceptMode(QFileDialog::AcceptSave);
    fileDialog->setFileMode(QFileDialog::AnyFile);
    fileDialog->setViewMode(QFileDialog::Detail);
    fileDialog->setDirectory(".");
    int execCode = fileDialog->exec();
    if(execCode == QDialog::Accepted){
        QString path = fileDialog->selectedFiles()[0];
        this->logs.append(Log::Info("输出文件" ,path));
        updateLog();
        this->ui->outFileSelectedPath->setText(path);
        this->outputFilePath = path;
    }
    delete  fileDialog;

}

/**
 * the slot of file operation @see op.
 * @brief MainWindow::opCurrentChanged
 * @param index
 */
void MainWindow::opCurrentChanged(int index){
    if(index == 0) op = ENCRYPT;
    else op = DECRYPT;
}

/**
 * select operation speed @see NORMAL, FAST, FASTEST
 * @brief MainWindow::opSpeedCurrentChanged
 * @param index
 */
void MainWindow::opSpeedCurrentChanged(int index){
    switch (index) {
        case 0:
            sp = NORMAL;
            break;
        case 1:
            sp = FAST;
            break;
        case 2:
            sp = FASTEST;
            break;
    }
}

/**
 * start file operation.
 * @brief MainWindow::opStartOnClick
 */
void MainWindow::opStartOnClick(){
    this->ui->start->setEnabled(false);
    QString key = this->ui->filePrivateKey->text();
    if(key.length() == 0){
        this->logs.append(Log::Error("没有输入密钥！"));
        updateLog();
        this->ui->start->setEnabled(true);
        return;
    }

    if(inputFilePath.length() == 0){
        this->logs.append(Log::Error("没有输入文件！"));
        updateLog();
        this->ui->start->setEnabled(true);
        return;
    }

    if(outputFilePath.length() == 0){
        this->logs.append(Log::Error("没有输出文件！"));
        this->ui->start->setEnabled(true);
        updateLog();
        return;
    }

    fp = new FileOp(this);
    fp->setKey(key);

    connect(fp, SIGNAL(onProcess(int)), this, SLOT(fileOnProcess(int)));
    connect(fp, SIGNAL(finished()), this, SLOT(fileFinished()));
    connect(fp, SIGNAL(error(QString)), this, SLOT(fileOpError(QString)));

    if(op == ENCRYPT) {
        connect(fp, SIGNAL(onEncryptStart(QString, QString, qint64)), this , SLOT(fileEncryptStart(QString, QString, qint64)));
        fp->encryptFile(inputFilePath, outputFilePath);
    }else {
        connect(fp, SIGNAL(onDecryptStart(QString, QString, QString, qint64)), this , SLOT(fileDecryptStart(QString, QString, QString, qint64)));
        fp->decryptFile(inputFilePath, outputFilePath);
    }
}

/**
 * pause the operation.
 * @brief MainWindow::opPauseOnClick
 */
void MainWindow::opPauseOnClick(){
    // nothing to do
}

/**
 * update the log
 * @brief MainWindow::updateLog
 */
void MainWindow::updateLog(){
    this->ui->logs->setPlainText(this->logs);
}

/**
 * the slot of file operation start.
 * @brief MainWindow::fileStart
 * @param name  the operation file name.
 * @param md5  the md5
 * @param len  the length of file.
 */
void MainWindow::fileEncryptStart(QString name, QString md5, qint64 len){
    this->logs.append(Log::Info("文件名称", name));
    this->logs.append(Log::Info("文件大小", QString::number(len)));
    this->logs.append(Log::Info("文件md5值", md5));
    this->size = len;
    this->logs.append(Log::Info("开始加密操作..."));
    this->ui->progressBar->setRange(0, int(len));
    this->ui->progressBar->setValue(0);
    updateLog();
}

void MainWindow::fileDecryptStart(QString name, QString time, QString md5, qint64 len){
    this->logs.append(Log::Info("原文件名称", name));
    this->logs.append(Log::Info("原文件大小", QString::number(len)));
    this->logs.append(Log::Info("原文件加密时间", time));
    this->logs.append(Log::Info("原文件md5值", md5));
    this->md5 = md5;
    this->size = len;
    this->logs.append(Log::Info("开始解密操作..."));
    this->ui->progressBar->setRange(0, int(len));
    this->ui->progressBar->setValue(0);
    updateLog();
}
/**
 * the slot of file operation running.
 * @brief MainWindow::fileOnProcess
 * @param process
 */
void MainWindow::fileOnProcess(int process){
    this->ui->progressBar->setValue(process);
    QString rate = QString::number(static_cast<double>(process) / static_cast<double>(size) * 100);
    qDebug()<<rate;
    this->ui->rate->setText(rate.append("%"));
}

/**
 * the slot of file operation finished.
 * @brief MainWindow::fileFinished
 */
void MainWindow::fileFinished(){
    this->ui->start->setEnabled(true);
    if(ui->decryptValid->isChecked() && this->op == DECRYPT){
        this->logs.append(Log::Info("正在校验md5..."));
        updateLog();
        QString newFileMd5 = FileOp::fileMd5(outputFilePath);
        this->logs.append(Log::Info("解密文件md5 ", newFileMd5));
        if(newFileMd5.compare(md5) == 0)
            this->logs.append(Log::Info("两个文件md5相符！"));
        else
            this->logs.append(Log::Info("两个文件md5不符！"));
        updateLog();
    }
    this->logs.append(Log::Info("操作完成！"));
    updateLog();
}

/**
 * the slot of file opertion error occured.
 * @brief MainWindow::fileOpError
 * @param s error message.
 */
void MainWindow::fileOpError(QString s){
    this->ui->start->setEnabled(true);
    this->logs.append(Log::Error(s));
    updateLog();
}

/**
 * generate a random 56-bits private key.
 * @brief MainWindow::randomKeyGenerator
 * @return s
 */
QString MainWindow::randomKeyGenerator(){
    QString s;
    for (int i = 0; i < 56; i++) {
        QTime time =  QTime::currentTime();
        qsrand(static_cast<uint>(time.msec() + time.second() * 1000));
        int random = qrand() % 2;
        s.append(QString::number(random));
    }
    return  s;
}


/**
 * slot of random private key generate.
 * @brief MainWindow::stringKeyGenerator
 */
void MainWindow::stringKeyGenerator(){
    this->ui->private_key->setPlainText(randomKeyGenerator());
}

/**
 * the residue key you enter
 * @brief MainWindow::fileKeyResidue
 * @param s
 */
void MainWindow::fileKeyResidue(QString s){
    this->ui->residueKey->setText(QString::number(56 - s.length()));
}

/**
 * @brief MainWindow::fileKeyGenerator
 */
void MainWindow::fileKeyGenerator(){
    this->ui->filePrivateKey->setText(randomKeyGenerator());
}

