#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("SM3");

    this->ui->tabWidget->setTabText(0, "字符");
    this->ui->tabWidget->setTabText(1, "文件");


    this->ui->stringSM3->setReadOnly(true);
    this->ui->fileSM3->setReadOnly(true);
    this->ui->filePathInput->setReadOnly(true);

    /** string **/
    connect(ui->stringStart, SIGNAL(clicked()), this, SLOT(stringStart()));

    /** file **/
    connect(ui->fileSelect, SIGNAL(clicked()), this, SLOT(selectFile()));
    connect(ui->fileStart, SIGNAL(clicked()), this, SLOT(fileStart()));
    this->ui->progressBar->setValue(0);
    qDebug("OF: %x",(0xffffffff + 0x01));
}

MainWindow::~MainWindow()
{
    delete ui;

}

/**
 * execute string sm3
 * @brief MainWindow::stringStart
 */
void MainWindow::stringStart(){
    SM3 *sm3 = new SM3();
    QByteArray db = this->ui->stringInput->toPlainText().toUtf8();
    for(int i = 0; i < db.size() / 64; i++){
        sm3->addData(subByteArray(db, i * 64, 64));
    }

    if(db.size() % 64 != 0) sm3->addData(subByteArray(db, db.size()  - (db.size() % 64) , db.size() % 64));

    QByteArray byte = sm3->toByte();
    this->ui->stringSM3->setPlainText(QString(byte));
}

/**
 * split QByteArray
 * @brief MainWindow::subByteArray
 * @param q
 * @param start
 * @param count
 * @return
 */
QByteArray MainWindow::subByteArray(QByteArray q, int start, int count){
    QByteArray a;
    for(int i = start; i < count; i++)
        a.append(q.at(i));
    return a;
}

/**
 * select a input file path
 * @brief MainWindow::selectFile
 */
void MainWindow::selectFile(){
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle("打开文件");
    fileDialog->setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog->setFileMode(QFileDialog::AnyFile);
    fileDialog->setViewMode(QFileDialog::Detail);
    fileDialog->setDirectory(".");
    int execCode = fileDialog->exec();
    if(execCode == QDialog::Accepted){
        QString path = fileDialog->selectedFiles()[0];
        this->ui->filePathInput->setText(path);
        this->path = path;
    }
    delete fileDialog;
}

/**
 * execute file sm3
 * @brief MainWindow::fileStart
 */
void MainWindow::fileStart(){
    if(this->ui->filePathInput->text().length() == 0) return;
    this->ui->fileStart->setEnabled(false);
    FileOp *op = new FileOp(this->path);
    op->opStart();
    connect(op, SIGNAL(onStart(QString, qint64)), this, SLOT(fileStart(QString, qint64)));
    connect(op, SIGNAL(onProcess(qint64)), this, SLOT(fileProcess(qint64)));
    connect(op, SIGNAL(onFinish(qint64, QString)), this, SLOT(fileFinished(qint64, QString)));
}

/**
 * start state
 * @brief MainWindow::fileStart
 * @param name
 * @param len
 */
void MainWindow::fileStart(QString name, qint64 len){
    qDebug()<<name;
    this->size = len;
    this->ui->progressBar->setRange(0, int(len));
    qDebug()<<len;
}

/**
 * processing state
 * @brief MainWindow::fileProcess
 * @param pro
 */
void MainWindow::fileProcess(qint64 pro){
    this->ui->progressBar->setValue(int(pro));
    this->ui->rate->setText(QString::number(static_cast<double>(pro) / static_cast<double>(size) * 100).append("%"));
}


/**
 * finish state
 * @brief MainWindow::fileFinished
 * @param pro
 * @param sm3
 */
void MainWindow::fileFinished(qint64 pro, QString sm3){
    this->ui->progressBar->setValue(int(pro));
    this->ui->rate->setText(QString::number(static_cast<double>(pro) / static_cast<double>(size) * 100).append("%"));
    this->ui->fileSM3->setText(sm3);
    this->ui->fileStart->setEnabled(true);
}
