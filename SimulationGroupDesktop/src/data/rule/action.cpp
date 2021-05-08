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
    for(int i=0;i<len;++i){
        printf("%d ",states[i]);
    }printf("|");
    for(int i=0;i<len;++i){
        printf("%d ",states[i+len]);
    }printf("|");
    int type=libExecute(states,len,nowTime);
    for(int i=0;i<len;++i){
        printf("%d ",states[i]);
    }printf("\n");fflush(stdout);

    if(type==1){
        index=len+1;
        for(Cell *nc:cell.neighbors){
            nc->update(states[index++],nowTime);
        }
    }
    cell.update(states[len],nowTime);
}
