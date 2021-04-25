/********************************************************************************
** Form generated from reading UI file 'CodeEditor.ui'
**
** Created by: Qt User Interface Compiler version 6.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CODEEDITOR_H
#define UI_CODEEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CodeEditor
{
public:
    QVBoxLayout *verticalLayout;
    QTextEdit *codeText;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *CodeEditor)
    {
        if (CodeEditor->objectName().isEmpty())
            CodeEditor->setObjectName(QString::fromUtf8("CodeEditor"));
        CodeEditor->resize(400, 300);
        verticalLayout = new QVBoxLayout(CodeEditor);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        codeText = new QTextEdit(CodeEditor);
        codeText->setObjectName(QString::fromUtf8("codeText"));

        verticalLayout->addWidget(codeText);

        buttonBox = new QDialogButtonBox(CodeEditor);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(CodeEditor);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, CodeEditor, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, CodeEditor, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(CodeEditor);
    } // setupUi

    void retranslateUi(QDialog *CodeEditor)
    {
        CodeEditor->setWindowTitle(QCoreApplication::translate("CodeEditor", "Dialog", nullptr));
        codeText->setHtml(QCoreApplication::translate("CodeEditor", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CodeEditor: public Ui_CodeEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CODEEDITOR_H
