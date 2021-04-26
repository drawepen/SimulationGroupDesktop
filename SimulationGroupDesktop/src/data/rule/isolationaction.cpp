#include "isolationaction.h"

IsolationAction::IsolationAction()
{

}

void IsolationAction::execute(Cell &cell,int nowTime){
    if(this->nowTime!=nowTime){
        this->nowTime=nowTime;
        disMove.clear();
    }
    int count=0,state=cell.getState();
    for(Cell *nc:cell.neighbors){
        if(nc->type!=-1 && nc->getState()==state){
            ++count;
        }
    }
    if(count*1.0/cell.neighbors.size() < 0.33){
        std::unordered_set<int> have;
        std::vector<Cell*> ncells;
        for(Cell *nc:cell.neighbors){
            ncells.push_back(nc);
            have.insert(nc->id);
        }
        for(int index=0;index<ncells.size();++index){
            Cell *ncell=ncells[index];
            if(ncell->type==-1 && disMove.find(ncell->id)==disMove.end()){
                int x=cell.mapX,y=cell.mapY;
                cell.mapX=ncell->mapX;
                cell.mapY=ncell->mapY;
                ncell->mapX=x;
                ncell->mapY=y;
                disMove.insert(ncell->id);
                //实际位置交换放在规则外面，model
                break;
            }
            for(Cell *nc:ncell->neighbors){
                if(have.find(nc->id)==have.end()){
                    ncells.push_back(nc);
                    have.insert(nc->id);
                }
            }
        }
    }
    cell.update(state);
}
