#ifndef MODELEXAMPLES_H
#define MODELEXAMPLES_H
#include "src/controller.h"
#include "mainwindow.h"
#include <QDialog>

namespace Ui {
class ModelExamples;
}

class ModelExamples : public QDialog
{
    Q_OBJECT

public:
    explicit ModelExamples(QWidget *parent = nullptr,MainWindow *mainWindow=nullptr);
    ~ModelExamples();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::ModelExamples *ui;
    Controller *controller;
    MainWindow *mainWindow;
};

#endif // MODELEXAMPLES_H
