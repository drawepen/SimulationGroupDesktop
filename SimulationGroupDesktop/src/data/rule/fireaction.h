#ifndef FIREACTION_H
#define FIREACTION_H
#include "action.h"

class FireAction:public Action
{
public:
    FireAction();
    void execute(Cell &cell,int nowTime);
};

#endif // FIREACTION_H
