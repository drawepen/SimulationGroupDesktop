#include "sandaction.h"

SandAction::SandAction()
{

}

void SandAction::execute(Cell &cell,int nowTime){
    if(cell.getState() < cell.neighbors.size()){
        cell.update(cell.getState());
        return;
    }
    int nextTime=cell.latestTime()+1;
    for(Cell *nc:cell.neighbors){
        int nextState=nc->getState(nextTime);
        if(nextState!=-1){
            nc->update(nextState+1,nextTime);
        }else{
            nc->update(nc->getState()+1,nextTime);
        }
    }
    cell.update(cell.getState()-cell.neighbors.size(),nextTime);
}
