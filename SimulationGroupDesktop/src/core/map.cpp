#include "map.h"
#include<bits/stdc++.h>


void Map::mapupdate()
{
    int dx[8]={0,0,-1,1,-1,1,-1,1};
    int dy[8]={1,-1,0,0,1,1,-1,-1};

    memset(neighbor,0,sizeof(neighbor));//邻居细胞数量清零

    //重新统计邻居细胞数量
    for(int x=0;x<widthnum;x++)
    {
        for(int y=0;y<heightnum;y++)
        {
            if(map[x][y]==1)
            {
                for(int i=0;i<8;i++)
                {
                    if(dx[i]+x>=0 and dx[i]+x<=widthnum and dy[i]+y>=0 and dy[i]+y<=heightnum) //防止越界
                    {
                        neighbor[dx[i]+x][dy[i]+y]++;
                    }
                }
            }
        }
    }

    //改变细胞状态
    for(int x=0;x<widthnum;x++)
    {
        for(int y=0;y<heightnum;y++)
        {
            if(neighbor[x][y]==3)
                map[x][y]=1;
            else if(neighbor[x][y]!=2)
                map[x][y]=0;
        }
    }
}
