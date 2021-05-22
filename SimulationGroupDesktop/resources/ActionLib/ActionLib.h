#ifndef ACTIONLIB_H
#define ACTIONLIB_H

#include "ActionLib_global.h"
//@Parameter len 元胞邻域数+1(元胞本身)
//@Parameter ncells 大小3len+3，依次有：元胞和其邻域上一时刻状态值、当前时刻可读状态值、id,私有空间大小，公共空间大小,元胞总数
//@Parameter privateSpace 元胞私有空间，同一元胞不同时间下共有,第一次执行前自动初始化为0
//@Parameter publicSpace 公共空间，所有元胞均可访问，第一次执行前自动初始化为0
//@Parameter nowTime 当前时间，即第几次更新全体元胞状态，从0开始
//@return int 由两组选择2进制值取或运算生成，即（1）01B修改邻域状态值00B仅修改自身状态|（2）10B元胞移动00B元胞移动；如返回二进制11B表示修改自身及邻域状态且移动元胞位置
//@return ncells 无需主动返回，在ncells[len,2*len-1]中填充修改后的当前元胞状态值和邻域状态值，如需移动元胞，在ncells[0]填充要与之交换位置的邻域下标，通过交换来移动当前元胞位置。
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
    //0空地;1着火;2树木
    int state=ncells[0];
    int newState=state;
    if(state>0){
        for(int i=1;i<len;++i){
            if(ncells[i]==1){
                newState=1;
                break;
            }
        }
    }else if(state<=0){
        newState=0;
    }
    ncells[len]=newState;
    return 0;
}
//沙堆模型1-主动释放型
int execute(int *ncells,int len,void *privateSpace,void *publicSpace,int nowTime){
    //[0,5]
    int nowState=ncells[len];
    if(nowState!=-1){
        nowState+=ncells[0];
    }else{
        nowState=ncells[0];
    }
    if(ncells[0] >= 5){
        for(int i=1;i<len;++i){
            int state=ncells[i+len];
            if(state!=-1){
                ncells[i+len]=state+1;
            }else{
                ncells[i+len]=1;
            }
        }
        nowState-=4;
        if(ncells[2*len]==218 || ncells[2*len]==424){
            nowState+=1;
        }
        ncells[len]=nowState;
        return 1;
    }else{
        if(ncells[2*len]==218 || ncells[2*len]==424){
            nowState+=1;
        }
        ncells[len]=nowState;
        return 0;
    }
}
//沙堆模型2-仅修改自身-需确保元胞邻居的邻居包含自身
int execute(int *ncells,int len,void *privateSpace,void *publicSpace,int nowTime){
    //[0,5]
    int newState=ncells[0];
    if(newState>=5){
        newState-=4;
    }
    for(int i=1;i<len;++i){
        if(ncells[i]>=5){
            newState+=1;
        }
    }
    //选择初始点，每帧自动加一
    if(nowTime==1){
         ((bool*)privateSpace)[0]=(ncells[0]>0);
    }
    if(((bool*)privateSpace)[0] && newState < 5){
        newState+=1;
    }
    ncells[len]=newState;
    return 0;
}
//谢林顿隔离模型
//优先级搬迁
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
//环境：随机增糖，产生新生命
//元胞：先判断己方是否需要逃跑、是否发动战争、对方是否逃跑、战争判定、是否接受合作邀请、是否发出合作邀请(向后遍历即id大的)、是否移动到环境
//糖域模型1
int execute(int *ncells,int len,void *privateSpace,void *publicSpace,int nowTime){
    int sugarMax=9;//单块空地糖量上限
    double sugarRand=0.5,leftRand=0.1,bankSugRand=0.02;//生产糖平均速度（具体大小随机）、生命生成概率、空地开始生产糖概率
    int newState=ncells[0];
    int cellCount=ncells[len*2+2];
    //通知状态值[0,cellCount):已执行的时间点//用于判断是否执行过
    //通知状态值[cellCount,...):0无1空地糖被去走
    int *pSpace=(int*)publicSpace;
    pSpace[ncells[len*2]]=nowTime;
    //空地
    if(newState<=sugarMax){
        if(pSpace[cellCount+ncells[len*2]]==1){
            pSpace[cellCount+ncells[len*2]]=0;
            ncells[len]=0;
            return 0;
        }
        if(ncells[0]==0 && rand()*1.0/RAND_MAX>=bankSugRand){
            ncells[len]=0;
            return 0;
        }
        int maxR=((int)sugarRand)*2+1+(((int)sugarRand)<sugarRand);
        newState+=rand()%maxR;
        if(newState>sugarMax){
            newState=sugarMax;
        }
        //糖量达上限，随机产生新生命体
        if(newState==sugarMax && rand()*1.0/RAND_MAX<leftRand){
            newState=sugarMax+sugarMax;
        }
        ncells[len]=newState;
        return 0;
    }
    //生命体
    newState-=1;
    if(newState<=sugarMax){
        ncells[len]=0;
        return 0;
    }
    int64_t optionalS=0;
    char *optional=(char*)(&optionalS);
    int index=0,maxV=0;
    for(int i=1;i<len;++i){
        if(ncells[i]>sugarMax){
            continue;
        }
        if(ncells[i]>maxV){
            maxV=ncells[i];
            index=0;
            optional[index++]=i;
        }else if(ncells[i]==maxV){
            optional[index++]=i;
        }
    }
    if(index>0){
        //移动
        int oindex=optional[rand()%index];
        ncells[0]=oindex-1;
        ncells[len]=newState+ncells[oindex];
        if(pSpace[ncells[len*2+oindex]]!=nowTime){
            pSpace[cellCount+ncells[len*2+oindex]]=1;
            return 0|10;
        }else{
            ncells[len+oindex]=0;
            return 1|10;
        }
    }else{
        ncells[len]=newState;
        return 0;
    }
}

//随机智能对群体智能的影响仿真实验1
int execute(int *ncells,int len,void *privateSpace,void *publicSpace,int nowTime){
    //1,2,3节点|0空地
    if(ncells[0]==0){
        ncells[len]=0;
        return 0;
    }
    int sNum=3;
    if(nowTime==1){
        //分配机器人类型 1机器人2Agent
        double robotRate=0.05;
        if(rand()*1.0/(RAND_MAX+1) < robotRate){
            ((int*)privateSpace)[0]=1;
        }else{
            ((int*)privateSpace)[0]=2;
        }
    }
    if(((int*)privateSpace)[0]==1){
        //机器人
        double robotP=0.3;
        if(rand()*1.0/(RAND_MAX+1) < robotP){
            ncells[len]=(rand()%3)+1;
        }else{
            //Agent
            long long c1=0;
            char *cs=(char*)(&c1);
            for(int i=1;i<len;++i){
                cs[ncells[i]]++;
            }
            if(cs[ncells[0]]==0){
                ncells[len]=ncells[0];
            }else{
                int minI=1,count=1;
                for(int i=2;i<=sNum;++i){
                    if(cs[i]<cs[minI]){
                        minI=i;
                        count=1;
                    }else if(cs[i]==cs[minI]){
                        count+=1;
                    }
                }
                if(count>1){
                    int num=rand()%count;
                    for(int i=minI+1,j=0;i<=sNum && j<num;++i){
                        if(cs[i]==cs[minI]){
                            minI=i;
                            ++j;
                         }
                    }
                }
                ncells[len]=minI;
            }
        }
    }else if(((int*)privateSpace)[0]==2){
        //Agent
        long long c1=0;
        char *cs=(char*)(&c1);
        for(int i=1;i<len;++i){
            cs[ncells[i]]++;
        }
        if(cs[ncells[0]]==0){
            ncells[len]=ncells[0];
        }else{
            int minI=1,count=1;
            for(int i=2;i<=sNum;++i){
                if(cs[i]<cs[minI]){
                    minI=i;
                    count=1;
                }else if(cs[i]==cs[minI]){
                    count+=1;
                }
            }
            if(count>1){
                int num=rand()%count;
                for(int i=minI+1,j=0;i<=sNum && j<num;++i){
                    if(cs[i]==cs[minI]){
                        minI=i;
                        ++j;
                     }
                }
            }
            ncells[len]=minI;
        }
    }
    return 0;
}
//随机智能对群体智能的影响仿真实验2
int mostDifferent(int *ncells,int len){
    int64_t c1=0;
    int sNum=3;
    char *cs=(char*)(&c1);
    for(int i=1;i<len;++i){
        cs[ncells[i]]++;
    }
    if(cs[ncells[0]]==0){
        return ncells[0];
    }
    int minV=cs[1],index=1;
    cs[1]=1;
    for(int i=2;i<=sNum;++i){
        if(cs[i]<minV){
            minV=cs[i];
            index=0;
            cs[index++]=i;
        }else if(cs[i]==minV){
            cs[index++]=i;
        }
    }
    return cs[rand()%index];
}
int execute(int *ncells,int len,void *privateSpace,void *publicSpace,int nowTime){
    //1,2,3节点|0空地
    if(ncells[0]==0){
        ncells[len]=0;
        return 0;
    }
    int *space=(int*)privateSpace;
    if(nowTime==1){
        //分配机器人类型 1机器人2Agent
        if(ncells[0] < 0){
            space[0]=1;
            ncells[0]=(rand()%3)+1;
        }else{
            space[0]=2;
            space[1]=(rand()%4)+2;
            space[2]=rand();
        }
    }
    if(space[0]==1){
        //机器人
        double robotP=0.3;
        if(rand()*1.0/(RAND_MAX+1) < robotP){
            ncells[len]=(rand()%3)+1;
        }else{
            ncells[len]=mostDifferent(ncells,len);
        }
    }else if(space[0]==2){
        //Agent
        //优先选择最不同的颜色
        int newState=mostDifferent(ncells,len);
        //如果发现历史同间隔长度循环选择同一颜色k次，随机(概率p/RAND_MAX)不改变颜色
        int k=space[1],p=space[2];
        int count=space[3+newState*3+0],iTime=space[3+newState*3+1],lastTime=space[3+newState*3+2];
        int index=space[1],hl=space[2];
        if(nowTime-lastTime==iTime){
            count++;
            if(count>=k && rand()<p){
                newState=ncells[0];
            }
        }
        int newITime=nowTime-space[3+newState*3+2];
        if(newITime==space[3+newState*3+1]){
            space[3+newState*3+0]++;
        }else{
            space[3+newState*3+0]=(space[3+newState*3+2]!=0?1:0);
            space[3+newState*3+1]=newITime;
        }
        space[3+newState*3+2]=nowTime;
        ncells[len]=newState;
    }
    return 0;
}

//交通流量模拟
int execute(int *ncells,int len,void *privateSpace,void *publicSpace,int nowTime){
    //0空地1墙2车辆产生3车辆消失10车
    //元胞邻域传入顺序上、右、左
    int cellCount=ncells[len*2+2];
    //通知状态值[0,cellCount):空地是否已被占用，占用放nowTime
    int *pSpace=(int*)publicSpace;
    int state=ncells[0];
    ncells[len]=state;
    switch (state) {
    case 0:
    case 1:
    case 3: return 0;
    case 2:{
        if(len>1 && ncells[len+1]==0 && pSpace[ncells[len*2+1]]!=nowTime){
            ncells[len+1]=10;
            pSpace[ncells[len*2+1]]=nowTime;
            return 1;
        }else{
            return 0;
        }
    }
    case 10:{
        if(len>1 && ncells[len+1]==3){
            ncells[len]=0;
            return 0;
        }else{
            for(int i=1;i<len;++i){
                if(ncells[i]==0 && pSpace[ncells[len*2+i]]!=nowTime){
                    pSpace[ncells[len*2+i]]=nowTime;
                    ncells[0]=i-1;
                    return 0|2;
                }
            }
            return 0;
        }
    }
    }
    return 0;
}

*/
