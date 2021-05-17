#ifndef CELL_H
#define CELL_H
#include <iostream>
#include <vector>

class Cell
{
public:
    Cell(int size);
    ~Cell();
    void update(int state);
    void update(int state,int time);
    int setSpaceSize(int size);
    int getState(){
        return type!=-1?*states.rbegin():-1;
    }
    int getState(int time){
        return time<states.size()?states[time]:-1;
    }
    int latestTime(){
        return states.size()-1;
    }
public:
    std::vector<Cell*> neighbors;
    void *space=NULL;
    int spaceSize=0;
    int mapX,mapY;          //在地图中的坐标
    int id;
    int type=0;               //类型 -1:无元胞、0:基础元胞、1:anget
private:
    std::vector<int> states;
};

#endif // CELL_H
