#include "sandaction.h"

SandAction::SandAction()
{

}

void SandAction::execute(Cell &cell,int nowTime){
    int lastTime=nowTime-1;
    int nowState=cell.getState(nowTime);
    if(nowState!=-1){
        nowState+=cell.getState(lastTime);
    }else{
        nowState=cell.getState(lastTime);
    }
    if(cell.getState(lastTime) >= cell.neighbors.size()){
        for(Cell *nc:cell.neighbors){
            int state=nc->getState(nowTime);
            if(state!=-1){
                nc->update(state+1,nowTime);
            }else{
                nc->update(1,nowTime);
            }
        }
        nowState-=cell.neighbors.size();
    }
    cell.update(nowState,nowTime);
}
