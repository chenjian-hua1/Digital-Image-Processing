/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionRGB2Gray;
    QAction *actionOTSU;
    QAction *actionIntroduction;
    QAction *actionNegative;
    QAction *actionCustomize;
    QAction *actionScale;
    QAction *actionBitPlane;
    QAction *actionRotate;
    QAction *actionHistogram;
    QAction *actionHistEqualization;
    QAction *actionSobel;
    QAction *actionPrewitt;
    QAction *actionMedian;
    QAction *actionDilation;
    QAction *actionErosion;
    QAction *actionOpen_2;
    QAction *actionClose;
    QAction *actionConnect4;
    QAction *actionConnect8;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menuIP;
    QMenu *menuBinary;
    QMenu *menuFilter;
    QMenu *menuMorpology;
    QMenu *menuFile;
    QMenu *menuTeam;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1127, 601);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName("actionOpen");
        actionRGB2Gray = new QAction(MainWindow);
        actionRGB2Gray->setObjectName("actionRGB2Gray");
        actionOTSU = new QAction(MainWindow);
        actionOTSU->setObjectName("actionOTSU");
        actionIntroduction = new QAction(MainWindow);
        actionIntroduction->setObjectName("actionIntroduction");
        actionNegative = new QAction(MainWindow);
        actionNegative->setObjectName("actionNegative");
        actionCustomize = new QAction(MainWindow);
        actionCustomize->setObjectName("actionCustomize");
        actionScale = new QAction(MainWindow);
        actionScale->setObjectName("actionScale");
        actionBitPlane = new QAction(MainWindow);
        actionBitPlane->setObjectName("actionBitPlane");
        actionRotate = new QAction(MainWindow);
        actionRotate->setObjectName("actionRotate");
        actionHistogram = new QAction(MainWindow);
        actionHistogram->setObjectName("actionHistogram");
        actionHistEqualization = new QAction(MainWindow);
        actionHistEqualization->setObjectName("actionHistEqualization");
        actionSobel = new QAction(MainWindow);
        actionSobel->setObjectName("actionSobel");
        actionPrewitt = new QAction(MainWindow);
        actionPrewitt->setObjectName("actionPrewitt");
        actionMedian = new QAction(MainWindow);
        actionMedian->setObjectName("actionMedian");
        actionDilation = new QAction(MainWindow);
        actionDilation->setObjectName("actionDilation");
        actionErosion = new QAction(MainWindow);
        actionErosion->setObjectName("actionErosion");
        actionOpen_2 = new QAction(MainWindow);
        actionOpen_2->setObjectName("actionOpen_2");
        actionClose = new QAction(MainWindow);
        actionClose->setObjectName("actionClose");
        actionConnect4 = new QAction(MainWindow);
        actionConnect4->setObjectName("actionConnect4");
        actionConnect8 = new QAction(MainWindow);
        actionConnect8->setObjectName("actionConnect8");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1127, 24));
        menuIP = new QMenu(menubar);
        menuIP->setObjectName("menuIP");
        menuBinary = new QMenu(menuIP);
        menuBinary->setObjectName("menuBinary");
        menuFilter = new QMenu(menuIP);
        menuFilter->setObjectName("menuFilter");
        menuMorpology = new QMenu(menuIP);
        menuMorpology->setObjectName("menuMorpology");
        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        menuTeam = new QMenu(menubar);
        menuTeam->setObjectName("menuTeam");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuIP->menuAction());
        menubar->addAction(menuTeam->menuAction());
        menuIP->addAction(actionRGB2Gray);
        menuIP->addAction(actionNegative);
        menuIP->addAction(actionBitPlane);
        menuIP->addAction(actionHistogram);
        menuIP->addAction(actionHistEqualization);
        menuIP->addAction(menuFilter->menuAction());
        menuIP->addAction(menuBinary->menuAction());
        menuIP->addAction(actionScale);
        menuIP->addAction(actionRotate);
        menuIP->addAction(menuMorpology->menuAction());
        menuBinary->addAction(actionOTSU);
        menuFilter->addAction(actionCustomize);
        menuFilter->addAction(actionSobel);
        menuFilter->addAction(actionPrewitt);
        menuFilter->addAction(actionMedian);
        menuMorpology->addAction(actionDilation);
        menuMorpology->addAction(actionErosion);
        menuMorpology->addAction(actionOpen_2);
        menuMorpology->addAction(actionClose);
        menuMorpology->addAction(actionConnect4);
        menuMorpology->addAction(actionConnect8);
        menuFile->addAction(actionOpen);
        menuTeam->addAction(actionIntroduction);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionOpen->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
        actionRGB2Gray->setText(QCoreApplication::translate("MainWindow", "RGB2Gray", nullptr));
        actionOTSU->setText(QCoreApplication::translate("MainWindow", "OTSU", nullptr));
        actionIntroduction->setText(QCoreApplication::translate("MainWindow", "Introduction", nullptr));
        actionNegative->setText(QCoreApplication::translate("MainWindow", "Negative", nullptr));
        actionCustomize->setText(QCoreApplication::translate("MainWindow", "Customize", nullptr));
        actionScale->setText(QCoreApplication::translate("MainWindow", "Scale", nullptr));
        actionBitPlane->setText(QCoreApplication::translate("MainWindow", "BitPlane", nullptr));
        actionRotate->setText(QCoreApplication::translate("MainWindow", "Rotate", nullptr));
        actionHistogram->setText(QCoreApplication::translate("MainWindow", "Histogram", nullptr));
        actionHistEqualization->setText(QCoreApplication::translate("MainWindow", "HistEqualization", nullptr));
        actionSobel->setText(QCoreApplication::translate("MainWindow", "Sobel", nullptr));
        actionPrewitt->setText(QCoreApplication::translate("MainWindow", "Prewitt", nullptr));
        actionMedian->setText(QCoreApplication::translate("MainWindow", "Median", nullptr));
        actionDilation->setText(QCoreApplication::translate("MainWindow", "Dilation", nullptr));
        actionErosion->setText(QCoreApplication::translate("MainWindow", "Erosion", nullptr));
        actionOpen_2->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
        actionClose->setText(QCoreApplication::translate("MainWindow", "Close", nullptr));
        actionConnect4->setText(QCoreApplication::translate("MainWindow", "Connect4", nullptr));
        actionConnect8->setText(QCoreApplication::translate("MainWindow", "Connect8", nullptr));
        menuIP->setTitle(QCoreApplication::translate("MainWindow", "IP", nullptr));
        menuBinary->setTitle(QCoreApplication::translate("MainWindow", "Binary", nullptr));
        menuFilter->setTitle(QCoreApplication::translate("MainWindow", "Filter", nullptr));
        menuMorpology->setTitle(QCoreApplication::translate("MainWindow", "Morpology", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuTeam->setTitle(QCoreApplication::translate("MainWindow", "Team", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
