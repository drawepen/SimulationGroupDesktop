#ifndef MODELSETTING_H
#define MODELSETTING_H

#include <QDialog>
#include "src/controller.h"
#include "mainwindow.h"

namespace Ui {
class ModelSetting;
}

class ModelSetting : public QDialog
{
    Q_OBJECT

public:
    explicit ModelSetting(QWidget *parent = nullptr,MainWindow *mainWindow = nullptr);
    ~ModelSetting();
    void paintEvent(QPaintEvent *event);
    void setActionTableText(int row,QString text);
    QString actionTableText(int row);
public:
    vector<int *> codeEditorPtrs;

private slots:
    void on_comboBox_activated(int index);

    void on_cellRowNum_valueChanged(int arg1);

    void on_cellColNum_valueChanged(int arg1);

    void on_buttonBox_accepted();

    void on_addActionButton_clicked();

    void on_buttonBox_rejected();

    void on_actionTable_cellClicked(int row, int column);

private:
    Ui::ModelSetting *ui;
    MainWindow *mainWindow;
    Controller *controller;
};

#endif // MODELSETTING_H
