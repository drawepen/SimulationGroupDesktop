#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "modelsetting.h"
#include <math.h>
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QPixmap>
#include "src/data/model.h" //???引用头文件报错找不到方法[已解决：makefile文件中被引用的文件要在前声明]


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setMouseTracking(true);  //激活鼠标追踪
    ui->centralwidget->setMouseTracking(true);
    ui->mapShowFrame->setMouseTracking(true);

    timer.stop();
    connect(&timer,&QTimer::timeout,this,&MainWindow::timerUpdate);

    ui->speedSlider->setValue(controller.getSpeed());
    ui->speedShowLabel->setText(QString::number(controller.getSpeed(), 10));
    //操作
    ui->operationTypeCombo->setCurrentIndex(controller.getOperationType());
    ui->operationValueSpin->setValue(controller.getOperationValue());
    ui->operationValueSpin2->setValue(controller.getOperationValue2());
    ui->intervalSymbolLable->setVisible(controller.getOperationType()==2);
    ui->operationValueSpin2->setVisible(controller.getOperationType()==2);
    ui->randButton->setChecked(false);

    QIcon icon1,icon2,icon3,icon4;
    icon1.addFile(tr(":/image/cur/resources/resizeApi1.ico"));
    ui->curTypeButton1->setIcon(icon1);
    ui->curTypeButton1->setIconSize(QSize(26,26));
    icon2.addFile(tr(":/image/cur/resources/cur_set.ico"));
    ui->curTypeButton2->setIcon(icon2);
    ui->curTypeButton2->setIconSize(QSize(26,26));
    icon3.addFile(tr(":/image/cur/resources/resizeApi3.ico"));
    ui->curTypeButton3->setIcon(icon3);
    ui->curTypeButton3->setIconSize(QSize(26,26));
    icon4.addFile(tr(":/image/cur/resources/cur_enlarge.ico"));
    ui->curTypeButton4->setIcon(icon4);
    ui->curTypeButton4->setIconSize(QSize(26,26));

    ui->curTypeButton1->setChecked(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QPoint point=event->pos();
    if(event->button()==Qt::LeftButton)
    {
        QPoint point1=point - ui->centralwidget->pos()- ui->mapShowFrame->pos();
        pointEvent(point1);
        //窗口缩放
        winZoomType=0;
        switch (1) {
        case 1:{
            QPoint point1=point-ui->centralwidget->pos()-
                    ui->mapShowFrame->pos()-ui->widget_6->pos();
            int x=point1.x(),y=point1.y();
            if (x>=0 && x<ui->widget_6->width() && y>=0 && y<ui->widget_6->height())
            {
                winZoomType=1;
                winZoomOriX=point.x();
                winZoomOriY=point.y();
                break;
            }
        }
        }
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    QPoint point=event->pos() - ui->centralwidget->pos() -ui->mapShowFrame->pos();
    if(event->buttons() & Qt::LeftButton)
    {
        pointEvent(point);
        //窗口缩放
        switch (winZoomType) {
        case 1:{
            QPoint point=event->pos();
            int relX=point.x()-winZoomOriX;
            if(relX!=0 && !(relX<0 && ui->mapShowFrame->width()<=ui->mapShowFrame->minimumWidth())
                    && !(relX>0 && ui->frame->minimumWidth()<=0)){
                winZoomOriX=point.x();
                winZoomOriY=point.y();
                ui->frame->setMinimumWidth(ui->frame->minimumWidth()-relX);
            }
        }
            break;
        }
    }
    int x=point.x();
    int y=point.y();
    int cellWidth,cellHeight;
    cellWidth=ui->mapShowFrame->width()/controller.getCellColNum();
    cellHeight=ui->mapShowFrame->height()/controller.getCellRowNum();
    cellWidth=cellHeight=min(cellWidth,cellHeight);
    int cellX=x/cellWidth;
    int cellY=y/cellHeight;
    if(x>=0 && cellX<controller.getCellColNum() && cellX!=this->cellX)
    {
        ui->cellXSpin->setValue(cellX);
    }
    if(y>=0 && cellY<controller.getCellRowNum() && cellY!=this->cellY)
    {
        ui->cellYSpin->setValue(cellY);
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event){
    winZoomType=0;
}

void MainWindow::timerUpdate()
{
    controller.runOneFrame();
    ui->timeSpend->setText(QString().setNum(controller.getTimeSpend()*1.0/1000,'f',3));
    updateProgress();
}

//绘图
void MainWindow::paintEvent(QPaintEvent *)
{
    int cellWidthNum,cellHeightNum,cellWidth,cellHeight;
    cellWidthNum=controller.getCellColNum();
    cellHeightNum=controller.getCellRowNum();
    cellWidth=ui->mapShowFrame->width()/cellWidthNum;
    cellHeight=ui->mapShowFrame->height()/cellHeightNum;
    cellWidth=cellHeight=min(cellWidth,cellHeight);

    QPainter painter(this);

    //设置网格颜色
    QPen pen(Qt::gray);
    painter.setPen(pen);

    //以label左上角为原点
    painter.translate(ui->centralwidget->x()+ui->mapShowFrame->x(),
                      ui->centralwidget->y()+ui->mapShowFrame->y());

    //清空画布
    QBrush brush(Qt::white,Qt::SolidPattern);
    painter.setBrush(brush);
    painter.drawRect(0,0,ui->mapShowFrame->width()-1,ui->mapShowFrame->height()-1);

    //绘制网格
    for(int x=0;x<=cellWidthNum;x++)
    {
        painter.drawLine(x*cellWidth,0,x*cellWidth,cellHeightNum*cellHeight);
    }
    for(int y=0;y<=cellHeightNum;y++)
    {
        painter.drawLine(0,y*cellHeight,cellWidthNum*cellWidth,y*cellHeight);
    }

    //绘制细胞
    brush.setColor(Qt::black);
    painter.setBrush(brush);
    for(int y=0;y<cellHeightNum;y++)
    {
        for(int x=0;x<cellWidthNum;x++)
        {
            if(controller.getState(x,y)>0){
                painter.drawRect(x*cellWidth,y*cellHeight,cellWidth,cellHeight);
            }
        }
    }

    painter.end();
}

//播放控件
void MainWindow::on_startPushButton_clicked()
{
    if(startButtion==1 || startButtion==3){
        timer.start(1000/controller.getSpeed());
        ui->startPushButton->setText("暂停");
        startButtion=2;
    }else if(startButtion==2){
        timer.stop();
        ui->startPushButton->setText("继续");
        startButtion=3;
    }
}

void MainWindow::on_speedSlider_valueChanged(int arg1)
{
    controller.setSpeed(ui->speedSlider->maximum()/(std::max(ui->speedSlider->maximum()-arg1,1))*arg1);
    ui->speedShowLabel->setText(QString::number(controller.getSpeed(), 10));
    if(timer.isActive()){
        timer.start(1000/controller.getSpeed());
    }
}

void MainWindow::on_nextFrameButton_clicked()
{
    controller.selfAddNowTime();
    if(controller.getNowTime()==controller.getRunTime()){
        ui->timeSpend->setText(QString().setNum(controller.getTimeSpend()*1.0/1000,'f',3));
    }
    updateProgress();
}

void MainWindow::on_lastFrameButton_clicked()
{
    controller.selfSubNowTime();
    updateProgress();
}

void MainWindow::on_progressSlider_valueChanged(int arg1)
{
    controller.setNowTime(arg1);
    ui->nowTimeLabel->setText(QString::number(controller.getNowTime(),10));
    update();
}

void MainWindow::updateProgress(){
    ui->runTimeLabel->setText(QString::number(controller.getRunTime(),10));
    ui->progressSlider->setMaximum(controller.getRunTime());
    ui->progressSlider->setValue(controller.getNowTime());
}

void MainWindow::on_modelset_triggered()
{
    if(startButtion==2){
        timer.stop();
        ui->startPushButton->setText("继续");
        startButtion=3;
    }

    ModelSetting *ms=new ModelSetting(nullptr,this);
    ms->setWindowModality(Qt::ApplicationModal);//在关闭当前窗口前无法操作其他窗口
    ms->show();

}

void MainWindow::reShowMap()
{
    ui->nowTimeLabel->setText(QString::number(controller.getNowTime(),10));
    ui->runTimeLabel->setText(QString::number(controller.getRunTime(),10));
    ui->progressSlider->setValue(controller.getNowTime());
}
//操作
void MainWindow::pointEvent(QPoint &point)
{
    if(winZoomType!=0){
        return;
    }
    int cellWidthNum,cellHeightNum,cellWidth,cellHeight;
    cellWidthNum=controller.getCellColNum();
    cellHeightNum=controller.getCellRowNum();
    cellWidth=ui->mapShowFrame->width()/cellWidthNum;
    cellHeight=ui->mapShowFrame->height()/cellHeightNum;
    cellWidth=cellHeight=min(cellWidth,cellHeight);

    int x=point.x();
    int y=point.y();
    int cellX=x/cellWidth;
    int cellY=y/cellHeight;
    if(x>=0 && cellX<cellWidthNum && y>=0 && cellY<cellHeightNum)
    {
        if(curType==2){
            controller.clickCell(cellX,cellY);
        }else if(curType==3){
            controller.allClick();
        }
        showState();
        update();
    }
}

void MainWindow::showState()
{
    int rowCount=ui->stateTable->rowCount();
    if(rowCount!=1){
        ui->stateTable->setRowCount(1);
        for(int i=0;i<1;++i){
            QTableWidgetItem *item=new QTableWidgetItem("-");
            item->setTextAlignment(Qt::AlignCenter);
            ui->stateTable->setItem(i,0,item);
        }
    }
    if(cellX>=0&&cellX<controller.getCellColNum() && cellY>=0 && cellY<=controller.getCellRowNum()){
        for(int i=0;i<1;++i){
            ui->stateTable->item(i,0)->setText(QString::number(controller.getState(cellX,cellY)));
        }
    }else{
        for(int i=0;i<1;++i){
            ui->stateTable->item(i,0)->setText("-");
        }
    }
}

void MainWindow::on_operationTypeCombo_activated(int index)
{
    controller.setOperationType(index);
}

void MainWindow::on_operationValueSpin_valueChanged(int arg1)
{
    controller.setOperationValue(arg1);
}

void MainWindow::on_cellXSpin_valueChanged(int arg1)
{
    if(cellX!=arg1)
    {
        cellX=arg1;
        showState();
    }
}

void MainWindow::on_cellYSpin_valueChanged(int arg1)
{
    if(cellY!=arg1)
    {
        cellY=arg1;
        showState();
    }
}

void MainWindow::on_operationValueSpin2_valueChanged(int arg1)
{
    controller.setOperationValue2(arg1);
}

void MainWindow::on_randButton_clicked(bool checked)
{
    ui->intervalSymbolLable->setVisible(checked);
    ui->operationValueSpin2->setVisible(checked);
    controller.setValueType(checked);
}

void MainWindow::on_curTypeButton1_clicked(bool checked)
{
    if(checked){
        curType=1;
        ui->curTypeButton2->setChecked(false);
        ui->curTypeButton3->setChecked(false);
        ui->curTypeButton4->setChecked(false);
        ui->mapShowFrame->setCursor(Qt::ArrowCursor);
    }
}

void MainWindow::on_curTypeButton2_clicked(bool checked)
{
    if(checked){
        curType=2;
        ui->curTypeButton1->setChecked(false);
        ui->curTypeButton3->setChecked(false);
        ui->curTypeButton4->setChecked(false);
        ui->mapShowFrame->setCursor(Qt::PointingHandCursor);
    }
}

void MainWindow::on_curTypeButton3_clicked(bool checked)
{
    if(checked){
        curType=3;
        ui->curTypeButton1->setChecked(false);
        ui->curTypeButton2->setChecked(false);
        ui->curTypeButton4->setChecked(false);
        ui->mapShowFrame->setCursor(Qt::SizeAllCursor);
    }
}

void MainWindow::on_curTypeButton4_clicked(bool checked)
{
    if(checked){
        curType=4;
        ui->curTypeButton1->setChecked(false);
        ui->curTypeButton2->setChecked(false);
        ui->curTypeButton3->setChecked(false);
        ui->mapShowFrame->setCursor(Qt::CrossCursor);
    }
}
