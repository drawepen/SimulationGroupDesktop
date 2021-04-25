#ifndef MAP_H
#define MAP_H


class Map
{
public:
    int getwidth(){return width;};
    int getheight(){return height;};
    void changewidth(int value){width=value;};
    void changeheight(int value){height=value;};
    int getwidthnum(){return widthnum;};
    int getheightnum(){return heightnum;};
    void changewidthnum(int value){widthnum=value;};
    void changeheightnum(int value){heightnum=value;};
    void changemap(int x,int y){map[x][y]^=1;};
    int getmap(int x,int y){return map[x][y];};
    void mapupdate();

private:
    int map[1000][1000];//存活状态 1为存活
    int neighbor[1000][1000];//邻居细胞个数
    int width=8; //细胞大小
    int height=8;
    int widthnum=120; //细胞个数
    int heightnum=80;
};

#endif // MAP_H
