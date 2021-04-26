#include "cell.h"

Cell::Cell()
{
}
void Cell::update(int state){
    states.push_back(state);
}
void Cell::update(int state,int time){
    if((time >= states.size())){
        states.push_back(state);
    }else{
        states[time]=state;
    }
}
