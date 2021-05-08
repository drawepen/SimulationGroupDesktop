#ifndef MAP_H
#define MAP_H
#include "cell.h"
#include <vector>
class Map
{
public:
    int getwidth(){return width;};
    int getheight(){return height;};
    void changewidth(int value){width=value;};
    void changeheight(int value){height=value;};
    int getColNum(){return colNum;};
    int getRowNum(){return rowNum;};
    void setWidthNum(int value){colNum=value;};
    void setHeightNum(int value){rowNum=value;};

    std::vector<std::vector<Cell*>> cells;
private:
    int width=16; //元胞大小
    int height=16;
    int colNum=30; //元胞个数
    int rowNum=30;
};

#endif // MAP_H
