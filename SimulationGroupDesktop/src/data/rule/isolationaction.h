#ifndef ISOLATIONACTION_H
#define ISOLATIONACTION_H
#include "action.h"
#include <unordered_set>

class IsolationAction:public Action
{
public:
    IsolationAction();
    void execute(Cell &cell,int nowTime);
private:
    std::unordered_set<int> disMove;
    int nowTime=-1;
};

#endif // ISOLATIONACTION_H
