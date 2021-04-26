#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QDialog>
#include "src/controller.h"
#include "modelsetting.h"

namespace Ui {
class CodeEditor;
}

class CodeEditor : public QDialog
{
    Q_OBJECT

public:
    explicit CodeEditor(QWidget *parent = nullptr,ModelSetting *modelSetting = nullptr,
                        Controller *controller = nullptr,int index=0);
    ~CodeEditor();

public:
    int index;

private slots:
//    void on_buttonBox_accepted();

    void on_CodeEditor_finished(int result);

private:
    void accept();
    Ui::CodeEditor *ui;
    ModelSetting *modelSetting;
    Controller *controller;
};

#endif // CODEEDITOR_H
