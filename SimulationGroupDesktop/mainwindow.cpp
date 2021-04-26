#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "modelsetting.h"
#include <math.h>
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include "src/data/model.h" //???引用头文件报错找不到方法[已解决：makefile文件中被引用的文件要在前声明]

int startButtion=1;//1开始 2暂停 3继续
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer.stop();
    connect(&timer,&QTimer::timeout,this,&MainWindow::timerUpdate);

    ui->speedSlider->setValue(controller.getSpeed());
    ui->speedShowLabel->setText(QString::number(controller.getSpeed(), 10));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    int cellWidthNum,cellHeightNum,cellWidth,cellHeight;
    cellWidthNum=controller.getCellColNum();
    cellHeightNum=controller.getCellRowNum();
    cellWidth=controller.getCellWidth();
    cellHeight=controller.getCellHeight();

    if(event->button()==Qt::LeftButton)
    {
        QPoint point=event->pos()-ui->mapShowLabel->pos();
        //offset=event->pos()-ui->mapShowLabel->pos();
        if(point.x()>=0 and point.x()<=cellWidth*cellWidthNum and point.y()>=0 and point.y()<=cellHeight*cellHeightNum)//防止超出map范围
        {
            lastcellx=point.x()/cellWidth;
            lastcelly=point.y()/cellHeight;
            controller.clickCell(point.x()/cellWidth,point.y()/cellHeight);
            update();//重绘界面
        }
    }

    if(event->button()==Qt::RightButton)
    {
        if(startcell==false)//记录开始点坐标
        {
            startcell=true;
            startcellx=(event->pos().x()-ui->mapShowLabel->pos().x())/cellWidth;
            startcelly=(event->pos().y()-ui->mapShowLabel->pos().y())/cellHeight;
        }
        else //绘制矩形
        {
            startcell=false;
            int stopcellx=(event->pos().x()-ui->mapShowLabel->pos().x())/cellWidth;
            int stopcelly=(event->pos().y()-ui->mapShowLabel->pos().y())/cellHeight;
            if(startcellx>stopcellx) std::swap(startcellx,stopcellx);
            if(startcelly>stopcelly) std::swap(startcelly,stopcelly);
            for(int x=startcellx;x<=stopcellx;x++)
            {
                for(int y=startcelly;y<=stopcelly;y++)
                {
                    controller.clickCell(x,y);
                }
            }
            update();
        }
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    int cellWidthNum,cellHeightNum,cellWidth,cellHeight;
    cellWidthNum=controller.getCellColNum();
    cellHeightNum=controller.getCellRowNum();
    cellWidth=controller.getCellWidth();
    cellHeight=controller.getCellHeight();

    if(event->buttons() & Qt::LeftButton)
    {
        QPoint point=event->pos()-ui->mapShowLabel->pos();
        //offset=event->pos()-ui->mapShowLabel->pos();
        if(point.x()>=0 and point.x()<=cellWidth*cellWidthNum and point.y()>=0 and point.y()<=cellHeight*cellHeightNum)//防止超出map范围
        {
            if(lastcellx!=point.x()/cellWidth or lastcelly!=point.y()/cellHeight)
            {
                lastcellx=point.x()/cellWidth;
                lastcelly=point.y()/cellHeight;
                if(lastcellx>=0 && lastcellx<cellWidthNum && lastcelly>=0 && lastcelly<cellHeightNum){
                    controller.clickCell(point.x()/cellWidth,point.y()/cellHeight);
                    update();//重绘界面
                }
            }
        }
    }
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
    cellWidth=controller.getCellWidth();
    cellHeight=controller.getCellHeight();

    QPainter painter(this);

    //设置网格颜色
    QPen pen(Qt::gray);
    painter.setPen(pen);

    //以label左上角为原点
    painter.translate(ui->centralwidget->x()+ui->mapShowLabel->x(),
                      ui->centralwidget->y()+ui->mapShowLabel->y());

    //清空画布
    QBrush brush(Qt::white,Qt::SolidPattern);
    painter.setBrush(brush);
    painter.drawRect(0,0,ui->mapShowLabel->width()-1,ui->mapShowLabel->height()-1);

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
    //printf("---%d----\n",controller.getNowTime());
    for(int y=0;y<cellHeightNum;y++)
    {
        for(int x=0;x<cellWidthNum;x++)
        {
            if(controller.getState(x,y)>0) painter.drawRect(x*cellWidth,y*cellHeight,cellWidth,cellHeight);
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
    if(timer.isActive())
        timer.start(1000/controller.getSpeed());
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
    ms->show();

}

void MainWindow::reShowMap(){
    ui->nowTimeLabel->setText(QString::number(controller.getNowTime(),10));
    ui->runTimeLabel->setText(QString::number(controller.getRunTime(),10));
    ui->progressSlider->setValue(controller.getNowTime());
}
