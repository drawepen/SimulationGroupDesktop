#include "controller.h"
#include "data/rule/wlaction.h"
#include "data/rule/voteaction.h"
#include "data/rule/sandaction.h"
#include "data/rule/fireaction.h"
#include "data/rule/isolationaction.h"
#include <sys/time.h>

int64_t currentTimeUs(){
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec * 1000000 + tv.tv_usec;
}

Controller::Controller()
{
    model.setNeighborRule(model.relCoosF);
//    model.addAction(new WlAction());//注意释放
//    model.addAction(new VoteAction());//注意释放
//    model.addAction(new SandAction());//注意释放
//    model.addAction(new FireAction());//注意释放
    model.addAction(new IsolationAction());//注意释放
    randomState();
//    initState();

}

bool Controller::start(){
    return true;
}

bool Controller::suspend(){
    return true;
}

void Controller::runOneFrame(){
    int64_t startTime=currentTimeUs();
    model.update(runTime+1);
    ++runTime;
    nowTime=runTime;
    realTimeSpend=currentTimeUs()-startTime;
}

void Controller::randomState(){
    for(Cell &cell:model.cells){
//        cell.update(rand()%2==1?10:0,nowTime);
        //谢林顿隔离模型
        if(rand()%3==0){
            cell.type=-1;
        }else{
            cell.type=1;
            cell.update(rand()%2,nowTime);
        }
    }
}

void Controller::initState(){
    for(Cell &cell:model.cells){
        cell.update(0,nowTime);
    }
}
//点击操作不会生成新的帧，直接修改最后一帧
void Controller::clickCell(int x,int y){
    if(nowTime<runTime){
        return;         //回放暂时不支持修改
    }
    Cell *cell=model.map.cells[y][x];
//    if(cell->getState()==0){
//        cell->update(10,cell->latestTime());
//    }else{
//        cell->update(cell->getState()-1,cell->latestTime());
//    }
    //沙堆模型
    cell->update(cell->getState()+1000000,cell->latestTime());
}

int Controller::getState(int x,int y){
    return model.getState(x,y,nowTime);
}

void Controller::setModelNeighborRule(int type){
    switch (type) {
    case 0:
        model.setNeighborRule(model.relCoosF);
        break;
    case 1:
        model.setNeighborRule(model.relCoosM);
        break;
    case 2:
        model.setNeighborRule(model.relCoosME);
        break;
    }
}

//设置模型
void Controller::setCellAction(int index,std::string code){

}
