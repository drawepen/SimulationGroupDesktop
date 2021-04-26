#include "fireaction.h"
#include <cstdlib>

FireAction::FireAction()
{

}

void FireAction::execute(Cell &cell,int nowTime){
    int state=cell.getState();
    int newState=0;
    switch (state)
    {
    case 0:
        //newState=rand()%100==0?10:0;
        break;
    case 10:
    {
        int count=0;
        for(Cell *nc:cell.neighbors){
            if(nc->getState()==1){
                ++count;
            }
        }
        newState=count>0?9:10;
        break;
    }
    default:newState=state-1;
    }
    cell.update(newState);
}
