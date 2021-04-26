#include "CodeEditor.h"
#include "ui_CodeEditor.h"
#include <QMessageBox>

CodeEditor::CodeEditor(QWidget *parent,ModelSetting *modelSetting,Controller *controller,int index) :
    QDialog(parent),
    ui(new Ui::CodeEditor)
{
    ui->setupUi(this);
    this->index=index;
    this->modelSetting=modelSetting;
    this->controller=controller;
    ui->codeText->setText(modelSetting->actionTableText(index));
}

CodeEditor::~CodeEditor()
{
    delete ui;
}

void CodeEditor::accept()
{
    if(index<0){
        QMessageBox::StandardButton btn = QMessageBox::question(this, "提示", "该项已被删除，是否添加?", QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
        if (btn == QMessageBox::Yes) {
            modelSetting->setActionTableText(-1,ui->codeText->toPlainText());
        }else if(btn == QMessageBox::Cancel){
            return;
        }
    }else{
        modelSetting->setActionTableText(index,ui->codeText->toPlainText());
    }
    QDialog::accept();
}

void CodeEditor::on_CodeEditor_finished(int result)
{
    if(index>=0 && (CodeEditor*)(modelSetting->codeEditorPtrs[index])==this){
        modelSetting->codeEditorPtrs[index]=nullptr;
    }
}
