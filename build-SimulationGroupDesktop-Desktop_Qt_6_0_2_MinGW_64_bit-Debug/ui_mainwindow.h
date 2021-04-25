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
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDial>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *modelset;
    QAction *modelnew;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QFrame *mapShowLabel;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout;
    QLabel *nowTimeLabel;
    QSlider *progressSlider;
    QLabel *runTimeLabel;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_2;
    QWidget *widget;
    QPushButton *nextFrameButton;
    QPushButton *lastFrameButton;
    QLabel *speedShowLabel;
    QLabel *speedShowlabel2;
    QPushButton *startPushButton;
    QDial *speedSlider;
    QWidget *widget_3;
    QLabel *label_2;
    QLabel *timeSpend;
    QLabel *label;
    QLabel *label_3;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QMenu *menu_4;
    QMenu *menu_5;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(677, 505);
        modelset = new QAction(MainWindow);
        modelset->setObjectName(QString::fromUtf8("modelset"));
        modelnew = new QAction(MainWindow);
        modelnew->setObjectName(QString::fromUtf8("modelnew"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(9, 0, -1, 0);
        mapShowLabel = new QFrame(centralwidget);
        mapShowLabel->setObjectName(QString::fromUtf8("mapShowLabel"));
        mapShowLabel->setFrameShape(QFrame::StyledPanel);
        mapShowLabel->setFrameShadow(QFrame::Raised);
        mapShowLabel->setLineWidth(0);

        verticalLayout->addWidget(mapShowLabel);

        widget_2 = new QWidget(centralwidget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget_2->sizePolicy().hasHeightForWidth());
        widget_2->setSizePolicy(sizePolicy);
        widget_2->setMinimumSize(QSize(0, 21));
        horizontalLayout = new QHBoxLayout(widget_2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        nowTimeLabel = new QLabel(widget_2);
        nowTimeLabel->setObjectName(QString::fromUtf8("nowTimeLabel"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(nowTimeLabel->sizePolicy().hasHeightForWidth());
        nowTimeLabel->setSizePolicy(sizePolicy1);
        nowTimeLabel->setMinimumSize(QSize(61, 21));
        QFont font;
        font.setPointSize(12);
        nowTimeLabel->setFont(font);
        nowTimeLabel->setLayoutDirection(Qt::LeftToRight);
        nowTimeLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(nowTimeLabel);

        progressSlider = new QSlider(widget_2);
        progressSlider->setObjectName(QString::fromUtf8("progressSlider"));
        progressSlider->setCursor(QCursor(Qt::PointingHandCursor));
        progressSlider->setFocusPolicy(Qt::StrongFocus);
        progressSlider->setMaximum(0);
        progressSlider->setPageStep(1);
        progressSlider->setTracking(true);
        progressSlider->setOrientation(Qt::Horizontal);
        progressSlider->setInvertedAppearance(false);
        progressSlider->setInvertedControls(false);
        progressSlider->setTickPosition(QSlider::NoTicks);
        progressSlider->setTickInterval(0);

        horizontalLayout->addWidget(progressSlider);

        runTimeLabel = new QLabel(widget_2);
        runTimeLabel->setObjectName(QString::fromUtf8("runTimeLabel"));
        sizePolicy1.setHeightForWidth(runTimeLabel->sizePolicy().hasHeightForWidth());
        runTimeLabel->setSizePolicy(sizePolicy1);
        runTimeLabel->setMinimumSize(QSize(61, 21));
        runTimeLabel->setFont(font);
        runTimeLabel->setLayoutDirection(Qt::LeftToRight);
        runTimeLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        runTimeLabel->setWordWrap(false);

        horizontalLayout->addWidget(runTimeLabel);


        verticalLayout->addWidget(widget_2);

        widget_4 = new QWidget(centralwidget);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        sizePolicy.setHeightForWidth(widget_4->sizePolicy().hasHeightForWidth());
        widget_4->setSizePolicy(sizePolicy);
        widget_4->setMinimumSize(QSize(0, 60));
        horizontalLayout_2 = new QHBoxLayout(widget_4);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(widget_4);
        widget->setObjectName(QString::fromUtf8("widget"));
        QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy2);
        widget->setMinimumSize(QSize(224, 60));
        nextFrameButton = new QPushButton(widget);
        nextFrameButton->setObjectName(QString::fromUtf8("nextFrameButton"));
        nextFrameButton->setGeometry(QRect(190, 20, 31, 31));
        QFont font1;
        font1.setPointSize(16);
        nextFrameButton->setFont(font1);
        nextFrameButton->setCursor(QCursor(Qt::WhatsThisCursor));
        lastFrameButton = new QPushButton(widget);
        lastFrameButton->setObjectName(QString::fromUtf8("lastFrameButton"));
        lastFrameButton->setGeometry(QRect(70, 20, 31, 31));
        lastFrameButton->setFont(font1);
        lastFrameButton->setCursor(QCursor(Qt::WhatsThisCursor));
        speedShowLabel = new QLabel(widget);
        speedShowLabel->setObjectName(QString::fromUtf8("speedShowLabel"));
        speedShowLabel->setGeometry(QRect(340, 20, 51, 31));
        QFont font2;
        font2.setPointSize(18);
        speedShowLabel->setFont(font2);
        speedShowLabel->setLayoutDirection(Qt::LeftToRight);
        speedShowLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        speedShowLabel->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
        speedShowlabel2 = new QLabel(widget);
        speedShowlabel2->setObjectName(QString::fromUtf8("speedShowlabel2"));
        speedShowlabel2->setGeometry(QRect(400, 30, 31, 21));
        speedShowlabel2->setFont(font);
        speedShowlabel2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        startPushButton = new QPushButton(widget);
        startPushButton->setObjectName(QString::fromUtf8("startPushButton"));
        startPushButton->setGeometry(QRect(120, 20, 51, 31));
        startPushButton->setFont(font1);
        startPushButton->setCursor(QCursor(Qt::ArrowCursor));
        startPushButton->setIconSize(QSize(16, 16));
        speedSlider = new QDial(widget);
        speedSlider->setObjectName(QString::fromUtf8("speedSlider"));
        speedSlider->setGeometry(QRect(260, 0, 88, 64));
        speedSlider->setMinimum(1);
        speedSlider->setMaximum(32);
        speedSlider->setPageStep(8);
        speedSlider->setOrientation(Qt::Horizontal);
        speedSlider->setInvertedAppearance(false);
        speedSlider->setInvertedControls(false);
        speedSlider->setWrapping(true);
        speedSlider->setNotchesVisible(false);

        horizontalLayout_2->addWidget(widget);

        widget_3 = new QWidget(widget_4);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        sizePolicy1.setHeightForWidth(widget_3->sizePolicy().hasHeightForWidth());
        widget_3->setSizePolicy(sizePolicy1);
        widget_3->setMinimumSize(QSize(151, 51));
        widget_3->setMaximumSize(QSize(16777215, 16777215));
        widget_3->setLayoutDirection(Qt::LeftToRight);
        widget_3->setAutoFillBackground(false);
        label_2 = new QLabel(widget_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(130, 30, 21, 21));
        timeSpend = new QLabel(widget_3);
        timeSpend->setObjectName(QString::fromUtf8("timeSpend"));
        timeSpend->setGeometry(QRect(70, 30, 54, 20));
        timeSpend->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label = new QLabel(widget_3);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 30, 31, 21));
        label_3 = new QLabel(widget_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(0, 30, 31, 20));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(widget_3);


        verticalLayout->addWidget(widget_4);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 677, 21));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        menu_3 = new QMenu(menubar);
        menu_3->setObjectName(QString::fromUtf8("menu_3"));
        menu_4 = new QMenu(menubar);
        menu_4->setObjectName(QString::fromUtf8("menu_4"));
        menu_5 = new QMenu(menubar);
        menu_5->setObjectName(QString::fromUtf8("menu_5"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_2->menuAction());
        menubar->addAction(menu_3->menuAction());
        menubar->addAction(menu_4->menuAction());
        menubar->addAction(menu_5->menuAction());
        menu_2->addAction(modelnew);
        menu_2->addAction(modelset);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\347\276\244\344\275\223\346\250\241\346\213\237\345\231\250", nullptr));
#if QT_CONFIG(whatsthis)
        MainWindow->setWhatsThis(QCoreApplication::translate("MainWindow", "<html><head/><body><p>\345\274\200\345\247\213</p></body></html>", nullptr));
#endif // QT_CONFIG(whatsthis)
        modelset->setText(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256", nullptr));
        modelnew->setText(QCoreApplication::translate("MainWindow", "\346\226\260\345\273\272", nullptr));
        nowTimeLabel->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        runTimeLabel->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
#if QT_CONFIG(whatsthis)
        nextFrameButton->setWhatsThis(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:14pt;\">\344\270\213\344\270\200\345\270\247</span></p></body></html>", nullptr));
#endif // QT_CONFIG(whatsthis)
        nextFrameButton->setText(QCoreApplication::translate("MainWindow", ">>", nullptr));
#if QT_CONFIG(whatsthis)
        lastFrameButton->setWhatsThis(QCoreApplication::translate("MainWindow", "<html><head/><body><p>\344\270\212\344\270\200\345\270\247</p></body></html>", nullptr));
#endif // QT_CONFIG(whatsthis)
        lastFrameButton->setText(QCoreApplication::translate("MainWindow", "<<", nullptr));
        speedShowLabel->setText(QCoreApplication::translate("MainWindow", "10", nullptr));
        speedShowlabel2->setText(QCoreApplication::translate("MainWindow", "\345\270\247/s", nullptr));
        startPushButton->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "ms", nullptr));
        timeSpend->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\347\272\277\347\250\213", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266", nullptr));
        menu_2->setTitle(QCoreApplication::translate("MainWindow", "\346\250\241\345\236\213", nullptr));
        menu_3->setTitle(QCoreApplication::translate("MainWindow", "\346\223\215\344\275\234", nullptr));
        menu_4->setTitle(QCoreApplication::translate("MainWindow", "\347\273\237\350\256\241", nullptr));
        menu_5->setTitle(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
