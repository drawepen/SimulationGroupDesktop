#include "fireaction.h"
#include <cstdlib>

FireAction::FireAction()
{

}

void FireAction::execute(Cell &cell,int nowTime){
    //-100000着火;<=0空地;>0树木
    int lastTime=nowTime-1;
    int state=cell.getState(lastTime);
    int newState=state;
    if(state>0){
        newState=1;
        for(Cell *nc:cell.neighbors){
            if(nc->getState(lastTime)==-100000){
                newState=-100000;
                break;
            }
        }
    }else if(state<=0 && state!=-100000){
        newState=0;
    }
    cell.update(newState,nowTime);
}
