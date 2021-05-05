#ifndef ACTION_H
#define ACTION_H
#include "../cell.h"
#include "src/tool/ShellTool.h"
using namespace std;
class Action
{
public:
    Action();
    virtual void execute(Cell &cell,int nowTime);
public:
    FUN libExecute;
};

#endif // ACTION_H
