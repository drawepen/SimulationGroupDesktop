#ifndef SANDACTION_H
#define SANDACTION_H
#include "action.h"

class SandAction:public Action
{
public:
    SandAction();
    void execute(Cell &cell,int nowTime);
};

#endif // SANDACTION_H
