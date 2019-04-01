#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("凯撒密码");
    connect(ui->decrypt_radio, SIGNAL(clicked()), this, SLOT(decrypt_click()));
    connect(ui->encrpt_radio, SIGNAL(clicked()), this, SLOT(encrypt_click()));
    connect(ui->clear, SIGNAL(clicked()), this, SLOT(clear()));
    connect(ui->op, SIGNAL(clicked()), this, SLOT(op_click()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete caesar;
}


void MainWindow::decrypt_click()
{
    this->flag = DECRYPT;
}

void MainWindow::encrypt_click()
{
    this->flag = ENCRYPT;
}

void MainWindow::op_click()
{
    caesar = new Caesar(ui->private_key->toPlainText());
    if(flag == ENCRYPT) {
        QString plaintext = ui->text->document()->toPlainText();
        ui->ciphertext->setPlainText(caesar->encrypt(ui->text->toPlainText()));
    }
    else if (flag == DECRYPT) {
        QString plaintext = ui->ciphertext->document()->toPlainText();
        ui->text->setPlainText(caesar->decrypt(ui->ciphertext->toPlainText()));
    }
}

void MainWindow::clear()
{
    ui->text->setPlainText("");
    ui->ciphertext->setPlainText("");
    ui->private_key->setText("");
}
