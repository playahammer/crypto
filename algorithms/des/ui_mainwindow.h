/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label;
    QComboBox *plaintextComboBox;
    QHBoxLayout *horizontalLayout_6;
    QPlainTextEdit *plaintext;
    QPlainTextEdit *plainTextFormatShow;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLabel *label_12;
    QLabel *privateKeyLen;
    QPushButton *stringKeyGer;
    QHBoxLayout *horizontalLayout_7;
    QPlainTextEdit *private_key;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_8;
    QPlainTextEdit *ciphertext;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QComboBox *plaintextComboBox_1;
    QPlainTextEdit *plaintext_1;
    QHBoxLayout *horizontalLayout;
    QPushButton *encrypt;
    QPushButton *decrypt;
    QPushButton *clear;
    QWidget *tab_2;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_5;
    QPushButton *logsSave;
    QPlainTextEdit *logs;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_6;
    QLineEdit *inFileSelectedPath;
    QPushButton *selectInFile;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_7;
    QComboBox *opComboBox;
    QLabel *label_8;
    QComboBox *speedComboBox;
    QCheckBox *decryptValid;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_11;
    QLineEdit *filePrivateKey;
    QLabel *label_13;
    QLabel *residueKey;
    QPushButton *fileKeyGer;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_9;
    QLineEdit *outFileSelectedPath;
    QPushButton *selectOutFile;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_10;
    QProgressBar *progressBar;
    QLabel *rate;
    QHBoxLayout *horizontalLayout_14;
    QPushButton *start;
    QPushButton *pause;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1001, 657);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayout_2 = new QGridLayout(tab);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label = new QLabel(tab);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_5->addWidget(label);

        plaintextComboBox = new QComboBox(tab);
        plaintextComboBox->setObjectName(QString::fromUtf8("plaintextComboBox"));

        horizontalLayout_5->addWidget(plaintextComboBox);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        plaintext = new QPlainTextEdit(tab);
        plaintext->setObjectName(QString::fromUtf8("plaintext"));

        horizontalLayout_6->addWidget(plaintext);

        plainTextFormatShow = new QPlainTextEdit(tab);
        plainTextFormatShow->setObjectName(QString::fromUtf8("plainTextFormatShow"));

        horizontalLayout_6->addWidget(plainTextFormatShow);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(tab);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        label_12 = new QLabel(tab);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_2->addWidget(label_12);

        privateKeyLen = new QLabel(tab);
        privateKeyLen->setObjectName(QString::fromUtf8("privateKeyLen"));

        horizontalLayout_2->addWidget(privateKeyLen);

        stringKeyGer = new QPushButton(tab);
        stringKeyGer->setObjectName(QString::fromUtf8("stringKeyGer"));

        horizontalLayout_2->addWidget(stringKeyGer);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        private_key = new QPlainTextEdit(tab);
        private_key->setObjectName(QString::fromUtf8("private_key"));

        horizontalLayout_7->addWidget(private_key);


        verticalLayout->addLayout(horizontalLayout_7);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(tab);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        ciphertext = new QPlainTextEdit(tab);
        ciphertext->setObjectName(QString::fromUtf8("ciphertext"));

        horizontalLayout_8->addWidget(ciphertext);


        verticalLayout->addLayout(horizontalLayout_8);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_4 = new QLabel(tab);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_4->addWidget(label_4);

        plaintextComboBox_1 = new QComboBox(tab);
        plaintextComboBox_1->setObjectName(QString::fromUtf8("plaintextComboBox_1"));

        horizontalLayout_4->addWidget(plaintextComboBox_1);


        verticalLayout->addLayout(horizontalLayout_4);

        plaintext_1 = new QPlainTextEdit(tab);
        plaintext_1->setObjectName(QString::fromUtf8("plaintext_1"));

        verticalLayout->addWidget(plaintext_1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        encrypt = new QPushButton(tab);
        encrypt->setObjectName(QString::fromUtf8("encrypt"));

        horizontalLayout->addWidget(encrypt);

        decrypt = new QPushButton(tab);
        decrypt->setObjectName(QString::fromUtf8("decrypt"));

        horizontalLayout->addWidget(decrypt);

        clear = new QPushButton(tab);
        clear->setObjectName(QString::fromUtf8("clear"));

        horizontalLayout->addWidget(clear);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout_2->addLayout(verticalLayout, 0, 0, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        gridLayout_3 = new QGridLayout(tab_2);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_5 = new QLabel(tab_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_9->addWidget(label_5);

        logsSave = new QPushButton(tab_2);
        logsSave->setObjectName(QString::fromUtf8("logsSave"));

        horizontalLayout_9->addWidget(logsSave);


        verticalLayout_2->addLayout(horizontalLayout_9);

        logs = new QPlainTextEdit(tab_2);
        logs->setObjectName(QString::fromUtf8("logs"));

        verticalLayout_2->addWidget(logs);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_6 = new QLabel(tab_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_10->addWidget(label_6);

        inFileSelectedPath = new QLineEdit(tab_2);
        inFileSelectedPath->setObjectName(QString::fromUtf8("inFileSelectedPath"));

        horizontalLayout_10->addWidget(inFileSelectedPath);

        selectInFile = new QPushButton(tab_2);
        selectInFile->setObjectName(QString::fromUtf8("selectInFile"));

        horizontalLayout_10->addWidget(selectInFile);


        verticalLayout_2->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_7 = new QLabel(tab_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_11->addWidget(label_7);

        opComboBox = new QComboBox(tab_2);
        opComboBox->setObjectName(QString::fromUtf8("opComboBox"));

        horizontalLayout_11->addWidget(opComboBox);

        label_8 = new QLabel(tab_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_11->addWidget(label_8);

        speedComboBox = new QComboBox(tab_2);
        speedComboBox->setObjectName(QString::fromUtf8("speedComboBox"));

        horizontalLayout_11->addWidget(speedComboBox);

        decryptValid = new QCheckBox(tab_2);
        decryptValid->setObjectName(QString::fromUtf8("decryptValid"));
        decryptValid->setMaximumSize(QSize(90, 16777215));

        horizontalLayout_11->addWidget(decryptValid);


        verticalLayout_2->addLayout(horizontalLayout_11);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        label_11 = new QLabel(tab_2);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        horizontalLayout_15->addWidget(label_11);

        filePrivateKey = new QLineEdit(tab_2);
        filePrivateKey->setObjectName(QString::fromUtf8("filePrivateKey"));

        horizontalLayout_15->addWidget(filePrivateKey);

        label_13 = new QLabel(tab_2);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        horizontalLayout_15->addWidget(label_13);

        residueKey = new QLabel(tab_2);
        residueKey->setObjectName(QString::fromUtf8("residueKey"));

        horizontalLayout_15->addWidget(residueKey);

        fileKeyGer = new QPushButton(tab_2);
        fileKeyGer->setObjectName(QString::fromUtf8("fileKeyGer"));

        horizontalLayout_15->addWidget(fileKeyGer);


        verticalLayout_2->addLayout(horizontalLayout_15);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        label_9 = new QLabel(tab_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_12->addWidget(label_9);

        outFileSelectedPath = new QLineEdit(tab_2);
        outFileSelectedPath->setObjectName(QString::fromUtf8("outFileSelectedPath"));

        horizontalLayout_12->addWidget(outFileSelectedPath);

        selectOutFile = new QPushButton(tab_2);
        selectOutFile->setObjectName(QString::fromUtf8("selectOutFile"));

        horizontalLayout_12->addWidget(selectOutFile);


        verticalLayout_2->addLayout(horizontalLayout_12);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        label_10 = new QLabel(tab_2);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        horizontalLayout_13->addWidget(label_10);

        progressBar = new QProgressBar(tab_2);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(24);

        horizontalLayout_13->addWidget(progressBar);

        rate = new QLabel(tab_2);
        rate->setObjectName(QString::fromUtf8("rate"));

        horizontalLayout_13->addWidget(rate);


        verticalLayout_2->addLayout(horizontalLayout_13);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        start = new QPushButton(tab_2);
        start->setObjectName(QString::fromUtf8("start"));

        horizontalLayout_14->addWidget(start);

        pause = new QPushButton(tab_2);
        pause->setObjectName(QString::fromUtf8("pause"));

        horizontalLayout_14->addWidget(pause);


        verticalLayout_2->addLayout(horizontalLayout_14);


        gridLayout_3->addLayout(verticalLayout_2, 0, 0, 1, 1);

        tabWidget->addTab(tab_2, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1001, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QApplication::translate("MainWindow", "\346\230\216\346\226\207", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "\345\257\206\351\222\245", nullptr));
        label_12->setText(QApplication::translate("MainWindow", "\345\257\206\351\222\245\345\211\251\344\275\231\351\225\277\345\272\246", nullptr));
        privateKeyLen->setText(QApplication::translate("MainWindow", "56", nullptr));
        stringKeyGer->setText(QApplication::translate("MainWindow", "\351\232\217\346\234\272\347\224\237\346\210\220\345\257\206\351\222\245", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "\345\257\206\346\226\207", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "\346\230\216\346\226\207", nullptr));
        encrypt->setText(QApplication::translate("MainWindow", "\345\212\240\345\257\206", nullptr));
        decrypt->setText(QApplication::translate("MainWindow", "\350\247\243\345\257\206", nullptr));
        clear->setText(QApplication::translate("MainWindow", "\346\270\205\347\251\272", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Tab 1", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "\346\266\210\346\201\257", nullptr));
        logsSave->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "\351\200\211\345\217\226\346\226\207\344\273\266\357\274\232", nullptr));
        selectInFile->setText(QApplication::translate("MainWindow", "\351\200\211\345\217\226\346\226\207\344\273\266", nullptr));
        label_7->setText(QApplication::translate("MainWindow", "\350\247\243/\345\212\240\345\257\206", nullptr));
        label_8->setText(QApplication::translate("MainWindow", "\351\200\237\345\272\246", nullptr));
        decryptValid->setText(QApplication::translate("MainWindow", "\350\247\243\345\257\206\346\240\241\351\252\214", nullptr));
        label_11->setText(QApplication::translate("MainWindow", "\345\257\206\351\222\245:", nullptr));
        label_13->setText(QApplication::translate("MainWindow", "\345\257\206\351\222\245\345\211\251\344\275\231\351\225\277\345\272\246\357\274\232", nullptr));
        residueKey->setText(QApplication::translate("MainWindow", "56", nullptr));
        fileKeyGer->setText(QApplication::translate("MainWindow", "\347\224\237\346\210\220\351\232\217\346\234\272\345\257\206\351\222\245", nullptr));
        label_9->setText(QApplication::translate("MainWindow", "\350\276\223\345\207\272\346\226\207\344\273\266\357\274\232", nullptr));
        selectOutFile->setText(QApplication::translate("MainWindow", "\351\200\211\345\217\226\346\226\207\344\273\266", nullptr));
        label_10->setText(QApplication::translate("MainWindow", "\345\256\214\346\210\220\346\257\224\344\276\213", nullptr));
        rate->setText(QApplication::translate("MainWindow", "0%", nullptr));
        start->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213", nullptr));
        pause->setText(QApplication::translate("MainWindow", "\347\273\210\346\255\242", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Tab 2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
