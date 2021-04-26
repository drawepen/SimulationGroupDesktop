#ifndef ACTION_H
#define ACTION_H
#include "../cell.h"
using namespace std;
class Action
{
public:
    Action();
    virtual void execute(Cell &cell,int nowTime);
};

#endif // ACTION_H
