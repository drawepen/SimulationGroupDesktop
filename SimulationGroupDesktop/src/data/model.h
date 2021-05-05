#ifndef MODEL_H
#define MODEL_H
#include "map.h"
#include "cell.h"
#include "rule/action.h"
#include <vector>

class Model
{
public:
    Model();
    ~Model(){
        for(Action *action:actions){delete action;}
    }
    void update(int nowTime);
    void addAction(Action* action){actions.push_back(action);}
    void clearAction(){
        for(Action *action:actions){delete action;}
        actions.clear();
    }
    void setNeighborRule(std::vector<std::pair<int,int>> &relCoos);//[{x差值,y差值}]
    std::vector<std::pair<int,int>>& getNeighborRule(){return relCoos;}
    //状态参数设置
    int getState(int x,int y){return map.cells[y][x]->getState();}
    int getState(int x,int y,int time){return map.cells[y][x]->getState(time);}
    //其他参数设置
    std::pair<int,int> getCellNum(){return {map.getRowNum(),map.getColNum()};}
    void setCellNum(std::pair<int,int> num){map.setHeightNum(num.first);map.setWidthNum(num.second);}
    //元胞和地图初始化
    void updateCellAndMap();

public:
    Map map;//创建地图
    std::vector<Cell> cells;
    int neighborRuleType=0;
    //内置邻居规则//???static附初始值总为空
    std::vector<std::pair<int,int>> relCoosF={{0,-1},{-1,0},{1,0},{0,1}};//冯诺依曼型
    std::vector<std::pair<int,int>> relCoosM={{-1,-1},{0,-1},{1,-1},{-1,0},{1,0},{-1,1},{0,1},{1,1}};//摩尔型
    std::vector<std::pair<int,int>> relCoosME={{-2,-2},{-1,-2},{0,-2},{1,-2},{2,-2},{-2,-1},{-1,-1},{0,-1},
                                               {1,-1}, {2,-1}, {-2,0},{-1,0},{1,0},{2,0},{-2,1},{-1,1},
                                               {0,1},  {1,1},  {2,1}, {-2,2},{-1,2},{0,2},{1,2},{2,2}};//扩展摩尔型
private:
    std::vector<Action*> actions;
    std::vector<std::pair<int,int>> relCoos;    //邻居规则

private:
    void updateNeighbor();
};
#endif // MODEL_H
