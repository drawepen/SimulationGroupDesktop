#ifndef WLACTION_H
#define WLACTION_H
#include "action.h"

class WlAction:public Action
{
public:
    WlAction();
    void execute(Cell &cell,int nowTime);
};

#endif // WLACTION_H
