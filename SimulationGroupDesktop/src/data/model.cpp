#include "model.h"
#include <cstdlib>
#include <ctime>

Model::Model()
{
    srand(time(NULL));
    updateCellAndMap();
    defColor=StateColor(0,0,255,255,255,0);
    state2Color.push_back(defColor);
    state2Color.push_back(StateColor(1,INT32_MAX,0,0,0,0));//TODO删除
}

void Model::updateCellAndMap()
{
    int cellId=0;
    cells.clear();
    for(int i=0,hLen=map.getRowNum();i<hLen;++i){
        for(int j=0,wLen=map.getColNum();j<wLen;++j){
            cells.emplace_back();
            cells.rbegin()->id=cellId++;
        }
    }
    //cells大小不再变化才能使用指针，否则地址会变
    int index=0;
    map.cells.clear();
    for(int i=0,hLen=map.getRowNum();i<hLen;++i){
        map.cells.emplace_back();
        for(int j=0,wLen=map.getColNum();j<wLen;++j){
            Cell *cell=&cells[index++];
            cell->mapX=j;
            cell->mapY=i;
            map.cells[i].push_back(cell);
        }
    }
    updateNeighbor();
}

void Model::update(int nowTime)
{
    bool positionChang=false;
    for(Cell &cell:cells){
        for(Action *action:actions){
            action->execute(cell,nowTime);
        }
        //改变元胞位置
        if(map.cells[cell.mapY][cell.mapX]->id != cell.id){
            positionChang=true;
            map.cells[cell.mapY][cell.mapX]=&cell;
        }
    }
    if(positionChang){
        updateNeighbor();
    }
    statistics(nowTime);
}

void Model::setNeighborRule(std::vector<std::pair<int,int>> &relCoos,int type)
{
    this->neighborRuleType=type;
    this->relCoos=relCoos;
    updateNeighbor();
}

void Model::updateNeighbor()
{
    for(int y=0,hLen=map.getRowNum();y<hLen;++y){
        for(int x=0,wLen=map.getColNum();x<wLen;++x){
            Cell *cell=map.cells[y][x];
            cell->neighbors.clear();
            for(std::pair<int,int> coo:relCoos){
                int nX=x+coo.first,nY=y+coo.second;
                if(nX>=0 && nX<wLen && nY>=0 && nY<hLen){
                    cell->neighbors.push_back(map.cells[nY][nX]);
                }
            }
        }
    }
}


void Model::statistics(int nowTime){
    //统计
    std::vector<std::pair<int,int>> statistics;
    std::unordered_map<int,int> state2Count;
    for(Cell &cell:cells){
        int state=cell.getState(nowTime);
        auto iter=state2Count.find(state);
        if(iter!=state2Count.end()){
            iter->second+=1;
        }else{
            state2Count.insert({state,1});
        }
    }
    for(auto iter:state2Count){
        statistics.emplace_back(iter.first,iter.second);
    }
    std::sort(statistics.begin(),statistics.end());
    if(statisticStates.size()<=nowTime){
        statisticStates.push_back(statistics);
    }else{
        statisticStates[nowTime]=statistics;
    }
}
