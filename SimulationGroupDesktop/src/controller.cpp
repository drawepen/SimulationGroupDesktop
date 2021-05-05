#include "controller.h"
#include "data/rule/wlaction.h"
#include "data/rule/voteaction.h"
#include "data/rule/sandaction.h"
#include "data/rule/fireaction.h"
#include "data/rule/isolationaction.h"
#include "tool/ShellTool.h"
#include <sys/time.h>

int64_t currentTimeUs(){
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec * 1000000 + tv.tv_usec;
}

Controller::Controller()
{
    model.setNeighborRule(model.relCoosF);
//    model.addAction(new WlAction());
//    model.addAction(new VoteAction());
    model.addAction(new SandAction());
//    model.addAction(new FireAction());
//    model.addAction(new IsolationAction());
//    randomState();
    initState();
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

void Controller::initState(){
    for(Cell &cell:model.cells){
        int value=operationValue;
        if(valueType==1){
            value=rand()%abs(operationValue2-operationValue+1)+min(operationValue,operationValue2);
        }
        cell.update(value,runTime);
    }
}

//点击操作不会生成新的帧，直接修改最后一帧
void Controller::clickCell(int x,int y){
    if(nowTime<runTime){
        return;         //回放时不支持修改
    }
    Cell *cell=model.map.cells[y][x];
    //沙堆模型
    int value=operationValue;
    if(valueType==1){
        value=rand()%abs(operationValue2-operationValue+1)+min(operationValue,operationValue2);
    }
    if(operationType==0){
        cell->update(value,nowTime);
    }else if(operationType==1){
        cell->update(cell->getState()+value,nowTime);
    }
}

void Controller::allClick(){
    if(nowTime<runTime){
        return;         //回放时不支持修改
    }
    for(Cell &cell:model.cells){
        int value=operationValue;
        if(valueType==1){
            value=rand()%abs(operationValue2-operationValue+1)+min(operationValue,operationValue2);
        }
        if(operationType==0){
            cell.update(value,nowTime);
        }else if(operationType==1){
            cell.update(cell.getState()+value,nowTime);
        }
    }
}

int Controller::getState(int x,int y){
    return model.getState(x,y,nowTime);
}

void Controller::setModelNeighborRule(int type){
    model.neighborRuleType=type;
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
ShellTool shellTool;
//设置模型
void Controller::setCellAction(std::vector<std::string> codes){
    model.clearAction();
    for(auto code:codes){
        Action *action=new Action();
        shellTool.buildDll(code);
        action->libExecute=shellTool.libExecute;
        model.addAction(action);
    }
}
