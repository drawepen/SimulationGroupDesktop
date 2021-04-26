#include "modelsetting.h"
#include "ui_modelsetting.h"
#include "CodeEditor.h"
#include <QPainter>
#include <QAbstractItemView>
#include <QMessageBox>

int oldCellRowNum,oldCellColNum;
ModelSetting::ModelSetting(QWidget *parent,MainWindow *mainWindow) :
    QDialog(parent),
    ui(new Ui::ModelSetting)
{
    ui->setupUi(this);
    this->mainWindow=mainWindow;
    this->controller= &mainWindow->controller;
    ui->cellRowNum->setValue(controller->getCellRowNum());
    ui->cellColNum->setValue(controller->getCellColNum());
    oldCellRowNum=controller->getCellRowNum();
    oldCellColNum=controller->getCellColNum();
    //设置
    ui->actionTable->setColumnWidth(0,240);
    ui->actionTable->setColumnWidth(1,50);
    ui->actionTable->verticalHeader()->setMinimumWidth(20);
}

ModelSetting::~ModelSetting()
{
    delete ui;
}

//绘图展示样例

void ModelSetting::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    //设置网格颜色
    QPen pen(Qt::gray);
    painter.setPen(pen);

    //以label左上角为原点
    painter.translate(ui->showView->x(),ui->showView->y());

    //清空画布
    QBrush brush(Qt::white,Qt::SolidPattern);
    painter.setBrush(brush);
    painter.drawRect(0,0,ui->showView->width()-1,ui->showView->height()-1);

    //绘制网格
    int cellWidthNum=7,cellHeightNum=7;
    int cellWidth=ui->showView->width()/cellWidthNum,cellHeight=ui->showView->width()/cellWidthNum;
    cellWidth=cellHeight=std::min(cellWidth,cellHeight);
    for(int x=0;x<=cellWidthNum;x++)
    {
        painter.drawLine(x*cellWidth,0,x*cellWidth,cellHeightNum*cellHeight);
    }
    for(int y=0;y<=cellHeightNum;y++)
    {
        painter.drawLine(0,y*cellHeight,cellWidthNum*cellWidth,y*cellHeight);
    }

    //绘制细胞
    int cellX=3,cellY=3;

    brush.setColor(Qt::black);
    painter.setBrush(brush);

    for(std::pair<int,int> cn:controller->getNowModelNeighborRule()){
        int x=cellX+cn.first,y=cellY+cn.second;
        painter.drawRect(x*cellWidth,y*cellHeight,cellWidth,cellHeight);
    }

    brush.setColor(Qt::red);
    painter.setBrush(brush);
    painter.drawRect(cellX*cellWidth,cellY*cellHeight,cellWidth,cellHeight);

    painter.end();
}

void ModelSetting::on_comboBox_activated(int index)
{
    if(index<3){
        controller->setModelNeighborRule(index);
    }else{

    }
    update();
}

void ModelSetting::on_cellRowNum_valueChanged(int arg1)
{
    controller->setCellNum({arg1,ui->cellColNum->value()});
}

void ModelSetting::on_cellColNum_valueChanged(int arg1)
{
    controller->setCellNum({ui->cellRowNum->value(),arg1});
}

void ModelSetting::on_buttonBox_accepted()
{
    if(controller->getCellColNum()!=oldCellColNum || controller->getCellRowNum()!=oldCellRowNum){
        controller->init();
        mainWindow->reShowMap();
    }
}

//设置行为规则
void ModelSetting::on_addActionButton_clicked()
{

    ui->addActionButton->setGeometry(ui->addActionButton->x(),ui->addActionButton->y()+30,
                                     ui->addActionButton->width(),ui->addActionButton->height());

    int rowIndex = ui->actionTable->rowCount();
    ui->actionTable->setRowCount(rowIndex + 1);

    QTableWidgetItem *item0=new QTableWidgetItem("编辑");
    QTableWidgetItem *item1=new QTableWidgetItem("删除");
    item1->setForeground(QBrush(Qt::red));
    item0->setTextAlignment(Qt::AlignCenter);
    item1->setTextAlignment(Qt::AlignCenter);
    item0->setFlags(item0->flags() & (~Qt::ItemIsEditable));
    item1->setFlags(item1->flags() & (~Qt::ItemIsEditable));
    ui->actionTable->setItem(rowIndex,0,item0);//没有默认QTableWidgetItem，需要先添加
    ui->actionTable->setItem(rowIndex,1,item1);
}

void ModelSetting::on_buttonBox_rejected()
{
    if(controller->getCellColNum()!=oldCellColNum || controller->getCellRowNum()!=oldCellRowNum){
        controller->setCellNum({oldCellRowNum,oldCellColNum});
    }
}

void ModelSetting::on_actionTable_cellClicked(int row, int column)
{
    if(column==0){
        if(codeEditorPtrs.size()>row && codeEditorPtrs[row]!=nullptr){
            ((CodeEditor*)codeEditorPtrs[row])->raise();
        }else{
            CodeEditor *codeEditor=new CodeEditor(nullptr,this,controller,row);
            codeEditor->setAttribute(Qt::WA_DeleteOnClose);
//            codeEditor->setWindowModality(Qt::ApplicationModal);//在关闭当前窗口前无法操作其他窗口
            while(codeEditorPtrs.size() <= row){
                codeEditorPtrs.push_back(nullptr);
            }
            codeEditorPtrs[row]=(int*)(codeEditor);
            codeEditor->show();
        }
    }else if(column==1){
        QMessageBox::StandardButton btn = QMessageBox::question(this, "提示", "确定要删除吗?", QMessageBox::Yes|QMessageBox::No);
        if (btn == QMessageBox::Yes) {
            ui->actionTable->removeRow(row);
            ui->addActionButton->setGeometry(ui->addActionButton->x(),ui->addActionButton->y()-30,
                                             ui->addActionButton->width(),ui->addActionButton->height());
            if(row<codeEditorPtrs.size() && codeEditorPtrs[row]!=nullptr){
                ((CodeEditor*)codeEditorPtrs[row])->index=-1;
                codeEditorPtrs[row]=nullptr;
            }
            for(int i=row+1;i<codeEditorPtrs.size();++i){
                if(codeEditorPtrs[i]!=nullptr){
                    ((CodeEditor*)codeEditorPtrs[i])->index--;
                    codeEditorPtrs[i-1]=codeEditorPtrs[i];
                    codeEditorPtrs[i]=nullptr;
                }
            }
        }
        //TODO
    }
}

void ModelSetting::setActionTableText(int row,QString text){
    if(row==-1){
        row=ui->actionTable->rowCount();
        on_addActionButton_clicked();
    }
    ui->actionTable->item(row,0)->setText(text);
    controller->setCellAction(row,text.toStdString());
}

QString ModelSetting::actionTableText(int row){
    return ui->actionTable->item(row,0)->text();
}
