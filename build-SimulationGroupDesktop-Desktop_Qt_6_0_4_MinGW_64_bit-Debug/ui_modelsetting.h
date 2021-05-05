/********************************************************************************
** Form generated from reading UI file 'modelsetting.ui'
**
** Created by: Qt User Interface Compiler version 6.0.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODELSETTING_H
#define UI_MODELSETTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ModelSetting
{
public:
    QDialogButtonBox *buttonBox;
    QToolBox *toolBox;
    QWidget *cellMapping;
    QWidget *widget_2;
    QLabel *label;
    QLabel *label_2;
    QSpinBox *cellRowNum;
    QLabel *label_3;
    QSpinBox *cellColNum;
    QWidget *widget_3;
    QLabel *label_13;
    QWidget *cellNeighbor;
    QWidget *horizontalWidget;
    QWidget *widget;
    QComboBox *comboBox;
    QWidget *page;
    QPushButton *addActionButton;
    QTableWidget *actionTable;
    QLabel *showView;

    void setupUi(QDialog *ModelSetting)
    {
        if (ModelSetting->objectName().isEmpty())
            ModelSetting->setObjectName(QString::fromUtf8("ModelSetting"));
        ModelSetting->resize(577, 419);
        buttonBox = new QDialogButtonBox(ModelSetting);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(10, 390, 561, 21));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        toolBox = new QToolBox(ModelSetting);
        toolBox->setObjectName(QString::fromUtf8("toolBox"));
        toolBox->setGeometry(QRect(9, 9, 371, 351));
        cellMapping = new QWidget();
        cellMapping->setObjectName(QString::fromUtf8("cellMapping"));
        cellMapping->setGeometry(QRect(0, 0, 371, 273));
        widget_2 = new QWidget(cellMapping);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setGeometry(QRect(0, 10, 261, 41));
        label = new QLabel(widget_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 54, 21));
        label_2 = new QLabel(widget_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(90, 10, 16, 21));
        cellRowNum = new QSpinBox(widget_2);
        cellRowNum->setObjectName(QString::fromUtf8("cellRowNum"));
        cellRowNum->setGeometry(QRect(110, 10, 42, 22));
        cellRowNum->setMinimum(7);
        cellRowNum->setMaximum(500);
        cellRowNum->setValue(20);
        label_3 = new QLabel(widget_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(160, 10, 31, 21));
        cellColNum = new QSpinBox(widget_2);
        cellColNum->setObjectName(QString::fromUtf8("cellColNum"));
        cellColNum->setGeometry(QRect(190, 10, 42, 22));
        cellColNum->setMinimum(7);
        cellColNum->setMaximum(500);
        cellColNum->setValue(10);
        widget_3 = new QWidget(cellMapping);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        widget_3->setGeometry(QRect(0, 60, 261, 41));
        label_13 = new QLabel(widget_3);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(10, 0, 54, 41));
        label_13->setWordWrap(true);
        toolBox->addItem(cellMapping, QString::fromUtf8("\345\205\203\350\203\236\346\230\240\345\260\204"));
        cellNeighbor = new QWidget();
        cellNeighbor->setObjectName(QString::fromUtf8("cellNeighbor"));
        cellNeighbor->setGeometry(QRect(0, 0, 371, 273));
        horizontalWidget = new QWidget(cellNeighbor);
        horizontalWidget->setObjectName(QString::fromUtf8("horizontalWidget"));
        horizontalWidget->setGeometry(QRect(10, 0, 411, 210));
        widget = new QWidget(horizontalWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(9, 16, 89, 171));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        comboBox = new QComboBox(widget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(0, 0, 89, 22));
        sizePolicy.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy);
        toolBox->addItem(cellNeighbor, QString::fromUtf8("\345\205\203\350\203\236\351\202\273\345\261\205\350\247\204\345\210\231"));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        page->setGeometry(QRect(0, 0, 371, 273));
        addActionButton = new QPushButton(page);
        addActionButton->setObjectName(QString::fromUtf8("addActionButton"));
        addActionButton->setGeometry(QRect(10, 20, 20, 30));
        actionTable = new QTableWidget(page);
        if (actionTable->columnCount() < 2)
            actionTable->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        actionTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        actionTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        actionTable->setObjectName(QString::fromUtf8("actionTable"));
        actionTable->setGeometry(QRect(10, 0, 321, 251));
        actionTable->setLineWidth(0);
        actionTable->setAutoScrollMargin(16);
        actionTable->setGridStyle(Qt::SolidLine);
        actionTable->setSortingEnabled(false);
        actionTable->horizontalHeader()->setCascadingSectionResizes(false);
        actionTable->horizontalHeader()->setMinimumSectionSize(2);
        actionTable->horizontalHeader()->setDefaultSectionSize(100);
        actionTable->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        actionTable->horizontalHeader()->setStretchLastSection(false);
        actionTable->verticalHeader()->setCascadingSectionResizes(false);
        actionTable->verticalHeader()->setMinimumSectionSize(30);
        actionTable->verticalHeader()->setDefaultSectionSize(30);
        actionTable->verticalHeader()->setProperty("showSortIndicator", QVariant(false));
        actionTable->verticalHeader()->setStretchLastSection(false);
        toolBox->addItem(page, QString::fromUtf8("\345\205\203\350\203\236\350\241\214\344\270\272\350\247\204\345\210\231"));
        actionTable->raise();
        addActionButton->raise();
        showView = new QLabel(ModelSetting);
        showView->setObjectName(QString::fromUtf8("showView"));
        showView->setGeometry(QRect(390, 30, 171, 181));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(showView->sizePolicy().hasHeightForWidth());
        showView->setSizePolicy(sizePolicy1);

        retranslateUi(ModelSetting);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, ModelSetting, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, ModelSetting, qOverload<>(&QDialog::reject));

        toolBox->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(ModelSetting);
    } // setupUi

    void retranslateUi(QDialog *ModelSetting)
    {
        ModelSetting->setWindowTitle(QCoreApplication::translate("ModelSetting", "\346\250\241\345\236\213\350\256\276\347\275\256", nullptr));
        label->setText(QCoreApplication::translate("ModelSetting", "\345\205\203\350\203\236\346\225\260\351\207\217", nullptr));
        label_2->setText(QCoreApplication::translate("ModelSetting", "\350\241\214", nullptr));
        label_3->setText(QCoreApplication::translate("ModelSetting", "\303\227\345\210\227", nullptr));
        label_13->setText(QCoreApplication::translate("ModelSetting", "\345\205\203\350\203\236\347\212\266\346\200\201\345\233\276\345\275\242\346\230\240\345\260\204", nullptr));
        toolBox->setItemText(toolBox->indexOf(cellMapping), QCoreApplication::translate("ModelSetting", "\345\205\203\350\203\236\346\230\240\345\260\204", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("ModelSetting", "\345\206\257\350\257\272\344\276\235\346\233\274\345\236\213", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("ModelSetting", "\346\221\251\345\260\224\345\236\213", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("ModelSetting", "\346\211\251\345\261\225\346\221\251\345\260\224\345\236\213", nullptr));

        toolBox->setItemText(toolBox->indexOf(cellNeighbor), QCoreApplication::translate("ModelSetting", "\345\205\203\350\203\236\351\202\273\345\261\205\350\247\204\345\210\231", nullptr));
        addActionButton->setText(QCoreApplication::translate("ModelSetting", "\357\274\213", nullptr));
        QTableWidgetItem *___qtablewidgetitem = actionTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ModelSetting", "\350\241\214\344\270\272\350\247\204\345\210\231", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = actionTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ModelSetting", "\346\223\215\344\275\234", nullptr));
        toolBox->setItemText(toolBox->indexOf(page), QCoreApplication::translate("ModelSetting", "\345\205\203\350\203\236\350\241\214\344\270\272\350\247\204\345\210\231", nullptr));
        showView->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ModelSetting: public Ui_ModelSetting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODELSETTING_H
