/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *btn_last;
    QPushButton *btn_next;
    QPushButton *btn_pause;
    QLabel *label_album;
    QPushButton *btn_musiclist;
    QPushButton *btn_soundswitch;
    QListWidget *listWidget;
    QPushButton *btn_back;
    QPushButton *btn_front;
    QPushButton *btn_lrc;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1024, 600);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        btn_last = new QPushButton(centralWidget);
        btn_last->setObjectName(QStringLiteral("btn_last"));
        btn_last->setGeometry(QRect(412, 500, 50, 50));
        btn_next = new QPushButton(centralWidget);
        btn_next->setObjectName(QStringLiteral("btn_next"));
        btn_next->setGeometry(QRect(562, 500, 50, 50));
        btn_pause = new QPushButton(centralWidget);
        btn_pause->setObjectName(QStringLiteral("btn_pause"));
        btn_pause->setGeometry(QRect(487, 500, 50, 50));
        label_album = new QLabel(centralWidget);
        label_album->setObjectName(QStringLiteral("label_album"));
        label_album->setGeometry(QRect(50, 60, 200, 200));
        btn_musiclist = new QPushButton(centralWidget);
        btn_musiclist->setObjectName(QStringLiteral("btn_musiclist"));
        btn_musiclist->setGeometry(QRect(900, 500, 50, 50));
        btn_soundswitch = new QPushButton(centralWidget);
        btn_soundswitch->setObjectName(QStringLiteral("btn_soundswitch"));
        btn_soundswitch->setGeometry(QRect(0, 500, 50, 50));
        listWidget = new QListWidget(centralWidget);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(724, 40, 300, 350));
        btn_back = new QPushButton(centralWidget);
        btn_back->setObjectName(QStringLiteral("btn_back"));
        btn_back->setGeometry(QRect(337, 500, 50, 50));
        btn_front = new QPushButton(centralWidget);
        btn_front->setObjectName(QStringLiteral("btn_front"));
        btn_front->setGeometry(QRect(637, 500, 50, 50));
        btn_lrc = new QPushButton(centralWidget);
        btn_lrc->setObjectName(QStringLiteral("btn_lrc"));
        btn_lrc->setGeometry(QRect(820, 500, 50, 50));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1024, 28));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        btn_last->setText(QString());
        btn_next->setText(QString());
        btn_pause->setText(QString());
        label_album->setText(QApplication::translate("MainWindow", "album", nullptr));
        btn_musiclist->setText(QString());
        btn_soundswitch->setText(QString());
        btn_back->setText(QString());
        btn_front->setText(QString());
        btn_lrc->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
