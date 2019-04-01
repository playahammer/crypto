#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "caesar.h"

enum crypt_flag
{
    ENCRYPT = 0,
    DECRYPT = 1
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
    void decrypt_click(); //decrypt_radio slot
    void encrypt_click(); //encrypt_radio slot
    void op_click();   //op slot
    void clear(); //clear text slot

private:
    Ui::MainWindow *ui;
    enum crypt_flag flag;
    Caesar *caesar;
};

#endif // MAINWINDOW_H
