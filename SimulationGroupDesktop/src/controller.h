#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <stdint.h>
#include <string>
#include "data/model.h"

class Controller
{
public:
    Controller();
    //设置model
    void setCellAction(int index,std::string code);
    //执行流程
    bool start();
    bool suspend();         //暂停或继续
    bool stop();
    void runOneFrame();
    void randomState();
    void initState();
    void init(){nowTime=runTime=0;updateCellAndMap();}
    //设置执行流程参数

    //界面交互
    void clickCell(int x,int y);
    int getState(int x,int y);
    int getCellWidth(){return model.map.getwidth();}
    int getCellHeight(){return model.map.getheight();}
    int getCellColNum(){return model.map.getColNum();}
    int getCellRowNum(){return model.map.getRowNum();}
    int getSpeed(){return speed;}
    int getNowTime(){return nowTime;}
    int getRunTime(){return runTime;}
    int getInterval(){return interval;}
    int getTimeSpend(){return realTimeSpend;}
    void setSpeed(int speed){
        if(speed<=0) return;
        this->speed=speed;
        interval=std::max(1000000/speed,1);
    }
    void setNowTime(int time){
        nowTime=time;
    }
    void selfAddNowTime(){
        if(nowTime<runTime){
            ++nowTime;
        }else{
            runOneFrame();
        }
    }
    void selfSubNowTime(){
        if(nowTime>0){
            --nowTime;
        }
    }

    //模型参数设置
    std::vector<std::pair<int,int>>& getNowModelNeighborRule(){return model.getNeighborRule();}
    void setModelNeighborRule(int type);
    std::pair<int,int> getCellNum(){return model.getCellNum();}
    void setCellNum(std::pair<int,int> num){model.setCellNum(num);}
private:
    //模型
    Model model;
    //执行流程的参数
    int nowTime=0;          //当前展示的时间点
    int runTime=0;          //当前运行的最大时间，从0开始计数
    int interval=100000;    //两帧开始执行时间点的间隔时间(us)
    int speed=10;           //预计每秒执行多少帧
    int64_t realTimeSpend;      //当前帧执行完花费的实际时间(us)

    //表达式计算
    int count(Cell &cell,int value);

    //模型设置

private:
    void updateCellAndMap(){model.updateCellAndMap();initState();}
};

#endif // CONTROLLER_H