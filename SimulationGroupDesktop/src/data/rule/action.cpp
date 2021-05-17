#include "action.h"

Action::Action()
{

}
int *ncells=(int*)malloc(sizeof(int)*4096);
void *publicSpace=malloc(1024*10240);
void Action::execute(Cell &cell,int nowTime)
{
    int lastTime=nowTime-1;
    int index=0;
    ncells[index++]=cell.getState(lastTime);
    for(Cell *nc:cell.neighbors){
        ncells[index++]=nc->getState(lastTime);
    }
    int len=index;
    ncells[index++]=cell.getState(nowTime);
    for(Cell *nc:cell.neighbors){
        ncells[index++]=nc->getState(nowTime);
    }
    ncells[index++]=cell.id;
    for(Cell *nc:cell.neighbors){
        ncells[index++]=nc->id;
    }
    ncells[index++]=cell.spaceSize;
    ncells[index++]=1024*10240;
//    for(int i=0;i<len;++i){
//        printf("%d ",states[i]);
//    }printf("|");
//    for(int i=0;i<len;++i){
//        printf("%d ",states[i+len]);
//    }printf("|");
    int type=libExecute(ncells,len,cell.space,publicSpace,nowTime);
//    for(int i=0;i<len;++i){
//        printf("%d ",states[i]);
//    }printf("\n");fflush(stdout);

    if((type&1)==1){
        index=len+1;
        for(Cell *nc:cell.neighbors){
            nc->update(ncells[index++],nowTime);
        }
    }
    if(cellMoveableSwitch && (type&10)==10 && ncells[0]>=0 && ncells[0]<cell.neighbors.size()){
        swap(cell.mapX,cell.neighbors[ncells[0]]->mapX);
        swap(cell.mapY,cell.neighbors[ncells[0]]->mapY);
    }
    cell.update(ncells[len],nowTime);
}
