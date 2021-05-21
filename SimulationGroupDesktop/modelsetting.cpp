#include "modelsetting.h"
#include "ui_modelsetting.h"
#include "CodeEditor.h"
#include <QPainter>
#include <QAbstractItemView>
#include <QMessageBox>
#include <QColorDialog>

ModelSetting::ModelSetting(QWidget *parent,MainWindow *mainWindow) :
    QDialog(parent),
    ui(new Ui::ModelSetting)
{
    ui->setupUi(this);
    this->mainWindow=mainWindow;
    this->controller= &mainWindow->controller;
    ui->cellRowNum->setValue(controller->getCellRowNum());
    ui->cellColNum->setValue(controller->getCellColNum());
    cellRowNum=controller->getCellRowNum();
    cellColNum=controller->getCellColNum();
    //元胞行为规则
    ui->actionTable->verticalHeader()->setMinimumWidth(20);
    ui->actionTable->setColumnWidth(0,240);
    ui->actionTable->setColumnWidth(1,ui->actionTable->width()-260-2);
    std::vector<std::string> &codes=controller->getActionCodes();
    for(std::string code:codes){
        on_addActionButton_clicked();
        setActionTableText(ui->actionTable->rowCount()-1,QString(code.c_str()));
    }
    //元胞交互规则
    controller->initTempNeighborRule();
    ui->comboBox->setCurrentIndex(controller->getModelNeighborRuleType());
    if(controller->getModelNeighborRuleType()<3){
        ui->label_4->setVisible(false);
        ui->showView->setCursor(Qt::ArrowCursor);
    }else{
        ui->label_4->setVisible(true);
        ui->showView->setCursor(Qt::PointingHandCursor);
    }

    //状态颜色映射
    ui->stateMapTable->verticalHeader()->setMinimumWidth(20);
    ui->stateMapTable->setColumnWidth(0,120);
    ui->stateMapTable->setColumnWidth(1,100);
    ui->stateMapTable->setColumnWidth(2,30);
    ui->stateMapTable->setColumnWidth(3,ui->stateMapTable->width()-270-2);
    ui->stateMapTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    std::vector<StateColor> &stateColors = controller->getState2Color();
    if(stateColors.size()>0){
        ui->addStateMapButton->setGeometry(ui->addStateMapButton->x(),ui->addStateMapButton->y()+30,
                                         ui->addStateMapButton->width(),ui->addStateMapButton->height());
        ui->stateMapTable->insertRow(0);
        QTableWidgetItem *item0=new QTableWidgetItem("默认");
        item0->setTextAlignment(Qt::AlignCenter);
        ui->stateMapTable->setItem(0,0,item0);
        QStringList stringList;
        stringList.append(tr("纯色"));//tr()翻译
        stringList.append(tr("斜线"));
        QComboBox *combobox=new QComboBox();
        combobox->addItems(stringList);
        ui->stateMapTable->setCellWidget(0,1,combobox);
        stateMapComboBoxs.push_back(combobox);
        ui->stateMapTable->setItem(0,2,new QTableWidgetItem());
        QTableWidgetItem *item1=new QTableWidgetItem("删除");
        item1->setTextAlignment(Qt::AlignCenter);
        item1->setBackgroundColor(Qt::gray);
        ui->stateMapTable->setItem(0,3,item1);

        stateMapComboBoxs[0]->setCurrentIndex(stateColors[0].type);
        ui->stateMapTable->item(0,2)->setBackgroundColor(QColor(stateColors[0].r,stateColors[0].g,stateColors[0].b));
    }
    for(int i=1;i<stateColors.size();++i){
        on_addStateMapButton_clicked();
        stateMapSpinBoxs[i*2-2]->setValue(stateColors[i].from);
        stateMapSpinBoxs[i*2-1]->setValue(stateColors[i].to);
        stateMapComboBoxs[i]->setCurrentIndex(stateColors[i].type);
        ui->stateMapTable->item(i,2)->setBackgroundColor(QColor(stateColors[i].r,stateColors[i].g,stateColors[i].b));
    }

    //多agent设置
    ui->moveableCheckBox->setChecked(controller->getCellMoveableSwitch());
    ui->freeSpaceCheckBox->setChecked(controller->getCellSpaceSwitch());
    ui->freeSpaceSpinBox->setValue(controller->getCellSpaceSize());

    ui->toolBox->setCurrentIndex(toolCurrentIndex);
    textChange=false;
    update();
}

ModelSetting::~ModelSetting()
{
    delete ui;
}

//绘图展示样例
void ModelSetting::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    //以label左上角为原点
    painter.translate(ui->showView->x(),ui->showView->y());
    if(toolCurrentIndex!=1){
        //清空画布
        QBrush brush(Qt::white,Qt::SolidPattern);
        painter.setBrush(brush);
        painter.drawRect(0,0,ui->showView->width()-1,ui->showView->height()-1);
        return;
    }
    //设置网格颜色
    QPen pen(Qt::gray);
    painter.setPen(pen);

    //清空画布
    QBrush brush(Qt::white,Qt::SolidPattern);
    painter.setBrush(brush);
    painter.drawRect(0,0,ui->showView->width()-1,ui->showView->height()-1);

    //绘制网格
    int cellColNum=7,cellRowNum=7;
    int cellWidth=ui->showView->width()/cellColNum,cellHeight=ui->showView->width()/cellColNum;
    cellWidth=cellHeight=std::min(cellWidth,cellHeight);
    for(int x=0;x<=cellColNum;x++)
    {
        painter.drawLine(x*cellWidth,0,x*cellWidth,cellRowNum*cellHeight);
    }
    for(int y=0;y<=cellRowNum;y++)
    {
        painter.drawLine(0,y*cellHeight,cellColNum*cellWidth,y*cellHeight);
    }

    //绘制细胞
    int cellCoreX=3,cellCoreY=3;

    brush.setColor(Qt::black);
    painter.setBrush(brush);

    for(std::pair<int,int> cn:controller->getTempNeighborRule()){
        int x=cellCoreX+cn.first,y=cellCoreY+cn.second;
        painter.drawRect(x*cellWidth,y*cellHeight,cellWidth,cellHeight);
    }

    brush.setColor(Qt::red);
    painter.setBrush(brush);
    painter.drawRect(cellCoreX*cellWidth,cellCoreY*cellHeight,cellWidth,cellHeight);
    //绘制特效
    if(toolCurrentIndex==1 && ui->comboBox->currentIndex()==3){
        QPoint point=ui->showView->mapFromGlobal(QCursor().pos());
        int cellX=point.x()/cellWidth;
        int cellY=point.y()/cellHeight;
        if(point.x()>=0 && cellX<cellColNum && point.y()>=0 && cellY<cellRowNum &&
                (cellX!=cellCoreX || cellY!=cellCoreY)){
            int mX=cellX*cellWidth,mY=cellY*cellHeight;
            //绘制元胞边界
            painter.setBrush(QBrush());
            painter.setPen(QPen(Qt::red, 2));
            int w=cellWidth,h=cellHeight,x=mX,y=mY;
            if(w>0 && w<4 && h>0 && h <4){
                x-=(4-w)/2;
                y-=(4-h)/2;
                w=h=4;
            }
            painter.drawRect(x,y,w,h);
            painter.setPen(QPen(Qt::white, 1));
            painter.drawRect(x+1,y+1,w-2,h-2);
            painter.drawRect(x-2,y-2,w+3,h+3);
        }
    }
    painter.end();
}

void ModelSetting::on_comboBox_activated(int index)
{
    if(index<3){
        ui->label_4->setVisible(false);
        ui->showView->setCursor(Qt::ArrowCursor);
    }else{
        ui->label_4->setVisible(true);
        ui->showView->setCursor(Qt::PointingHandCursor);
    }
    controller->setTempNeighborRule(index);
    update();
}

void ModelSetting::on_cellRowNum_valueChanged(int arg1)
{
    cellRowNum=arg1;
}

void ModelSetting::on_cellColNum_valueChanged(int arg1)
{
    cellColNum=arg1;
}

void ModelSetting::mouseDoubleClickEvent(QMouseEvent *e){
    if(toolCurrentIndex==1){
        int cellCoreX=3,cellCoreY=3;
        int cellColNum=7,cellRowNum=7;
        int cellWidth=ui->showView->width()/cellColNum,cellHeight=ui->showView->width()/cellRowNum;
        QPoint point=ui->showView->mapFromGlobal(QCursor().pos());
        int cellX=point.x()/cellWidth;
        int cellY=point.y()/cellHeight;
        if(point.x()>=0 && cellX<cellColNum && point.y()>=0 && cellY<cellRowNum &&
                (cellX!=cellCoreX || cellY!=cellCoreY)){
            controller->clickNeighbor(cellX-cellCoreX,cellY-cellCoreY);
            update();
        }
    }
}

void ModelSetting::mouseMoveEvent(QMouseEvent *event)
{
    if(toolCurrentIndex==1 && ui->comboBox->currentIndex()==3){
       update();
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

void ModelSetting::on_actionTable_cellClicked(int row, int column)
{
    if(column==0){
        if(codeEditorPtrs.size()>row && codeEditorPtrs[row]!=nullptr){
            ((CodeEditor*)codeEditorPtrs[row])->raise();
        }else{
            CodeEditor *codeEditor=new CodeEditor(nullptr,this,controller,row);
            codeEditor->setAttribute(Qt::WA_DeleteOnClose);
            codeEditor->setWindowModality(Qt::ApplicationModal);//在关闭当前窗口前无法操作其他窗口
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
            if(codeEditCounts.size()>row){
                codeEditCounts[row]=0;
            }
            for(int i=row+1;i<codeEditCounts.size();++i){
                codeEditCounts[i-1]=codeEditCounts[i];
            }
            if(codeEditCounts.size()>ui->actionTable->rowCount()){
                codeEditCounts.resize(ui->actionTable->rowCount());
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
    while (codeEditCounts.size() <= row) {
        codeEditCounts.push_back(0);
    }
    codeEditCounts[row]=1;
    ui->actionTable->item(row,0)->setText(text);
    textChange=true;
}

QString ModelSetting::actionTableText(int row){
    if(codeEditCounts.size() <= row || codeEditCounts[row]==0){
        return "";
    }
    return ui->actionTable->item(row,0)->text();
}

void ModelSetting::on_addStateMapButton_clicked()
{
    ui->addStateMapButton->setGeometry(ui->addStateMapButton->x(),ui->addStateMapButton->y()+30,
                                     ui->addStateMapButton->width(),ui->addStateMapButton->height());
    int row=ui->stateMapTable->rowCount();
    ui->stateMapTable->insertRow(row);
    QWidget *widget=new QWidget();
    QHBoxLayout *layout=new QHBoxLayout();
    layout->setMargin(0);
    widget->setLayout(layout);
    QSpinBox *spin1=new QSpinBox(),*spin2=new QSpinBox();
    spin1->setMinimum(INT32_MIN);spin1->setMaximum(INT32_MAX);
    spin2->setMinimum(INT32_MIN);spin2->setMaximum(INT32_MAX);
    layout->addWidget(spin1);
    layout->addWidget(new QLabel("～"));
    layout->addWidget(spin2);
    stateMapSpinBoxs.push_back(spin1);
    stateMapSpinBoxs.push_back(spin2);
    ui->stateMapTable->setCellWidget(row,0,widget);

    QStringList stringList;
    stringList.append(tr("纯色"));//tr()翻译
    stringList.append(tr("斜线"));
    QComboBox *combobox=new QComboBox();
    combobox->addItems(stringList);
    ui->stateMapTable->setCellWidget(row,1,combobox);
    stateMapComboBoxs.push_back(combobox);

    ui->stateMapTable->setItem(row,2,new QTableWidgetItem());
    QTableWidgetItem *item1=new QTableWidgetItem("删除");
    item1->setTextAlignment(Qt::AlignCenter);
    item1->setTextColor(Qt::red);
    ui->stateMapTable->setItem(row,3,item1);
}

void ModelSetting::on_stateMapTable_cellClicked(int row, int column)
{
    if(column==2){
        QColorDialog colorD;//调出颜色选择器对话框
        ui->stateMapTable->item(row,2)->setBackgroundColor(colorD.getRgba());
        //TODO选中时颜色设置
    }else if(column==3){
        if(row<=0){
            QMessageBox::question(this, "提示", "默认映射不可删除", QMessageBox::Ok);
            return;
        }
        QMessageBox::StandardButton btn = QMessageBox::question(this, "提示", "确定要删除吗?", QMessageBox::Yes|QMessageBox::No);
        if (btn == QMessageBox::Yes) {
            ui->stateMapTable->removeRow(row);
            ui->addStateMapButton->setGeometry(ui->addStateMapButton->x(),ui->addStateMapButton->y()-30,
                                             ui->addStateMapButton->width(),ui->addStateMapButton->height());
        }
    }
}
//多agent

//确认或取消
void ModelSetting::on_buttonBox_accepted()
{
    bool change=false;
    if(textChange){
        std::vector<std::string> codes;
        for(int i=0,len=ui->actionTable->rowCount();i<len;++i){
            QString text=actionTableText(i);
            if(text!=""){
                codes.push_back(text.toStdString());
            }
        }
        if(codes.size()>0){
            controller->setCellAction(codes);
        }
    }
    if(controller->getCellColNum()!=cellColNum || controller->getCellRowNum()!=cellRowNum){
        controller->setCellNum({cellRowNum,cellColNum});
        change=true;
    }
    //多agent
    controller->setCellMoveableSwitch(ui->moveableCheckBox->checkState()==Qt::Checked);
    controller->setCellSpaceSwitch(ui->freeSpaceCheckBox->checkState()==Qt::Checked);
    if(controller->getCellSpaceSize()!=ui->freeSpaceSpinBox->value()){
        controller->setCellSpaceSize(ui->freeSpaceSpinBox->value());
    }

    //元胞映射设置
    std::vector<StateColor> state2Color;
    QColor color=ui->stateMapTable->item(0,2)->backgroundColor();
    state2Color.push_back(StateColor(INT32_MIN,INT32_MAX,color.red(),color.green(),color.blue(),stateMapComboBoxs[0]->currentIndex()));
    for(int i=1;i<ui->stateMapTable->rowCount();++i){
        color=ui->stateMapTable->item(i,2)->backgroundColor();
        state2Color.push_back(StateColor(stateMapSpinBoxs[i*2-2]->value(),stateMapSpinBoxs[i*2-1]->value(),
                color.red(),color.green(),color.blue(),stateMapComboBoxs[i]->currentIndex()));
    }
    controller->setState2Color(state2Color);
    //元胞交互设置
    if(ui->comboBox->currentIndex()==3||controller->getModelNeighborRuleType()!=ui->comboBox->currentIndex()){
        controller->setModelNeighborRule(ui->comboBox->currentIndex());
    }
    if(change){
        controller->init();
        mainWindow->reShowMap();
    }
}

void ModelSetting::on_buttonBox_rejected()
{

}

void ModelSetting::on_toolBox_currentChanged(int index)
{
    toolCurrentIndex=index;
    update();
}
