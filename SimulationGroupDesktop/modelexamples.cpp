#include "modelexamples.h"
#include "ui_modelexamples.h"

ModelExamples::ModelExamples(QWidget *parent,MainWindow *mainWindow) :
    QDialog(parent),
    ui(new Ui::ModelExamples)
{
    ui->setupUi(this);
    this->mainWindow=mainWindow;
    controller=&(mainWindow->controller);
    for(std::string name:controller->modelsFromDb()){
        ui->comboBox->addItem(name.c_str());
    }
}

ModelExamples::~ModelExamples()
{
    delete ui;
}

void ModelExamples::on_buttonBox_accepted()
{
    if(ui->tabWidget->currentIndex()==0){
        controller->newModel("");
    }else{
        controller->newModel(ui->comboBox->currentText().toStdString());
    }
    mainWindow->reShowMap();
}
