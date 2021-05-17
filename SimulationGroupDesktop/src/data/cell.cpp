#include "cell.h"

Cell::Cell(int size)
{
    space=NULL;
    //vector扩容时会复制cell内存，覆盖space的起始地址，且调用析构函数混乱，会释放未申请的起始地址报错，申请空间
}
Cell::~Cell()
{
    if(space!=NULL){
        free(space);
        space=NULL;
    }
}
void Cell::update(int state){
    states.push_back(state);
}
void Cell::update(int state,int time){
    int len=states.size();
    if(time >= len){
        while(len<time){
            states.push_back(0);
            ++len;
        }
        states.push_back(state);
    }else{
        states[time]=state;
    }
}
int Cell::setSpaceSize(int size){
    spaceSize=size;
    if(space!=NULL){
        free(space);
        space=NULL;
    }
    if(size>0){
        space=malloc(size);
    }
}
