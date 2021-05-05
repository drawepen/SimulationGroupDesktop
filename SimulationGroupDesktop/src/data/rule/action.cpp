#include "action.h"

Action::Action()
{

}
int *states=(int*)malloc(sizeof(int)*4096);
void Action::execute(Cell &cell,int nowTime)
{
    int lastTime=nowTime-1;
    states[0]=cell.getState(lastTime);
    int index=1;
    for(Cell *nc:cell.neighbors){
        states[index++]=nc->getState(lastTime);
    }
    int len=index;
    states[index++]=cell.getState(nowTime);
    for(Cell *nc:cell.neighbors){
        states[index++]=nc->getState(nowTime);
    }
//    for(int i=0;i<len;++i){
//        printf("%d ",states[i]);
//    }
    int type=libExecute(states,len,nowTime);
//    printf("|%d|",type);
//    for(int i=0;i<len;++i){
//        printf("%d ",states[i]);
//    }printf("\n");
    if(type){
        index=1;
        for(Cell *nc:cell.neighbors){
            nc->update(states[index++],nowTime);
        }
    }
    cell.update(states[0],nowTime);
}
