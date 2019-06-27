#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("RSA");

    /*
    clock_t clk1 = clock();
    for(int i = 0; i < 1; i++){
        qDebug()<<QString::fromStdString(Rsa::randomPrimeGenerator(Rsa::RSA1024).toString());
    }
    qDebug()<<(clock() - clk1);
    */
    connect(ui->random, SIGNAL(clicked()), this, SLOT(randomGenerateClick()));

    connect(ui->encrypt, SIGNAL(clicked()), this, SLOT(encryptClick()));
    connect(ui->decrypt, SIGNAL(clicked()), this, SLOT(decryptClick()));
    connect(ui->selectFile, SIGNAL(clicked()), this, SLOT(fileSelectClick()));
    connect(ui->makeSignature, SIGNAL(clicked()), this, SLOT(makeSignature()));
    //BigInt s1 = BigInt("2") % BigInt("2");
    //qDebug()<<QString::fromStdString(s1.toString());
    //qDebug()<<QString::fromStdString()
    /*
    BigInt primerP = Rsa::randomPrimeGenerator(Rsa::RSA128);
    BigInt primerQ = Rsa::randomPrimeGenerator(Rsa::RSA128);
    BigInt publicKey = Rsa::publicKeyGenerator(primerP, primerQ);
    BigInt privateKey = Rsa::privateKeyGenerator((primerP - 1)*(primerQ - 1), publicKey);
    //BigInt public
    qDebug()<<"public key:"<<QString::fromStdString(publicKey.toString());
    qDebug()<<"private key:"<<QString::fromStdString(privateKey.toString());
    qDebug()<<"n:"<<QString::fromStdString((primerP * primerQ).toString());
    qDebug()<<"fn:"<<QString::fromStdString(((primerP - 1) * (primerQ - 1)).toString());
    BigInt cmd = Rsa::encrypt(BigInt("2342"), publicKey, primerP * primerQ);
    BigInt dec = Rsa::decrypt(cmd, privateKey, primerP * primerQ);
    qDebug()<<QString::fromStdString(cmd.toString());
    qDebug()<<QString::fromStdString(dec.toString());
    */

}

void MainWindow::randomGenerateClick(){
    rsa rsa = Rsa::createRandomRsa(Rsa::RSA256);
    qDebug()<<QString::fromStdString(rsa.d.toString());
    this->ui->p_text->setText(QString::fromStdString(rsa.p.toString()));
    this->ui->q_text->setText(QString::fromStdString(rsa.q.toString()));
    this->ui->n_text->setText(QString::fromStdString((rsa.p * rsa.q).toString()));
    this->ui->e_text->setText(QString::fromStdString(rsa.e.toString()));
    this->ui->d_text->setText(QString::fromStdString(rsa.d.toString()));
}

void MainWindow::encryptClick(){
    QString plain = this->ui->plaintext->toPlainText();
    QByteArray qb = plain.toUtf8();
    std::string s = byteToString(qb);
    BigInt bint;
    if(s.at(0) == '0') bint = BigInt(s.substr(1));
    else bint = BigInt(s);

    std::string n = this->ui->n_text->text().toStdString();
    std::string e = this->ui->e_text->text().toStdString();

    BigInt cipher = Rsa::encrypt(bint, e, n);
    this->ui->ciphertext->setPlainText(QString::fromStdString(cipher.toString()));
}

void MainWindow::decryptClick(){

    QString cipher = this->ui->ciphertext->toPlainText();
    BigInt s(cipher.toStdString());
    std::string n = this->ui->n_text->text().toStdString();
    std::string d = this->ui->d_text->text().toStdString();
    BigInt c = Rsa::decrypt(s, d, n);

    QByteArray qb = stringToByte(c.toString());
    QString s2 = QString::fromUtf8(qb);
    this->ui->dciphertext->setPlainText(s2);
}

std::string MainWindow::byteToString(QByteArray qb){
    std::string s;
    for (int i = 0; i < qb.length(); i++) {
        unsigned char uchar = static_cast<unsigned char>(qb[i]);

        if(uchar < 10) s.append("0");
        if(uchar < 100) s.append("0");
        s.append(std::to_string(uchar));
    }
    return s;
}

QByteArray MainWindow::stringToByte(std::string s){
    std::string s1;
    QByteArray qb;
    s = s.substr(1);
    if(s.length() % 3 != 0) s1.append("0");
    s1.append(s);
    for(unsigned long long i = 0; i < s1.length() / 3; i++){
        int pre = 100;
        int sum = 0;
        for(int j = 0; j < 3; j++){
            unsigned char code = static_cast<unsigned char>(s1[i * 3 + j]) - 48;
            sum += code * pre;
            pre /= 10;
        }
        qb.append(static_cast<char>(sum));

    }
    return qb;
}

void MainWindow::fileSelectClick(){
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle("打开文件");
    fileDialog->setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog->setFileMode(QFileDialog::AnyFile);
    fileDialog->setViewMode(QFileDialog::Detail);
    fileDialog->setDirectory(".");
    int execCode = fileDialog->exec();
    if(execCode == QDialog::Accepted){
        QString path = fileDialog->selectedFiles()[0];
        this->ui->filePath->setText(path);
        this->path = path;
    }
    delete fileDialog;
}


void MainWindow::fileStart(QString name, qint64 len){
    //TODO;
    qDebug()<<"File Name:" << name << " File Length:" << len << "bytes";
}

void MainWindow::fileProcess(qint64 process){
    qDebug()<<process;
}

void MainWindow::fileFinished(qint64 process, QString sm3){
    qDebug()<<process;
    this->ui->sm3->setText(sm3);
    std::string n = this->ui->n_text->text().toStdString();
    std::string e = this->ui->e_text->text().toStdString();
    this->ui->signature->setText(QString::fromStdString(Rsa::encrypt(hexToBigInt(sm3), e, n).toString()));
}

void MainWindow::makeSignature(){
    FileOp *op = new FileOp(this->path);
    op->opStart();
    connect(op, SIGNAL(onStart(QString, qint64)), this, SLOT(fileStart(QString, qint64)));
    connect(op, SIGNAL(onProcess(qint64)), this, SLOT(fileProcess(qint64)));
    connect(op, SIGNAL(onFinish(qint64, QString)), this, SLOT(fileFinished(qint64, QString)));

}


BigInt MainWindow::hexToBigInt(QString s){
    BigInt init = BigInt(1);
    BigInt result = BigInt(0);
    QByteArray sb = s.toLatin1();
    for (long long i = sb.length() - 1; i >= 0; i--) {
        int value;
        if(int(sb.at(i)) >= 48 && int(sb.at(i)) <= 58) value = sb.at(i) - '0';
        else {
            value = sb.at(i) - 'a' + 10;
        }
        result += (init * value);
        init *= 16;

    }
    return result;
}
MainWindow::~MainWindow()
{
    delete ui;
}
