#ifndef VOTEACTION_H
#define VOTEACTION_H
#include "action.h"

class VoteAction:public Action
{
public:
    VoteAction();
    void execute(Cell &cell,int nowTime);
};

#endif // VOTEACTION_H
