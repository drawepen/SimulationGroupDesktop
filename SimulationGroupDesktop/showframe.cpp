#include "showframe.h"
#include <QPainter>
#include <QPen>

ShowFrame::ShowFrame(QWidget *parent) : QFrame(parent)
{

}

//绘图
void ShowFrame::paintEvent(QPaintEvent *qPaintEvent)
{
    Controller &controller=*this->controller;
    int cellColNum,cellRowNum,cellWidth,cellHeight;
    cellColNum=controller.getCellColNum();
    cellRowNum=controller.getCellRowNum();
    cellWidth=width()/cellColNum;
    cellHeight=height()/cellRowNum;
    cellWidth=cellHeight=min(cellWidth,cellHeight);

    QPainter painter(this);
    //以label左上角为原点
    painter.translate(0,0);
    //设置网格颜色
    painter.setPen(QPen(Qt::gray));
    //清空画布
    QBrush brush(Qt::white,Qt::SolidPattern);
    painter.setBrush(brush);
    painter.drawRect(0,0,width()-1,height()-1);

    //绘制细胞
    std::vector<StateColor>& state2Color=controller.getState2Color();

    brush.setColor(QColor(state2Color[0].r,state2Color[0].g,state2Color[0].b));
    painter.setBrush(brush);
    painter.drawRect(0,0,cellColNum*cellWidth,cellRowNum*cellHeight);
    for(int y=0;y<cellRowNum;y++)
    {
        for(int x=0;x<cellColNum;x++)
        {
            int state=controller.getState(x,y);
            for(int i=state2Color.size()-1;i>0;--i){//TODO 待优化，减少颜色修改和内层循环(影响不大)、画矩形个数(影响大)、矩阵大小(影响也大)
                if(state>=state2Color[i].from && state<=state2Color[i].to){
                    brush.setColor(QColor(state2Color[i].r,state2Color[i].g,state2Color[i].b));
                    painter.setBrush(brush);
                    painter.drawRect(x*cellWidth,y*cellHeight,cellWidth,cellHeight);
                    break;
                }
            }
        }
    }

    //绘制网格
    for(int x=0;x<=cellColNum;x++)
    {
        painter.drawLine(x*cellWidth,0,x*cellWidth,cellRowNum*cellHeight);
    }
    for(int y=0;y<=cellRowNum;y++)
    {
        painter.drawLine(0,y*cellHeight,cellColNum*cellWidth,y*cellHeight);
    }

    //特效
    QPoint point=mapFromGlobal(QCursor().pos());
    int cellX=point.x()/cellWidth;
    int cellY=point.y()/cellHeight;
    if(point.x()>=0 && cellX<cellColNum && point.y()>=0 && cellY<cellRowNum){
        int mX=cellX*cellWidth,mY=cellY*cellHeight;
        //绘制元胞边界
        painter.setBrush(QBrush());
        if(controller.getCurType()==2){
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
        }else if(controller.getCurType()==3){
            painter.setPen(QPen(Qt::red, 4));
            painter.drawRect(0,0,cellColNum*cellWidth,cellRowNum*cellHeight);
            painter.setPen(QPen(Qt::white, 1));
            painter.drawRect(3,3,cellColNum*cellWidth-6,cellRowNum*cellHeight-6);
        }
    }
    painter.end();
}
