#include "cell.h"

Cell::Cell()
{
}
void Cell::update(int state){
    states.push_back(state);
}
void Cell::update(int state,int time){
    if(mapX==14 && mapY==14){
        int ab=0;
        ab+=1;
    }
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
