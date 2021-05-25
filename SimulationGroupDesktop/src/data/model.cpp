//#define DATA_S
#include "model.h"
#include <cstdlib>
#include <ctime>
#include <string.h>

Model::Model()
{
    initEmpty();
}

void Model::initEmpty(){
    srand(time(NULL));
    cellMoveableSwitch=1;
    cellSpaceSwitch=1;
    cellSpaceSize=0;
    neighborRuleType=1;
    statisticStates.clear();
    state2Color.clear();
    name.clear();
    actions.clear();
    relCoos.clear();
    state2Color.clear();
    actionCodes.clear();
    statisticStates.clear();

    updateCellAndMap();
    defColor=StateColor(0,0,255,255,255,0);
    state2Color.push_back(defColor);
    state2Color.push_back(StateColor(1,INT32_MAX,0,0,0,0));
}

void Model::updateCellAndMap()
{
    int cellId=0;
    cells.clear();
    for(int i=0,hLen=map.getRowNum();i<hLen;++i){
        for(int j=0,wLen=map.getColNum();j<wLen;++j){
            cells.emplace_back(cellSpaceSize);
            cells.rbegin()->id=cellId++;
        }
    }
    //cells大小不再变化才能使用指针，否则地址会变
    if(cellSpaceSize>0){
        for(Cell &cell:cells){
//            cell.setSpaceSize(cellSpaceSize);////???未解之谜 Release模式下,调用函数就报错，函数能正常执行，但出函数前报错
            cell.space=malloc(cellSpaceSize);
            cell.count=map.getRowNum()*map.getColNum();
        }
    }
    int index=0;
    map.cells.clear();
    map.historicalCells.clear();
    for(int i=0,hLen=map.getRowNum();i<hLen;++i){
        map.cells.emplace_back();
        map.historicalCells.emplace_back();
        for(int j=0,wLen=map.getColNum();j<wLen;++j){
            Cell *cell=&cells[index++];
            cell->mapX=j;
            cell->mapY=i;
            map.cells[i].push_back(cell);
            map.historicalCells[i].emplace_back();
            map.historicalCells[i][j].push_back(cell);
        }
    }
    updateNeighbor();
}

void Model::update(int nowTime)
{
    if(nowTime<=1){
        for(Cell &cell:cells){
            if(cell.spaceSize>0 && cell.space!=0){
                memset(cell.space,0,cell.spaceSize);
            }
        }
        for(Action *action:actions){
            memset(action->publicSpace,0,action->publicSpaceSize);
        }
    }
    for(Cell &cell:cells){
        for(Action *action:actions){
            action->execute(cell,nowTime);
        }
    }
    //改变元胞位置
    bool positionChang=false;
    for(Cell &cell:cells){
        if(cellMoveableSwitch && (map.cells[cell.mapY][cell.mapX])->id != cell.id){
            positionChang=true;
            map.cells[cell.mapY][cell.mapX]=&cell;
        }
        map.historicalCells[cell.mapY][cell.mapX].push_back(&cell);
    }
    if(positionChang){
        updateNeighbor();
    }
    statistics(nowTime);
#ifdef DATA_S
    if(nowTime==1){
        printf("\n0,");
    }
    if((nowTime%5)==0){
        std::vector<int> sugtCounts;
        double sum=0;
        for(Cell &cell:cells){
            int sug=cell.getState(nowTime)-9;
            if(sug>0){
                sugtCounts.push_back(sug);
                sum+=sug;
            }
        }
        if(sugtCounts.size()>0){
            double ave=sum/sugtCounts.size();
            sum=0;
            for(int sug:sugtCounts){
                sum+=(sug-ave)*(sug-ave);
            }
            sum/=sugtCounts.size();
        }else{
            sum=0;
        }
//        printf("%lf,",sum);fflush(stdout);//方差
        printf("%d,",sugtCounts.size());fflush(stdout);//数量
    }
#endif
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
