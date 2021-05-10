#include "cell.h"

Cell::Cell()
{
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
