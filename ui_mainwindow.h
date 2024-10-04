/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionConfig;
    QAction *actionSave;
    QAction *actionQuit;
    QAction *actionAbout;
    QWidget *centralWidget;
    QSlider *neckTurnSlider;
    QComboBox *comboBox;
    QPushButton *btnLeft;
    QPushButton *btnCentre;
    QPushButton *btnRight;
    QPushButton *btnHello;
    QPushButton *btnAsk;
    QPushButton *btnFortune;
    QPushButton *btnOkBye;
    QPushButton *btnThanks;
    QPushButton *btnAnimate;
    QSlider *volumeSlider;
    QLabel *label;
    QLabel *currentVolume;
    QLabel *currentVolume_2;
    QPlainTextEdit *textToSay;
    QPushButton *btnSpeak;
    QCheckBox *cbSaveFortune;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(877, 604);
        actionConfig = new QAction(MainWindow);
        actionConfig->setObjectName(QString::fromUtf8("actionConfig"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        neckTurnSlider = new QSlider(centralWidget);
        neckTurnSlider->setObjectName(QString::fromUtf8("neckTurnSlider"));
        neckTurnSlider->setGeometry(QRect(520, 0, 160, 29));
        neckTurnSlider->setMinimum(40);
        neckTurnSlider->setMaximum(140);
        neckTurnSlider->setPageStep(10);
        neckTurnSlider->setValue(90);
        neckTurnSlider->setTracking(true);
        neckTurnSlider->setOrientation(Qt::Horizontal);
        neckTurnSlider->setTickPosition(QSlider::TicksBelow);
        comboBox = new QComboBox(centralWidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(20, 10, 311, 27));
        btnLeft = new QPushButton(centralWidget);
        btnLeft->setObjectName(QString::fromUtf8("btnLeft"));
        btnLeft->setGeometry(QRect(20, 60, 101, 31));
        btnCentre = new QPushButton(centralWidget);
        btnCentre->setObjectName(QString::fromUtf8("btnCentre"));
        btnCentre->setGeometry(QRect(130, 60, 101, 31));
        btnRight = new QPushButton(centralWidget);
        btnRight->setObjectName(QString::fromUtf8("btnRight"));
        btnRight->setGeometry(QRect(240, 60, 101, 31));
        btnHello = new QPushButton(centralWidget);
        btnHello->setObjectName(QString::fromUtf8("btnHello"));
        btnHello->setGeometry(QRect(20, 100, 101, 31));
        btnAsk = new QPushButton(centralWidget);
        btnAsk->setObjectName(QString::fromUtf8("btnAsk"));
        btnAsk->setGeometry(QRect(130, 100, 101, 31));
        btnFortune = new QPushButton(centralWidget);
        btnFortune->setObjectName(QString::fromUtf8("btnFortune"));
        btnFortune->setGeometry(QRect(240, 100, 101, 31));
        btnOkBye = new QPushButton(centralWidget);
        btnOkBye->setObjectName(QString::fromUtf8("btnOkBye"));
        btnOkBye->setGeometry(QRect(20, 140, 101, 31));
        btnThanks = new QPushButton(centralWidget);
        btnThanks->setObjectName(QString::fromUtf8("btnThanks"));
        btnThanks->setGeometry(QRect(130, 140, 101, 31));
        btnAnimate = new QPushButton(centralWidget);
        btnAnimate->setObjectName(QString::fromUtf8("btnAnimate"));
        btnAnimate->setGeometry(QRect(20, 190, 321, 31));
        volumeSlider = new QSlider(centralWidget);
        volumeSlider->setObjectName(QString::fromUtf8("volumeSlider"));
        volumeSlider->setGeometry(QRect(40, 280, 20, 201));
        volumeSlider->setMaximum(100);
        volumeSlider->setValue(75);
        volumeSlider->setOrientation(Qt::Vertical);
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 250, 81, 16));
        label->setAlignment(Qt::AlignCenter);
        currentVolume = new QLabel(centralWidget);
        currentVolume->setObjectName(QString::fromUtf8("currentVolume"));
        currentVolume->setGeometry(QRect(20, 490, 57, 15));
        currentVolume->setAlignment(Qt::AlignCenter);
        currentVolume_2 = new QLabel(centralWidget);
        currentVolume_2->setObjectName(QString::fromUtf8("currentVolume_2"));
        currentVolume_2->setGeometry(QRect(140, 250, 421, 21));
        textToSay = new QPlainTextEdit(centralWidget);
        textToSay->setObjectName(QString::fromUtf8("textToSay"));
        textToSay->setGeometry(QRect(140, 280, 581, 191));
        btnSpeak = new QPushButton(centralWidget);
        btnSpeak->setObjectName(QString::fromUtf8("btnSpeak"));
        btnSpeak->setGeometry(QRect(730, 290, 101, 31));
        cbSaveFortune = new QCheckBox(centralWidget);
        cbSaveFortune->setObjectName(QString::fromUtf8("cbSaveFortune"));
        cbSaveFortune->setGeometry(QRect(360, 110, 181, 20));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 877, 19));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::BottomToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionConfig);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionQuit);
        menuHelp->addSeparator();
        menuHelp->addAction(actionAbout);
        mainToolBar->addAction(actionConfig);
        mainToolBar->addAction(actionSave);
        mainToolBar->addAction(actionQuit);
        mainToolBar->addAction(actionAbout);

        retranslateUi(MainWindow);
        QObject::connect(neckTurnSlider, SIGNAL(valueChanged(int)), MainWindow, SLOT(update()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionConfig->setText(QCoreApplication::translate("MainWindow", "Config", nullptr));
        actionSave->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        actionQuit->setText(QCoreApplication::translate("MainWindow", "Quit", nullptr));
        actionAbout->setText(QCoreApplication::translate("MainWindow", "About", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "Afraid", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "Awkward", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("MainWindow", "Angry", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("MainWindow", "Disappointed", nullptr));
        comboBox->setItemText(4, QCoreApplication::translate("MainWindow", "Happy", nullptr));
        comboBox->setItemText(5, QCoreApplication::translate("MainWindow", "Neutral", nullptr));
        comboBox->setItemText(6, QCoreApplication::translate("MainWindow", "Sad", nullptr));
        comboBox->setItemText(7, QCoreApplication::translate("MainWindow", "Sinister", nullptr));
        comboBox->setItemText(8, QCoreApplication::translate("MainWindow", "Sleepy", nullptr));
        comboBox->setItemText(9, QCoreApplication::translate("MainWindow", "Smile", nullptr));
        comboBox->setItemText(10, QCoreApplication::translate("MainWindow", "Sulk", nullptr));
        comboBox->setItemText(11, QCoreApplication::translate("MainWindow", "Surprised", nullptr));
        comboBox->setItemText(12, QCoreApplication::translate("MainWindow", "Yelling", nullptr));
        comboBox->setItemText(13, QCoreApplication::translate("MainWindow", "Worried", nullptr));

        btnLeft->setText(QCoreApplication::translate("MainWindow", "Left", nullptr));
        btnCentre->setText(QCoreApplication::translate("MainWindow", "Centre", nullptr));
        btnRight->setText(QCoreApplication::translate("MainWindow", "Right", nullptr));
        btnHello->setText(QCoreApplication::translate("MainWindow", "Hello", nullptr));
        btnAsk->setText(QCoreApplication::translate("MainWindow", "Ask", nullptr));
        btnFortune->setText(QCoreApplication::translate("MainWindow", "Fortune", nullptr));
        btnOkBye->setText(QCoreApplication::translate("MainWindow", "Ok Bye", nullptr));
        btnThanks->setText(QCoreApplication::translate("MainWindow", "Thanks", nullptr));
        btnAnimate->setText(QCoreApplication::translate("MainWindow", "Animate", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Volume", nullptr));
        currentVolume->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        currentVolume_2->setText(QCoreApplication::translate("MainWindow", "Enter a phrase", nullptr));
        btnSpeak->setText(QCoreApplication::translate("MainWindow", "Speak Phrase", nullptr));
        cbSaveFortune->setText(QCoreApplication::translate("MainWindow", "Save Fortune", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("MainWindow", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
