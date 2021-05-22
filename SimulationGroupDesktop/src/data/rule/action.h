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
    int cellMoveableSwitch=1;
    void *publicSpace;
    int *ncells;
    int publicSpaceSize=1024*10240;
};

#endif // ACTION_H
