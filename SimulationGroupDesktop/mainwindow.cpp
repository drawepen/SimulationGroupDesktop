#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>
#include <QPainter>
#include <QDebug>
#include <QTimer>
#include "src/core/map.h"

#include <QMouseEvent>

Map map;//创建地图
int speed=5;
QTimer *timer=new QTimer();

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(timer,&QTimer::timeout,this,&MainWindow::timerUpdate);
    timer->stop();
    ui->speedSlider->setValue(speed);
    ui->speedShowLabel->setText(QString::number(speed, 10));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//重新绘制
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    //设置网格颜色
    QPen pen(Qt::gray);
    painter.setPen(pen);

    //以label左上角为原点
    painter.translate(ui->mapShowLabel->x(),ui->mapShowLabel->y());

    //清空画布
    QBrush brush(Qt::white,Qt::SolidPattern);
    painter.setBrush(brush);
    painter.drawRect(0,0,ui->mapShowLabel->width()-1,ui->mapShowLabel->height()-1);

    //绘制网格
    for(int x=0;x<=map.getwidthnum();x++)
    {
        painter.drawLine(x*map.getwidth(),0,x*map.getwidth(),map.getheightnum()*map.getheight());
    }
    for(int y=0;y<=map.getheightnum();y++)
    {
        painter.drawLine(0,y*map.getheight(),map.getwidthnum()*map.getwidth(),y*map.getheight());
    }

    //绘制细胞
    brush.setColor(Qt::black);
    painter.setBrush(brush);
    for(int x=0;x<map.getwidthnum();x++)
    {
        for(int y=0;y<map.getheightnum();y++)
        {
            if(map.getmap(x,y)==1)
                    painter.drawRect(x*map.getwidth(),y*map.getheight(),map.getwidth(),map.getheight());
        }
    }

    painter.end();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        QPoint point=event->pos()-ui->mapShowLabel->pos();
        //offset=event->pos()-ui->mapShowLabel->pos();
        if(point.x()>=0 and point.x()<=map.getwidth()*map.getwidthnum() and point.y()>=0 and point.y()<=map.getheight()*map.getheightnum())//防止超出map范围
        {
            lastcellx=point.x()/map.getwidth();
            lastcelly=point.y()/map.getheight();
            map.changemap(point.x()/map.getwidth(),point.y()/map.getheight());
            update();//重绘界面
        }
    }

    if(event->button()==Qt::RightButton)
    {
        if(startcell==false)//记录开始点坐标
        {
            startcell=true;
            startcellx=(event->pos().x()-ui->mapShowLabel->pos().x())/map.getwidth();
            startcelly=(event->pos().y()-ui->mapShowLabel->pos().y())/map.getheight();
        }
        else //绘制矩形
        {
            startcell=false;
            int stopcellx=(event->pos().x()-ui->mapShowLabel->pos().x())/map.getwidth();
            int stopcelly=(event->pos().y()-ui->mapShowLabel->pos().y())/map.getheight();
            if(startcellx>stopcellx) std::swap(startcellx,stopcellx);
            if(startcelly>stopcelly) std::swap(startcelly,stopcelly);
            for(int x=startcellx;x<=stopcellx;x++)
            {
                for(int y=startcelly;y<=stopcelly;y++)
                {
                    map.changemap(x,y);
                }
            }
            update();
        }
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        QPoint point=event->pos()-ui->mapShowLabel->pos();
        //offset=event->pos()-ui->mapShowLabel->pos();
        if(point.x()>=0 and point.x()<=map.getwidth()*map.getwidthnum() and point.y()>=0 and point.y()<=map.getheight()*map.getheightnum())//防止超出map范围
        {
            if(lastcellx!=point.x()/map.getwidth() or lastcelly!=point.y()/map.getheight())
            {
                lastcellx=point.x()/map.getwidth();
                lastcelly=point.y()/map.getheight();
                map.changemap(point.x()/map.getwidth(),point.y()/map.getheight());
                update();//重绘界面
            }
        }
    }
}

void MainWindow::timerUpdate()
{
    map.mapupdate();
    update();//更新界面
}

void MainWindow::on_startPushButton_clicked()
{
    timer->start(1000/speed);
}

void MainWindow::on_pausePushButton_clicked()
{
    timer->stop();
}

void MainWindow::on_speedSlider_valueChanged(int arg1)
{
    speed=ui->speedSlider->maximum()/(std::max(ui->speedSlider->maximum()-arg1,1))*arg1;
    ui->speedShowLabel->setText(QString::number(speed, 10));
    if(timer->isActive())
        timer->start(1000/speed);
}
