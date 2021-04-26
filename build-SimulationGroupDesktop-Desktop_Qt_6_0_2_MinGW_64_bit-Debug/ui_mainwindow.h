/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *mapShowLabel;
    QPushButton *startPushButton;
    QPushButton *pausePushButton;
    QSlider *speedSlider;
    QLabel *speedShowlabel2;
    QLabel *speedShowLabel;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1000, 800);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        mapShowLabel = new QLabel(centralwidget);
        mapShowLabel->setObjectName(QString::fromUtf8("mapShowLabel"));
        mapShowLabel->setGeometry(QRect(10, 120, 971, 641));
        QFont font;
        font.setPointSize(32);
        mapShowLabel->setFont(font);
        mapShowLabel->setCursor(QCursor(Qt::PointingHandCursor));
        startPushButton = new QPushButton(centralwidget);
        startPushButton->setObjectName(QString::fromUtf8("startPushButton"));
        startPushButton->setGeometry(QRect(70, 20, 211, 71));
        QFont font1;
        font1.setPointSize(24);
        startPushButton->setFont(font1);
        startPushButton->setCursor(QCursor(Qt::PointingHandCursor));
        startPushButton->setIconSize(QSize(16, 16));
        pausePushButton = new QPushButton(centralwidget);
        pausePushButton->setObjectName(QString::fromUtf8("pausePushButton"));
        pausePushButton->setGeometry(QRect(290, 20, 181, 71));
        pausePushButton->setFont(font1);
        pausePushButton->setCursor(QCursor(Qt::PointingHandCursor));
        speedSlider = new QSlider(centralwidget);
        speedSlider->setObjectName(QString::fromUtf8("speedSlider"));
        speedSlider->setGeometry(QRect(490, 35, 211, 31));
        speedSlider->setCursor(QCursor(Qt::PointingHandCursor));
        speedSlider->setMinimum(1);
        speedSlider->setMaximum(32);
        speedSlider->setOrientation(Qt::Horizontal);
        speedShowlabel2 = new QLabel(centralwidget);
        speedShowlabel2->setObjectName(QString::fromUtf8("speedShowlabel2"));
        speedShowlabel2->setGeometry(QRect(800, 40, 51, 21));
        QFont font2;
        font2.setPointSize(14);
        speedShowlabel2->setFont(font2);
        speedShowlabel2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        speedShowLabel = new QLabel(centralwidget);
        speedShowLabel->setObjectName(QString::fromUtf8("speedShowLabel"));
        speedShowLabel->setGeometry(QRect(710, 30, 81, 31));
        speedShowLabel->setFont(font1);
        speedShowLabel->setLayoutDirection(Qt::LeftToRight);
        speedShowLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1000, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        mapShowLabel->setText(QString());
        startPushButton->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213", nullptr));
        pausePushButton->setText(QCoreApplication::translate("MainWindow", "\346\232\202\345\201\234", nullptr));
        speedShowlabel2->setText(QCoreApplication::translate("MainWindow", "\345\270\247/s", nullptr));
        speedShowLabel->setText(QCoreApplication::translate("MainWindow", "5", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
