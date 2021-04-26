#include "voteaction.h"
#include <cstdlib>

VoteAction::VoteAction()
{

}

void VoteAction::execute(Cell &cell,int nowTime){
    int count=0;
    for(Cell *nc:cell.neighbors){
        if(nc->getState()==1){
            ++count;
        }
    }
    cell.update( (rand()%cell.neighbors.size())<count?1:0 );
}
