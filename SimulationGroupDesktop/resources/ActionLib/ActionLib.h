#ifndef ACTIONLIB_H
#define ACTIONLIB_H

#include "ActionLib_global.h"
//传参len=cell+邻居数 ncells.size=3*len+2(上一时刻状态值len+当前状态值len+元胞及邻居id+自由空间大小1+公共空间大小1)
//传参privateSpace自由空间 publicSpace公共空间
//返回int (2进制下)1是0否修改邻居状态 | 10移动00不移动位置
//返回修改数组ncells[0]=[交互位置的邻居下标(非id，从0开始)] ncells[len~2*len-1]=[cell新状态,邻居新状态]
//TODO 传参历史状态值
extern "C" ACTIONLIB_EXPORT int execute(int *ncells,int len,void *privateSpace,void *publicSpace,int nowTime);

#endif // ACTIONLIB_H
/*
//康威生命游戏
int execute(int *ncells,int len,void *privateSpace,void *publicSpace,int nowTime){
    int count=0;
    for(int i=1;i<len;++i){
        if(ncells[i]>0){
            count++;
        }
    }
    if(count==3 || (count==2 && ncells[0]==1)){
        ncells[len]=1;
    }else{
        ncells[len]=0;
    }
    return 0;
}
//沙堆模型
int execute(int *ncells,int len,void *privateSpace,void *publicSpace,int nowTime){
    int nowState=ncells[len];
    if(nowState!=-1){
        nowState+=ncells[0];
    }else{
        nowState=ncells[0];
    }
    if(ncells[0] >= len-1){
        for(int i=1;i<len;++i){
            int state=ncells[i+len];
            if(state!=-1){
                ncells[i+len]=state+1;
            }else{
                ncells[i+len]=1;
            }
        }
        nowState-=len-1;
        ncells[len]=nowState;
        return 1;
    }else{
        ncells[len]=nowState;
        return 0;
    }
}
//投票模型
int execute(int *ncells,int len,void *privateSpace,void *publicSpace,int nowTime){
    if(len<=1){
        return 0;
    }
    int count=0;
    for(int i=1;i<len;++i){
        if(ncells[i]>0){
            ++count;
        }
    }
    ncells[len]= (rand()%(len-1))<count? 1:0;
    return 0;
}
//森林火灾模型
int execute(int *ncells,int len,void *privateSpace,void *publicSpace,int nowTime){
    //-100000着火;<=0空地;>0树木
    int state=ncells[0];
    int newState=state;
    if(state>0){
        newState=1;
        for(int i=1;i<len;++i){
            if(ncells[i]==-100000){
                newState=-100000;
                break;
            }
        }
    }else if(state<=0 && state!=-100000){
        newState=0;
    }
    ncells[len]=newState;
    return 0;
}
//谢林顿隔离模型
//优先搬迁
int execute(int *ncells,int len,void *privateSpace,void *publicSpace,int nowTime){
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
        //有优先级搬迁，优先往左上角搬迁
        for(int i=1;i<len;++i){
            if(ncells[i]<=0 && ncells[i+len]<=0){
                ncells[i+len]=ncells[0];
                ncells[len]=0;
                break;
            }
        }
    }
    return 1;
}
//随机搬迁
int execute(int *ncells,int len,void *privateSpace,void *publicSpace,int nowTime){
    //<=0空地;1类型1;2类型2
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
//糖域模型

*/
