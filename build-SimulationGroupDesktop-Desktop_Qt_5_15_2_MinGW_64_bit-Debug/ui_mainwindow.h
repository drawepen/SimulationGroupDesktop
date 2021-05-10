/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
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
#include <QtWidgets/QDial>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <showframe.h>
#include "qchartview.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *modelSet;
    QAction *modelnew;
    QAction *useDoc;
    QAction *exportMapImage;
    QAction *exportNowStaImage;
    QAction *exportAllStaImage;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QWidget *widget_4;
    QVBoxLayout *verticalLayout;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout;
    QLabel *nowTimeLabel;
    QSlider *progressSlider;
    QLabel *runTimeLabel;
    QWidget *widget;
    QPushButton *nextFrameButton;
    QPushButton *lastFrameButton;
    QLabel *speedShowLabel;
    QLabel *speedShowlabel2;
    QPushButton *startPushButton;
    QDial *speedSlider;
    QPushButton *resetButton;
    ShowFrame *mapShowFrame;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_2;
    QWidget *widget_6;
    QFrame *frame;
    QGridLayout *gridLayout_2;
    QFrame *frame_2;
    QComboBox *operationTypeCombo;
    QSpinBox *operationValueSpin;
    QSpinBox *operationValueSpin2;
    QLabel *intervalSymbolLable;
    QCheckBox *randButton;
    QFrame *frame_3;
    QLabel *label_4;
    QLabel *label_5;
    QSpinBox *cellXSpin;
    QSpinBox *cellYSpin;
    QTableWidget *stateTable;
    QCheckBox *checkBox;
    QtCharts::QChartView *graphicsView_3;
    QtCharts::QChartView *graphicsView;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QWidget *widget_3;
    QLabel *label_2;
    QLabel *timeSpend;
    QLabel *label;
    QLabel *label_3;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *cpuUseLabel;
    QLabel *ramUseLabel;
    QFrame *toolFrame;
    QPushButton *curTypeButton1;
    QPushButton *curTypeButton2;
    QPushButton *curTypeButton3;
    QPushButton *curTypeButton4;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_7;
    QMenu *menu_2;
    QMenu *menu_3;
    QMenu *menu_4;
    QMenu *menu_5;
    QMenu *menu_6;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(807, 523);
        modelSet = new QAction(MainWindow);
        modelSet->setObjectName(QString::fromUtf8("modelSet"));
        modelnew = new QAction(MainWindow);
        modelnew->setObjectName(QString::fromUtf8("modelnew"));
        useDoc = new QAction(MainWindow);
        useDoc->setObjectName(QString::fromUtf8("useDoc"));
        exportMapImage = new QAction(MainWindow);
        exportMapImage->setObjectName(QString::fromUtf8("exportMapImage"));
        exportNowStaImage = new QAction(MainWindow);
        exportNowStaImage->setObjectName(QString::fromUtf8("exportNowStaImage"));
        exportAllStaImage = new QAction(MainWindow);
        exportAllStaImage->setObjectName(QString::fromUtf8("exportAllStaImage"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        widget_4 = new QWidget(centralwidget);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget_4->sizePolicy().hasHeightForWidth());
        widget_4->setSizePolicy(sizePolicy);
        widget_4->setMinimumSize(QSize(0, 80));
        verticalLayout = new QVBoxLayout(widget_4);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widget_2 = new QWidget(widget_4);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        sizePolicy.setHeightForWidth(widget_2->sizePolicy().hasHeightForWidth());
        widget_2->setSizePolicy(sizePolicy);
        widget_2->setMinimumSize(QSize(0, 20));
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
        font1.setPointSize(20);
        nextFrameButton->setFont(font1);
        nextFrameButton->setCursor(QCursor(Qt::ArrowCursor));
        lastFrameButton = new QPushButton(widget);
        lastFrameButton->setObjectName(QString::fromUtf8("lastFrameButton"));
        lastFrameButton->setGeometry(QRect(70, 20, 31, 31));
        lastFrameButton->setFont(font1);
        lastFrameButton->setCursor(QCursor(Qt::ArrowCursor));
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
        QFont font3;
        font3.setFamily(QString::fromUtf8("Bauhaus 93"));
        font3.setPointSize(20);
        font3.setBold(false);
        font3.setItalic(false);
        font3.setWeight(50);
        startPushButton->setFont(font3);
        startPushButton->setCursor(QCursor(Qt::ArrowCursor));
        startPushButton->setStyleSheet(QString::fromUtf8("font: 20pt \"Bauhaus 93\";"));
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
        resetButton = new QPushButton(widget);
        resetButton->setObjectName(QString::fromUtf8("resetButton"));
        resetButton->setGeometry(QRect(20, 20, 31, 31));
        resetButton->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(widget);


        gridLayout->addWidget(widget_4, 1, 0, 1, 3);

        mapShowFrame = new ShowFrame(centralwidget);
        mapShowFrame->setObjectName(QString::fromUtf8("mapShowFrame"));
        mapShowFrame->setMinimumSize(QSize(60, 0));
        mapShowFrame->setCursor(QCursor(Qt::ArrowCursor));
        mapShowFrame->setFrameShape(QFrame::StyledPanel);
        mapShowFrame->setFrameShadow(QFrame::Raised);
        mapShowFrame->setLineWidth(0);
        horizontalLayout_4 = new QHBoxLayout(mapShowFrame);
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_2 = new QSpacerItem(915, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        widget_6 = new QWidget(mapShowFrame);
        widget_6->setObjectName(QString::fromUtf8("widget_6"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(widget_6->sizePolicy().hasHeightForWidth());
        widget_6->setSizePolicy(sizePolicy3);
        widget_6->setMinimumSize(QSize(2, 0));
        widget_6->setCursor(QCursor(Qt::SplitHCursor));
        widget_6->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_4->addWidget(widget_6);


        gridLayout->addWidget(mapShowFrame, 0, 1, 1, 1);

        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        sizePolicy3.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy3);
        frame->setMinimumSize(QSize(360, 0));
        QFont font4;
        font4.setPointSize(9);
        frame->setFont(font4);
        frame->setAutoFillBackground(false);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        frame->setLineWidth(1);
        gridLayout_2 = new QGridLayout(frame);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        frame_2 = new QFrame(frame);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setMinimumSize(QSize(0, 41));
        frame_2->setMaximumSize(QSize(16777215, 41));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        operationTypeCombo = new QComboBox(frame_2);
        operationTypeCombo->addItem(QString());
        operationTypeCombo->addItem(QString());
        operationTypeCombo->setObjectName(QString::fromUtf8("operationTypeCombo"));
        operationTypeCombo->setGeometry(QRect(0, 10, 41, 22));
        operationTypeCombo->setLayoutDirection(Qt::LeftToRight);
        operationValueSpin = new QSpinBox(frame_2);
        operationValueSpin->setObjectName(QString::fromUtf8("operationValueSpin"));
        operationValueSpin->setGeometry(QRect(50, 10, 42, 22));
        operationValueSpin->setMinimum(-214748364);
        operationValueSpin->setMaximum(2147483647);
        operationValueSpin2 = new QSpinBox(frame_2);
        operationValueSpin2->setObjectName(QString::fromUtf8("operationValueSpin2"));
        operationValueSpin2->setGeometry(QRect(120, 10, 42, 22));
        operationValueSpin2->setMinimum(-214748364);
        operationValueSpin2->setMaximum(2147483647);
        intervalSymbolLable = new QLabel(frame_2);
        intervalSymbolLable->setObjectName(QString::fromUtf8("intervalSymbolLable"));
        intervalSymbolLable->setGeometry(QRect(100, 10, 16, 21));
        randButton = new QCheckBox(frame_2);
        randButton->setObjectName(QString::fromUtf8("randButton"));
        randButton->setGeometry(QRect(170, 10, 51, 21));
        randButton->setLayoutDirection(Qt::LeftToRight);

        gridLayout_2->addWidget(frame_2, 0, 0, 1, 2);

        frame_3 = new QFrame(frame);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(frame_3->sizePolicy().hasHeightForWidth());
        frame_3->setSizePolicy(sizePolicy4);
        frame_3->setMinimumSize(QSize(170, 0));
        frame_3->setMaximumSize(QSize(170, 16777215));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        label_4 = new QLabel(frame_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(5, 10, 16, 21));
        label_5 = new QLabel(frame_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(67, 10, 16, 21));
        cellXSpin = new QSpinBox(frame_3);
        cellXSpin->setObjectName(QString::fromUtf8("cellXSpin"));
        cellXSpin->setGeometry(QRect(20, 10, 42, 22));
        cellXSpin->setMaximum(10000);
        cellYSpin = new QSpinBox(frame_3);
        cellYSpin->setObjectName(QString::fromUtf8("cellYSpin"));
        cellYSpin->setGeometry(QRect(80, 10, 42, 22));
        cellYSpin->setMaximum(10000);
        stateTable = new QTableWidget(frame_3);
        if (stateTable->columnCount() < 2)
            stateTable->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        stateTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        stateTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        stateTable->setObjectName(QString::fromUtf8("stateTable"));
        stateTable->setGeometry(QRect(0, 40, 167, 98));
        stateTable->horizontalHeader()->setDefaultSectionSize(80);
        checkBox = new QCheckBox(frame_3);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(124, 10, 51, 22));

        gridLayout_2->addWidget(frame_3, 1, 0, 1, 1);

        graphicsView_3 = new QtCharts::QChartView(frame);
        graphicsView_3->setObjectName(QString::fromUtf8("graphicsView_3"));
        graphicsView_3->setMinimumSize(QSize(0, 0));
        QFont font5;
        font5.setFamily(QString::fromUtf8("Microsoft JhengHei UI"));
        font5.setPointSize(6);
        font5.setBold(false);
        font5.setItalic(false);
        font5.setWeight(50);
        graphicsView_3->setFont(font5);
        graphicsView_3->setStyleSheet(QString::fromUtf8("font: 6pt \"Microsoft JhengHei UI\";"));

        gridLayout_2->addWidget(graphicsView_3, 1, 1, 1, 1);

        graphicsView = new QtCharts::QChartView(frame);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setMinimumSize(QSize(0, 220));

        gridLayout_2->addWidget(graphicsView, 2, 0, 1, 2);


        gridLayout->addWidget(frame, 0, 2, 1, 1);

        widget_5 = new QWidget(centralwidget);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        QSizePolicy sizePolicy5(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(widget_5->sizePolicy().hasHeightForWidth());
        widget_5->setSizePolicy(sizePolicy5);
        widget_5->setMinimumSize(QSize(0, 20));
        widget_5->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout_3 = new QHBoxLayout(widget_5);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(1044, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        widget_3 = new QWidget(widget_5);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        sizePolicy1.setHeightForWidth(widget_3->sizePolicy().hasHeightForWidth());
        widget_3->setSizePolicy(sizePolicy1);
        widget_3->setMinimumSize(QSize(301, 20));
        widget_3->setMaximumSize(QSize(16777215, 16777215));
        widget_3->setLayoutDirection(Qt::LeftToRight);
        widget_3->setAutoFillBackground(false);
        label_2 = new QLabel(widget_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(280, 0, 21, 21));
        timeSpend = new QLabel(widget_3);
        timeSpend->setObjectName(QString::fromUtf8("timeSpend"));
        timeSpend->setGeometry(QRect(220, 0, 54, 20));
        timeSpend->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label = new QLabel(widget_3);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(190, 0, 31, 21));
        label_3 = new QLabel(widget_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(160, 0, 21, 20));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_6 = new QLabel(widget_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 0, 21, 21));
        label_7 = new QLabel(widget_3);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(70, 0, 31, 21));
        cpuUseLabel = new QLabel(widget_3);
        cpuUseLabel->setObjectName(QString::fromUtf8("cpuUseLabel"));
        cpuUseLabel->setGeometry(QRect(35, 0, 31, 21));
        ramUseLabel = new QLabel(widget_3);
        ramUseLabel->setObjectName(QString::fromUtf8("ramUseLabel"));
        ramUseLabel->setGeometry(QRect(100, 0, 61, 21));

        horizontalLayout_3->addWidget(widget_3);


        gridLayout->addWidget(widget_5, 2, 0, 1, 3);

        toolFrame = new QFrame(centralwidget);
        toolFrame->setObjectName(QString::fromUtf8("toolFrame"));
        sizePolicy3.setHeightForWidth(toolFrame->sizePolicy().hasHeightForWidth());
        toolFrame->setSizePolicy(sizePolicy3);
        toolFrame->setMinimumSize(QSize(30, 0));
        toolFrame->setFrameShape(QFrame::StyledPanel);
        toolFrame->setFrameShadow(QFrame::Raised);
        toolFrame->setLineWidth(2);
        curTypeButton1 = new QPushButton(toolFrame);
        curTypeButton1->setObjectName(QString::fromUtf8("curTypeButton1"));
        curTypeButton1->setGeometry(QRect(0, 0, 30, 30));
        curTypeButton1->setAutoFillBackground(false);
        curTypeButton1->setStyleSheet(QString::fromUtf8(""));
        curTypeButton1->setCheckable(true);
        curTypeButton1->setChecked(false);
        curTypeButton1->setAutoDefault(false);
        curTypeButton1->setFlat(false);
        curTypeButton2 = new QPushButton(toolFrame);
        curTypeButton2->setObjectName(QString::fromUtf8("curTypeButton2"));
        curTypeButton2->setGeometry(QRect(0, 30, 30, 30));
        curTypeButton2->setStyleSheet(QString::fromUtf8(""));
        curTypeButton2->setCheckable(true);
        curTypeButton3 = new QPushButton(toolFrame);
        curTypeButton3->setObjectName(QString::fromUtf8("curTypeButton3"));
        curTypeButton3->setGeometry(QRect(0, 60, 30, 30));
        curTypeButton3->setStyleSheet(QString::fromUtf8(""));
        curTypeButton3->setCheckable(true);
        curTypeButton4 = new QPushButton(toolFrame);
        curTypeButton4->setObjectName(QString::fromUtf8("curTypeButton4"));
        curTypeButton4->setGeometry(QRect(0, 90, 30, 30));
        curTypeButton4->setCheckable(true);

        gridLayout->addWidget(toolFrame, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 807, 21));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_7 = new QMenu(menu);
        menu_7->setObjectName(QString::fromUtf8("menu_7"));
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        menu_3 = new QMenu(menubar);
        menu_3->setObjectName(QString::fromUtf8("menu_3"));
        menu_4 = new QMenu(menubar);
        menu_4->setObjectName(QString::fromUtf8("menu_4"));
        menu_5 = new QMenu(menubar);
        menu_5->setObjectName(QString::fromUtf8("menu_5"));
        menu_6 = new QMenu(menubar);
        menu_6->setObjectName(QString::fromUtf8("menu_6"));
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_2->menuAction());
        menubar->addAction(menu_3->menuAction());
        menubar->addAction(menu_4->menuAction());
        menubar->addAction(menu_5->menuAction());
        menubar->addAction(menu_6->menuAction());
        menu->addAction(menu_7->menuAction());
        menu_7->addAction(exportMapImage);
        menu_7->addAction(exportNowStaImage);
        menu_7->addAction(exportAllStaImage);
        menu_2->addAction(modelnew);
        menu_2->addAction(modelSet);
        menu_6->addAction(useDoc);

        retranslateUi(MainWindow);

        curTypeButton1->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\347\276\244\344\275\223\346\250\241\346\213\237\345\231\250", nullptr));
#if QT_CONFIG(whatsthis)
        MainWindow->setWhatsThis(QCoreApplication::translate("MainWindow", "<html><head/><body><p>\345\274\200\345\247\213</p></body></html>", nullptr));
#endif // QT_CONFIG(whatsthis)
        modelSet->setText(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256", nullptr));
        modelnew->setText(QCoreApplication::translate("MainWindow", "\346\226\260\345\273\272", nullptr));
        useDoc->setText(QCoreApplication::translate("MainWindow", "\344\275\277\347\224\250\346\226\207\346\241\243", nullptr));
        exportMapImage->setText(QCoreApplication::translate("MainWindow", "\345\257\274\345\207\272\345\234\260\345\233\276\344\270\272\345\233\276\347\211\207", nullptr));
        exportNowStaImage->setText(QCoreApplication::translate("MainWindow", "\345\257\274\345\207\272\347\273\237\350\256\241\345\233\276(\345\275\223\345\211\215\347\212\266\346\200\201)", nullptr));
        exportAllStaImage->setText(QCoreApplication::translate("MainWindow", "\345\257\274\345\207\272\347\273\237\350\256\241\345\233\276(\345\205\250\347\212\266\346\200\201)", nullptr));
        nowTimeLabel->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        runTimeLabel->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
#if QT_CONFIG(whatsthis)
        nextFrameButton->setWhatsThis(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:14pt;\">\344\270\213\344\270\200\345\270\247</span></p></body></html>", nullptr));
#endif // QT_CONFIG(whatsthis)
        nextFrameButton->setText(QCoreApplication::translate("MainWindow", "\302\273", nullptr));
#if QT_CONFIG(whatsthis)
        lastFrameButton->setWhatsThis(QCoreApplication::translate("MainWindow", "<html><head/><body><p>\344\270\212\344\270\200\345\270\247</p></body></html>", nullptr));
#endif // QT_CONFIG(whatsthis)
        lastFrameButton->setText(QCoreApplication::translate("MainWindow", "\302\253", nullptr));
        speedShowLabel->setText(QCoreApplication::translate("MainWindow", "10", nullptr));
        speedShowlabel2->setText(QCoreApplication::translate("MainWindow", "\345\270\247/s", nullptr));
        startPushButton->setText(QCoreApplication::translate("MainWindow", "\342\226\266", nullptr));
        resetButton->setText(QString());
        operationTypeCombo->setItemText(0, QCoreApplication::translate("MainWindow", "=", nullptr));
        operationTypeCombo->setItemText(1, QCoreApplication::translate("MainWindow", "+", nullptr));

        intervalSymbolLable->setText(QCoreApplication::translate("MainWindow", "\357\275\236", nullptr));
        randButton->setText(QCoreApplication::translate("MainWindow", "\351\232\217\346\234\272", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "X:", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Y:", nullptr));
        QTableWidgetItem *___qtablewidgetitem = stateTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "\347\212\266\346\200\201\345\200\274", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = stateTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "\345\244\207\346\263\250", nullptr));
        checkBox->setText(QCoreApplication::translate("MainWindow", "\345\217\252\350\257\273", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "ms", nullptr));
        timeSpend->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\347\272\277\347\250\213", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "CPU", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "\345\206\205\345\255\230", nullptr));
        cpuUseLabel->setText(QCoreApplication::translate("MainWindow", "1%", nullptr));
        ramUseLabel->setText(QCoreApplication::translate("MainWindow", "20MB", nullptr));
        curTypeButton1->setText(QString());
        curTypeButton2->setText(QString());
        curTypeButton3->setText(QString());
        curTypeButton4->setText(QString());
        menu->setTitle(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266", nullptr));
        menu_7->setTitle(QCoreApplication::translate("MainWindow", "\345\257\274\345\207\272", nullptr));
        menu_2->setTitle(QCoreApplication::translate("MainWindow", "\346\250\241\345\236\213", nullptr));
        menu_3->setTitle(QCoreApplication::translate("MainWindow", "\346\223\215\344\275\234", nullptr));
        menu_4->setTitle(QCoreApplication::translate("MainWindow", "\347\273\237\350\256\241", nullptr));
        menu_5->setTitle(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256", nullptr));
        menu_6->setTitle(QCoreApplication::translate("MainWindow", "\345\270\256\345\212\251", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
