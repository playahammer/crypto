#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>


#include "fileop.h"
#include "sm3.h"

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
    void stringStart();
    void selectFile();
    void fileStart();

    /** file op **/
    void fileStart(QString, qint64);
    void fileProcess(qint64);
    void fileFinished(qint64, QString);
private:
    Ui::MainWindow *ui;

    QByteArray subByteArray(QByteArray, int, int);

    QString path;
    qint64 size;
};

#endif // MAINWINDOW_H
