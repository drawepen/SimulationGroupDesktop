#include "wlaction.h"

WlAction::WlAction()
{

}

void WlAction::execute(Cell &cell,int nowTime){
    int time=cell.latestTime();
    int count=0;
    for(Cell *nc:cell.neighbors){
        if(nc->getState(time)!=0){
            ++count;
        }
    }
    cell.update((count==3 || (count==2 && cell.getState(time)==1))?1:0);
}
