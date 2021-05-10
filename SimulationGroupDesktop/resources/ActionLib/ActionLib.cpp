#include "ActionLib.h"
int execute(int *ncells,int len,int nowTime){
    //<0空地;1类型1;2类型2
    if(len<=1 || ncells[0]<=0){
        if(ncells[len]<=0){
            ncells[len]=0;
        }
        return 0;
    }
    int count=0;
    for(int i=1;i<len;++i){
        if(ncells[i]==ncells[0]){
            ++count;
        }
    }
    ncells[len]=ncells[0];
    if(count*1.0/(len-1)<0.33){
        //有优先级搬迁，优先往左上角搬迁，易阻塞//TODO写入研究
        //随机搬迁
        int blankCount=0;
        for(int i=1;i<len;++i){
            if(ncells[i]<=0 && ncells[i+len]<=0){
                ++blankCount;
            }
        }
        if(blankCount>0){
            int index=rand()%blankCount;
            for(int i=1;i<len;++i){
                if(ncells[i]<=0 && ncells[i+len]<=0){
                    ++index;
                    if(index==blankCount){
                        ncells[i+len]=ncells[0];
                        ncells[len]=0;
                        break;
                    }
                }
            }
        }
    }
    return 1;
}