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
    setModelNeighborRule(model.getNeighborRuleType());
//    model.addAction(new WlAction());
//    model.addAction(new VoteAction());
    model.addAction(new SandAction());
//    model.addAction(new FireAction());
//    model.addAction(new IsolationAction());
//    randomState();
    init();
}

void Controller::init(){
    srand(time(NULL));
    nowTime=runTime=0;
    model.init();
    updateCellAndMap();
    realTimeSpend.clear();
    realTimeSpend.push_back(0);
}

void Controller::updateCellAndMap(){
    model.updateCellAndMap();
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
    realTimeSpend.push_back(currentTimeUs()-startTime);
}

void Controller::initState(){
    for(Cell &cell:model.cells){
        int value=operationValue;
        if(valueType==1){
            value=rand()%abs(operationValue2-operationValue+1)+min(operationValue,operationValue2);
        }
        cell.update(value,runTime);
    }
    model.statistics(runTime);
}

void Controller::operationOneCell(Cell *cell)
{
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

//点击操作不会生成新的帧，直接修改最后一帧
void Controller::clickCell(int x,int y)
{
    if(nowTime<runTime){
        return;         //回放时不支持修改
    }
    Cell *cell=model.map.cells[y][x];
    operationOneCell(cell);
    model.statistics(nowTime);
}

void Controller::clickCell(int fromX,int fromY,int toX,int toY)
{
    if(nowTime<runTime){
        return;         //回放时不支持修改
    }
    int fX=min(fromX,toX),fY=min(fromY,toY);
    int tX=max(fromX,toX),tY=max(fromY,toY);
    for(int x=fX;x<=tX;++x){
        for(int y=fY;y<=tY;++y){
            Cell *cell=model.map.cells[y][x];
            operationOneCell(cell);
        }
    }
    model.statistics(nowTime);
}

void Controller::allClick()
{
    if(nowTime<runTime){
        return;//回放时不支持修改
    }
    for(Cell &cell:model.cells){
        operationOneCell(&cell);
    }
    model.statistics(nowTime);
}

int Controller::getState(int x,int y){
    return model.getState(x,y,nowTime);
}
//元胞邻居规则
void Controller::setModelNeighborRule(int type)
{
    switch (type) {
    case 0:
        model.setNeighborRule(model.relCoosF,type);
        break;
    case 1:
        model.setNeighborRule(model.relCoosM,type);
        break;
    case 2:
        model.setNeighborRule(model.relCoosME,type);
        break;
    case 3:
        model.setNeighborRule(tempNeighborRule,type);
        break;
    }
}
void Controller::clickNeighbor(int xSub,int ySub)
{
    bool change=false;
    for(auto iter=tempNeighborRule.begin();iter!=tempNeighborRule.end();++iter){
        if(iter->first==xSub && iter->second==ySub){
            tempNeighborRule.erase(iter);
            change=true;
            break;
        }
    }
    if(!change){
        tempNeighborRule.emplace_back(xSub,ySub);
    }
}

//设置模型
void Controller::setCellAction(std::vector<std::string> codes)
{
    model.clearAction();
    std::vector<Action*> actions;
    for(auto code:codes){
        Action *action=new Action();
        action->libExecute=shellTool.buildDll(code);
        actions.push_back(action);
    }
    for(Action *action:actions){
        model.addAction(action);
    }
    model.setActionCodes(codes);
}
