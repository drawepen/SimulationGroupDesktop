#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <stdint.h>
#include <string>
#include "data/model.h"

struct ProbValue{
    int from,to;
    double probability;
};

class Controller
{
public:
    Controller();
    //设置model
    void setCellAction(std::vector<std::string> codes);
    //执行流程
    bool start();
    bool suspend();//暂停或继续
    bool stop();
    void runOneFrame();
    void allClick();
    void initState();
    void init();
    void clickNeighbor(int xSub,int ySub);
    void setModelNeighborRule(int type);
public:
    std::vector<std::string>& getActionCodes(){
       return model.getActionCodes();
    }
    //设置执行流程参数
    void setRootPath(char *path){
        shellTool.setRootPath(path);
    }
    //界面交互
    void clickCell(int x,int y);
    void clickCell(int fromX,int fromY,int toX,int toY);
    int getState(int x,int y);
    int getCellWidth(){return model.map.getwidth();}
    int getCellHeight(){return model.map.getheight();}
    int getCellColNum(){return model.map.getColNum();}
    int getCellRowNum(){return model.map.getRowNum();}
    int getSpeed(){return speed;}
    int getNowTime(){return nowTime;}
    int getRunTime(){return runTime;}
    int getInterval(){return interval;}
    int getTimeSpend(){return realTimeSpend[nowTime];}
    void setSpeed(int speed){
        if(speed<=0) return;
        this->speed=speed;
        interval=std::max(1000000/speed,1);
    }
    void setNowTime(int time){
        nowTime=time;
    }
    void selfAddNowTime(){
        if(nowTime<runTime){
            ++nowTime;
        }else{
            runOneFrame();
        }
    }
    void selfSubNowTime(){
        if(nowTime>0){
            --nowTime;
        }
    }
    std::vector<std::pair<int,int>> &getStatistics(){
        return model.getStatistics(nowTime);
    }
    int getCurType(){
        return curType;
    }
    void setCurType(int curType){
        this->curType=curType;
    }
    //元胞邻居规则设置
    void initTempNeighborRule(){
        tempNeighborRule=model.getNeighborRule();
    }
    std::vector<std::pair<int,int>>& getTempNeighborRule(){
        return tempNeighborRule;
    }
    void setTempNeighborRule(int type){
        switch (type) {
        case 0:
            tempNeighborRule=model.relCoosF;
            break;
        case 1:
            tempNeighborRule=model.relCoosM;
            break;
        case 2:
            tempNeighborRule=model.relCoosME;
            break;
        }
    }
    //操作
    int getOperationType(){
        return operationType;
    }
    void setOperationType(int value){
        this->operationType=value;
    }
    int getValueType(){
        return valueType;
    }
    void setValueType(int value){
        this->valueType=value;
    }
    int getOperationValue(){
        return operationValue;
    }
    int setOperationValue(int value){
        this->operationValue=value;
    }
    int getOperationValue2(){
        return operationValue2;
    }
    int setOperationValue2(int value){
        this->operationValue2=value;
    }
    std::pair<int,int> getStartCellXY(){
        return {startCellX,startCellY};
    }
    void setStartCellXY(int cellX,int cellY){
        startCellX=cellX;
        startCellY=cellY;
    }

    //模型参数设置
    std::vector<std::pair<int,int>>& getNowModelNeighborRule(){
        return model.getNeighborRule();
    }
    int getModelNeighborRuleType(){
        return model.getNeighborRuleType();
    }
    std::pair<int,int> getCellNum(){
        return model.getCellNum();
    }
    void setCellNum(std::pair<int,int> num){
        model.setCellNum(num);
    }
    void setState2Color(std::vector<StateColor> state2Color){
        model.setState2Color(state2Color);
    }
    std::vector<StateColor>& getState2Color(){
        return model.getState2Color();
    }
    StateColor getDefColor(){
        return model.getDefColor();
    }
    int getCellMoveableSwitch(){
        return model.getCellMoveableSwitch();
    }
    void setCellMoveableSwitch(int cellMoveableSwitch){
        model.setCellMoveableSwitch(cellMoveableSwitch);
    }
    int getCellSpaceSwitch(){
        return model.getCellSpaceSwitch();
    }
    int setCellSpaceSwitch(int cellSpaceSwitch){
        model.setCellSpaceSwitch(cellSpaceSwitch);
    }
    int getCellSpaceSize(){
        return model.getCellSpaceSize();
    }
    void setCellSpaceSize(int cellSpaceSize){
        model.setCellSpaceSize(cellSpaceSize);
    }
    void setProbValues(int index,int from,int to,double probability){
        while(index>=probValues.size()){
            probValues.emplace_back();
        }
        probValues[index].from=from;
        probValues[index].to=to;
        probValues[index].probability=probability;
    }
    void removeProbValues(int index){
        if(index<probValues.size()){
            probValues.erase(probValues.begin()+index);
        }
    }
private:
    //模型
    Model model;
    //执行流程的参数
    int nowTime=0;          //当前展示的时间点
    int runTime=0;          //当前运行的最大时间，从0开始计数
    int interval=100000;    //两帧开始执行时间点的间隔时间(us)
    int speed=10;           //预计每秒执行多少帧
    vector<int64_t> realTimeSpend;  //当前帧执行完花费的实际时间(us)
    //操作
    int mouseType=0;
    int operationType=0;    //0设值1累加值
    int operationValue=0;
    int operationValue2=1;
    std::vector<ProbValue> probValues;
    int valueType=0;//0固定值1随机值2列表概率随机
    int curType=2;  //光标类型:1普通,2单元胞设值,3全元胞设值,4缩放地图
    int startCellX=-1,startCellY=-1;
    //模型设置
    ShellTool shellTool;
    std::vector<std::pair<int,int>> tempNeighborRule;
    //表达式计算
    int count(Cell &cell,int value);

private:
    void updateCellAndMap();
    void operationOneCell(Cell *cell);
};

#endif // CONTROLLER_H
