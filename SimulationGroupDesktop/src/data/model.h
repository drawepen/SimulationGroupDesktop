#ifndef MODEL_H
#define MODEL_H
#include "map.h"
#include "cell.h"
#include "rule/action.h"
#include <vector>
#include <unordered_map>

struct StateColor{
    int from,to;//from<=to 闭区间
    int r,g,b;
    int type;//0纯色1加斜线
    StateColor(){}
    StateColor(int from,int to,int r,int g,int b,int type=0):from(from),to(to),r(r),g(g),b(b),type(type){}
};

class Model
{
public:
    Model();
    //执行
    void update(int nowTime);
    void statistics(int nowTime);
    //元胞和地图初始化
    void updateCellAndMap();
    //配置设置
    void setNeighborRule(std::vector<std::pair<int,int>> &relCoos,int type);//[{x差值,y差值}

public:
    ~Model(){
        for(Action *action:actions){
            delete action;
        }
    }
    void addAction(Action* action){
        actions.push_back(action);
    }
    void clearAction(){
        for(Action *action:actions){
            delete action;
        }
        actions.clear();
    }
    int getNeighborRuleType(){
        return neighborRuleType;
    }
    std::vector<std::pair<int,int>>& getNeighborRule(){
        return relCoos;
    }
    //状态参数设置
    int getState(int x,int y){
        return map.cells[y][x]->getState();
    }
    int getState(int x,int y,int time){
        return map.cells[y][x]->getState(time);
    }
    void setState2Color(std::vector<StateColor> &state2Color){
        this->state2Color=state2Color;
    }
    std::vector<StateColor>& getState2Color(){
        return state2Color;
    }
    void setDefColor(StateColor sc){
        defColor=sc;
    }
    StateColor getDefColor(){
        return defColor;
    }
    std::vector<std::string>& getActionCodes(){
        return actionCodes;
    }
    void setActionCodes(std::vector<std::string> &actionCodes){
       this->actionCodes=actionCodes;
    }
    //其他参数设置
    std::pair<int,int> getCellNum(){
        return {map.getRowNum(),map.getColNum()};
    }
    void setCellNum(std::pair<int,int> num){
        map.setHeightNum(num.first);
        map.setWidthNum(num.second);
    }
    //统计
    std::vector<std::pair<int,int>> &getStatistics(int nowTime){
        return statisticStates[nowTime];
    }
    void init(){
        statisticStates.clear();
    }

public:
    Map map;//创建地图
    std::vector<Cell> cells;

    //内置邻居规则//???static附初始值总为空
    std::vector<std::pair<int,int>> relCoosF={{0,-1},{-1,0},{1,0},{0,1}};//冯诺依曼型
    std::vector<std::pair<int,int>> relCoosM={{-1,-1},{0,-1},{1,-1},{-1,0},{1,0},{-1,1},{0,1},{1,1}};//摩尔型
    std::vector<std::pair<int,int>> relCoosME={{-2,-2},{-1,-2},{0,-2},{1,-2},{2,-2},{-2,-1},{-1,-1},{0,-1},
                                               {1,-1}, {2,-1}, {-2,0},{-1,0},{1,0},{2,0},{-2,1},{-1,1},
                                               {0,1},  {1,1},  {2,1}, {-2,2},{-1,2},{0,2},{1,2},{2,2}};//扩展摩尔型
private:
    std::vector<Action*> actions;
    std::vector<std::pair<int,int>> relCoos;    //邻居规则
    int neighborRuleType=1;
    std::vector<StateColor> state2Color;   //元胞映射
    StateColor defColor;
    std::vector<std::string> actionCodes;
    //统计状态值[每帧[<状态值,个数>]]
    std::vector<std::vector<std::pair<int,int>>> statisticStates;

private:
    void updateNeighbor();

};
#endif // MODEL_H
