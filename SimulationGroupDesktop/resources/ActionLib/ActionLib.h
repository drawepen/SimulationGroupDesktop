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
//糖域模型(合作+竞争+长远)
int execute(int *ncells,int len,void *privateSpace,void *publicSpace,int nowTime){
    int sugarMax=9;//单块空地糖量上限
    double sugarRand=0.5,leftRand=0.1,bankSugRand=0.03;//生产糖平均速度（具体大小随机）、生命生成概率、空地开始生产糖概率
    int cooFrom=-1,cooTo=4;//合作收益区间
    double cooComRate=0.5;//合作竞争判断比率，持糖量差距小于cooComRate合作，否则竞争
    double compWast=0.1;//竞争损耗比
    int state=ncells[0];
    int cellCount=ncells[len*3+2];
    //通知状态值[0,cellCount):标记时的时间点//用于判断是否是当前时刻的标记
    //通知状态值[cellCount,cellCount*2):0无1空地糖被取走或agent已发生移动2agent合作3agent被攻击
    //通知状态值[cellCount*2,...):合作或被攻击获得的加糖量（正负都有）
    int *pSpace=(int*)publicSpace;
    //空地
    if(state<=sugarMax){
        if(pSpace[ncells[len*2]]==nowTime && pSpace[cellCount+ncells[len*2]]==1){
            ncells[len]=0;
            return 0;
        }
        if(ncells[0]==0 && rand()*1.0/RAND_MAX>=bankSugRand){
            ncells[len]=0;
            return 0;
        }
        int maxR=((int)sugarRand)*2+1+(((int)sugarRand)<sugarRand);
        state+=rand()%maxR;
        if(state>sugarMax){
            state=sugarMax;
        }
        //糖量达上限，随机产生新生命体
        if(state==sugarMax && rand()*1.0/RAND_MAX<leftRand){
            state=sugarMax+sugarMax;
        }
        ncells[len]=state;
        return 0;
    }
    //生命体
    int id=ncells[len*2];
    if(pSpace[id]==nowTime && (pSpace[cellCount+id]==2||pSpace[cellCount+id]==3)){
        state+=pSpace[cellCount*2+id]-1;
        if(state<=sugarMax){
            state=0;
        }
        ncells[len]=state;
        return 0;
    }
    state-=1;
    if(state<=sugarMax){
        ncells[len]=0;
        return 0;
    }
    int64_t optionalS=0;
    char *optional=(char*)(&optionalS);
    int index=0,blankCount=0;
    double maxV=0;
    //分析利润
    for(int i=1;i<len;++i){
        int nid=ncells[len*2+i];
        double value=0;//预计收益
        if(ncells[i]==0){
            blankCount++;
        }
        if(pSpace[nid]!=nowTime || pSpace[cellCount+nid]==0){
            if(ncells[i]<=sugarMax){
                //吃糖
                value=ncells[i]-1;
            }else{
                if(std::min(ncells[i],ncells[0])*1.0/std::max(ncells[i],ncells[0])>cooComRate){
                    //合作
                    value=(cooFrom+cooTo)*1.0/2;
                }else if(ncells[0]>ncells[i]){
                    //竞争
                    int a=ncells[0]-sugarMax,b=ncells[i]-sugarMax;
                    value=a*1.0/(a+b)*(b-(a+b)*compWast-1);
                }
            }
        }
        if(value>maxV){
            maxV=value;
            index=0;
            optional[index++]=i;
        }else if(value==maxV){
            optional[index++]=i;
        }
    }
    pSpace[id]=nowTime;
    pSpace[cellCount+id]=0;
    if(maxV>0){
        //移动
        int i=optional[rand()%index];
        int nid=ncells[len*2+i];
        if(ncells[i]<=sugarMax){
            //吃糖
            ncells[len]=state+ncells[i]-1;
            ncells[0]=i-1;
            ncells[len+i]=0;
            pSpace[nid]=nowTime;
            pSpace[cellCount+nid]=1;
            pSpace[cellCount+id]=1;
            return 1|2;
        }else{
            if(std::min(ncells[i],ncells[0])*1.0/std::max(ncells[i],ncells[0])>cooComRate){
                //合作
                int v=rand()%(cooTo-cooFrom+1)+cooFrom;
                ncells[len]=state+v-1;
                v=rand()%(cooTo-cooFrom+1)+cooFrom;
                ncells[len+i]+=v;
                pSpace[nid]=nowTime;
                pSpace[cellCount+nid]=2;
                pSpace[cellCount*2+nid]=v;
                pSpace[cellCount+id]=2;
                return 1;
            }else if(ncells[0]>ncells[i]){
                //竞争
                int a=ncells[0]-sugarMax,b=ncells[i]-sugarMax;
                int op;
                if(rand()*1.0/RAND_MAX < a*1.0/(a+b)){
                    //胜利
                    ncells[len]=state+(b-(a+b)*compWast-1);
                    op=-ncells[i];
                    ncells[len+i]=0;
                }else{
                    //失败
                    ncells[len]=0;
                    op=(a-(a+b)*compWast-1);
                    ncells[len+i]+=op;
                }
                ncells[0]=i-1;
                pSpace[nid]=nowTime;
                pSpace[cellCount+nid]=3;
                pSpace[cellCount*2+nid]=op;
                pSpace[cellCount+id]=3;
                return 1|2;
            }
        }
    }else{
        if(len>1 && blankCount==len-1 && ncells[0]>=32){
            //长远决策，糖量充足可移动
            index=0;
            for(int i=1;i<len;++i){
                int nid=ncells[len*2+i];
                if(pSpace[nid]!=nowTime || pSpace[cellCount+nid]==0){
                    optional[index++]=i;
                }
            }
            if(index>0){
                int i=optional[rand()%index];
                int nid=ncells[len*2+i];
                ncells[0]=i;
                ncells[len]=state-1;
                ncells[len+i]=0;
                pSpace[nid]=nowTime;
                pSpace[cellCount+nid]=1;
                pSpace[cellCount+id]=1;
                return 1|2;
            }
        }
        ncells[len]=state;
        return 0;
    }
}
//糖域模型(合作)
int execute(int *ncells,int len,void *privateSpace,void *publicSpace,int nowTime){
    int sugarMax=9;//单块空地糖量上限
    double sugarRand=0.5,leftRand=0.1,bankSugRand=0.03;//生产糖平均速度（具体大小随机）、生命生成概率、空地开始生产糖概率
    int cooFrom=-1,cooTo=4;//合作收益区间
    double cooComRate=0.5;//合作竞争判断比率，持糖量差距小于cooComRate合作，否则竞争
    double compWast=0.1;//竞争损耗比
    int state=ncells[0];
    int cellCount=ncells[len*3+2];
    //通知状态值[0,cellCount):标记时的时间点//用于判断是否是当前时刻的标记
    //通知状态值[cellCount,cellCount*2):0无1空地糖被取走或agent已发生移动2agent合作3agent被攻击
    //通知状态值[cellCount*2,...):合作或被攻击获得的加糖量（正负都有）
    int *pSpace=(int*)publicSpace;
    //空地
    if(state<=sugarMax){
        if(pSpace[ncells[len*2]]==nowTime && pSpace[cellCount+ncells[len*2]]==1){
            ncells[len]=0;
            return 0;
        }
        if(ncells[0]==0 && rand()*1.0/RAND_MAX>=bankSugRand){
            ncells[len]=0;
            return 0;
        }
        int maxR=((int)sugarRand)*2+1+(((int)sugarRand)<sugarRand);
        state+=rand()%maxR;
        if(state>sugarMax){
            state=sugarMax;
        }
        //糖量达上限，随机产生新生命体
        if(state==sugarMax && rand()*1.0/RAND_MAX<leftRand){
            state=sugarMax+sugarMax;
        }
        ncells[len]=state;
        return 0;
    }
    //生命体
    int id=ncells[len*2];
    if(pSpace[id]==nowTime && (pSpace[cellCount+id]==2||pSpace[cellCount+id]==3)){
        state+=pSpace[cellCount*2+id]-1;
        if(state<=sugarMax){
            state=0;
        }
        ncells[len]=state;
        return 0;
    }
    state-=1;
    if(state<=sugarMax){
        ncells[len]=0;
        return 0;
    }
    int64_t optionalS=0;
    char *optional=(char*)(&optionalS);
    int index=0,blankCount=0;
    double maxV=0;
    //分析利润
    for(int i=1;i<len;++i){
        int nid=ncells[len*2+i];
        double value=0;//预计收益
        if(ncells[i]==0){
            blankCount++;
        }
        if(pSpace[nid]!=nowTime || pSpace[cellCount+nid]==0){
            if(ncells[i]<=sugarMax){
                //吃糖
                value=ncells[i]-1;
            }else{
                if(std::min(ncells[i],ncells[0])*1.0/std::max(ncells[i],ncells[0])>cooComRate){
                    //合作
                    value=(cooFrom+cooTo)*1.0/2;
                }
            }
        }
        if(value>maxV){
            maxV=value;
            index=0;
            optional[index++]=i;
        }else if(value==maxV){
            optional[index++]=i;
        }
    }
    pSpace[id]=nowTime;
    pSpace[cellCount+id]=0;
    if(maxV>0){
        int i=optional[rand()%index];
        int nid=ncells[len*2+i];
        if(ncells[i]<=sugarMax){
            //吃糖
            ncells[len]=state+ncells[i]-1;
            ncells[0]=i-1;
            ncells[len+i]=0;
            pSpace[nid]=nowTime;
            pSpace[cellCount+nid]=1;
            pSpace[cellCount+id]=1;
            return 1|2;
        }else{
            //合作
            int v=rand()%(cooTo-cooFrom+1)+cooFrom;
            ncells[len]=state+v-1;
            v=rand()%(cooTo-cooFrom+1)+cooFrom;
            ncells[len+i]+=v;
            pSpace[nid]=nowTime;
            pSpace[cellCount+nid]=2;
            pSpace[cellCount*2+nid]=v;
            pSpace[cellCount+id]=2;
            return 1;
        }
    }else{
        ncells[len]=state;
        return 0;
    }
}
//糖域模型(竞争)
int execute(int *ncells,int len,void *privateSpace,void *publicSpace,int nowTime){
    int sugarMax=9;//单块空地糖量上限
    double sugarRand=0.5,leftRand=0.1,bankSugRand=0.03;//生产糖平均速度（具体大小随机）、生命生成概率、空地开始生产糖概率
    int cooFrom=-1,cooTo=4;//合作收益区间
    double cooComRate=0.5;//合作竞争判断比率，持糖量差距小于cooComRate合作，否则竞争
    double compWast=0.1;//竞争损耗比
    int state=ncells[0];
    int cellCount=ncells[len*3+2];
    //通知状态值[0,cellCount):标记时的时间点//用于判断是否是当前时刻的标记
    //通知状态值[cellCount,cellCount*2):0无1空地糖被取走或agent已发生移动2agent合作3agent被攻击
    //通知状态值[cellCount*2,...):合作或被攻击获得的加糖量（正负都有）
    int *pSpace=(int*)publicSpace;
    //空地
    if(state<=sugarMax){
        if(pSpace[ncells[len*2]]==nowTime && pSpace[cellCount+ncells[len*2]]==1){
            ncells[len]=0;
            return 0;
        }
        if(ncells[0]==0 && rand()*1.0/RAND_MAX>=bankSugRand){
            ncells[len]=0;
            return 0;
        }
        int maxR=((int)sugarRand)*2+1+(((int)sugarRand)<sugarRand);
        state+=rand()%maxR;
        if(state>sugarMax){
            state=sugarMax;
        }
        //糖量达上限，随机产生新生命体
        if(state==sugarMax && rand()*1.0/RAND_MAX<leftRand){
            state=sugarMax+sugarMax;
        }
        ncells[len]=state;
        return 0;
    }
    //生命体
    int id=ncells[len*2];
    if(pSpace[id]==nowTime && (pSpace[cellCount+id]==2||pSpace[cellCount+id]==3)){
        state+=pSpace[cellCount*2+id]-1;
        if(state<=sugarMax){
            state=0;
        }
        ncells[len]=state;
        return 0;
    }
    state-=1;
    if(state<=sugarMax){
        ncells[len]=0;
        return 0;
    }
    int64_t optionalS=0;
    char *optional=(char*)(&optionalS);
    int index=0,blankCount=0;
    double maxV=0;
    //分析利润
    for(int i=1;i<len;++i){
        int nid=ncells[len*2+i];
        double value=0;//预计收益
        if(ncells[i]==0){
            blankCount++;
        }
        if(pSpace[nid]!=nowTime || pSpace[cellCount+nid]==0){
            if(ncells[i]<=sugarMax){
                //吃糖
                value=ncells[i]-1;
            }else{
                if(std::min(ncells[i],ncells[0])*1.0/std::max(ncells[i],ncells[0])>cooComRate){
                }else if(ncells[0]>ncells[i]){
                    //竞争
                    int a=ncells[0]-sugarMax,b=ncells[i]-sugarMax;
                    value=a*1.0/(a+b)*(b-(a+b)*compWast-1);
                }
            }
        }
        if(value>maxV){
            maxV=value;
            index=0;
            optional[index++]=i;
        }else if(value==maxV){
            optional[index++]=i;
        }
    }
    pSpace[id]=nowTime;
    pSpace[cellCount+id]=0;
    if(maxV>0){
        int i=optional[rand()%index];
        int nid=ncells[len*2+i];
        if(ncells[i]<=sugarMax){
            //吃糖
            ncells[len]=state+ncells[i]-1;
            ncells[0]=i-1;
            ncells[len+i]=0;
            pSpace[nid]=nowTime;
            pSpace[cellCount+nid]=1;
            pSpace[cellCount+id]=1;
            return 1|2;
        }else{
            if(ncells[0]>ncells[i]){
                //竞争
                int a=ncells[0]-sugarMax,b=ncells[i]-sugarMax;
                int op;
                if(rand()*1.0/RAND_MAX < a*1.0/(a+b)){
                    //胜利
                    ncells[len]=state+(b-(a+b)*compWast-1);
                    op=-ncells[i];
                    ncells[len+i]=0;
                }else{
                    //失败
                    ncells[len]=0;
                    op=(a-(a+b)*compWast-1);
                    ncells[len+i]+=op;
                }
                ncells[0]=i-1;
                pSpace[nid]=nowTime;
                pSpace[cellCount+nid]=3;
                pSpace[cellCount*2+nid]=op;
                pSpace[cellCount+id]=3;
                return 1|2;
            }
        }
    }else{
        ncells[len]=state;
        return 0;
    }
}
//糖域模型(合作+竞争)
int execute(int *ncells,int len,void *privateSpace,void *publicSpace,int nowTime){
    int sugarMax=9;//单块空地糖量上限
    double sugarRand=0.5,leftRand=0.1,bankSugRand=0.03;//生产糖平均速度（具体大小随机）、生命生成概率、空地开始生产糖概率
    int cooFrom=-1,cooTo=4;//合作收益区间
    double cooComRate=0.5;//合作竞争判断比率，持糖量差距小于cooComRate合作，否则竞争
    double compWast=0.1;//竞争损耗比
    int state=ncells[0];
    int cellCount=ncells[len*3+2];
    //通知状态值[0,cellCount):标记时的时间点//用于判断是否是当前时刻的标记
    //通知状态值[cellCount,cellCount*2):0无1空地糖被取走或agent已发生移动2agent合作3agent被攻击
    //通知状态值[cellCount*2,...):合作或被攻击获得的加糖量（正负都有）
    int *pSpace=(int*)publicSpace;
    //空地
    if(state<=sugarMax){
        if(pSpace[ncells[len*2]]==nowTime && pSpace[cellCount+ncells[len*2]]==1){
            ncells[len]=0;
            return 0;
        }
        if(ncells[0]==0 && rand()*1.0/RAND_MAX>=bankSugRand){
            ncells[len]=0;
            return 0;
        }
        int maxR=((int)sugarRand)*2+1+(((int)sugarRand)<sugarRand);
        state+=rand()%maxR;
        if(state>sugarMax){
            state=sugarMax;
        }
        //糖量达上限，随机产生新生命体
        if(state==sugarMax && rand()*1.0/RAND_MAX<leftRand){
            state=sugarMax+sugarMax;
        }
        ncells[len]=state;
        return 0;
    }
    //生命体
    int id=ncells[len*2];
    if(pSpace[id]==nowTime && (pSpace[cellCount+id]==2||pSpace[cellCount+id]==3)){
        state+=pSpace[cellCount*2+id]-1;
        if(state<=sugarMax){
            state=0;
        }
        ncells[len]=state;
        return 0;
    }
    state-=1;
    if(state<=sugarMax){
        ncells[len]=0;
        return 0;
    }
    int64_t optionalS=0;
    char *optional=(char*)(&optionalS);
    int index=0,blankCount=0;
    double maxV=0;
    //分析利润
    for(int i=1;i<len;++i){
        int nid=ncells[len*2+i];
        double value=0;//预计收益
        if(ncells[i]==0){
            blankCount++;
        }
        if(pSpace[nid]!=nowTime || pSpace[cellCount+nid]==0){
            if(ncells[i]<=sugarMax){
                //吃糖
                value=ncells[i]-1;
            }else{
                if(std::min(ncells[i],ncells[0])*1.0/std::max(ncells[i],ncells[0])>cooComRate){
                    //合作
                    value=(cooFrom+cooTo)*1.0/2;
                }else if(ncells[0]>ncells[i]){
                    //竞争
                    int a=ncells[0]-sugarMax,b=ncells[i]-sugarMax;
                    value=a*1.0/(a+b)*(b-(a+b)*compWast-1);
                }
            }
        }
        if(value>maxV){
            maxV=value;
            index=0;
            optional[index++]=i;
        }else if(value==maxV){
            optional[index++]=i;
        }
    }
    pSpace[id]=nowTime;
    pSpace[cellCount+id]=0;
    if(maxV>0){
        int i=optional[rand()%index];
        int nid=ncells[len*2+i];
        if(ncells[i]<=sugarMax){
            //吃糖
            ncells[len]=state+ncells[i]-1;
            ncells[0]=i-1;
            ncells[len+i]=0;
            pSpace[nid]=nowTime;
            pSpace[cellCount+nid]=1;
            pSpace[cellCount+id]=1;
            return 1|2;
        }else{
            if(std::min(ncells[i],ncells[0])*1.0/std::max(ncells[i],ncells[0])>cooComRate){
                //合作
                int v=rand()%(cooTo-cooFrom+1)+cooFrom;
                ncells[len]=state+v-1;
                v=rand()%(cooTo-cooFrom+1)+cooFrom;
                ncells[len+i]+=v;
                pSpace[nid]=nowTime;
                pSpace[cellCount+nid]=2;
                pSpace[cellCount*2+nid]=v;
                pSpace[cellCount+id]=2;
                return 1;
            }else if(ncells[0]>ncells[i]){
                //竞争
                int a=ncells[0]-sugarMax,b=ncells[i]-sugarMax;
                int op;
                if(rand()*1.0/RAND_MAX < a*1.0/(a+b)){
                    //胜利
                    ncells[len]=state+(b-(a+b)*compWast-1);
                    op=-ncells[i];
                    ncells[len+i]=0;
                }else{
                    //失败
                    ncells[len]=0;
                    op=(a-(a+b)*compWast-1);
                    ncells[len+i]+=op;
                }
                ncells[0]=i-1;
                pSpace[nid]=nowTime;
                pSpace[cellCount+nid]=3;
                pSpace[cellCount*2+nid]=op;
                pSpace[cellCount+id]=3;
                return 1|2;
            }
        }
    }else{
        ncells[len]=state;
        return 0;
    }
}
//糖域模型(无高级行为)
int execute(int *ncells,int len,void *privateSpace,void *publicSpace,int nowTime){
    int sugarMax=9;//单块空地糖量上限
    double sugarRand=0.5,leftRand=0.1,bankSugRand=0.03;//生产糖平均速度（具体大小随机）、生命生成概率、空地开始生产糖概率
    int cooFrom=-1,cooTo=4;//合作收益区间
    double cooComRate=0.5;//合作竞争判断比率，持糖量差距小于cooComRate合作，否则竞争
    double compWast=0.1;//竞争损耗比
    int state=ncells[0];
    int cellCount=ncells[len*3+2];
    //通知状态值[0,cellCount):标记时的时间点//用于判断是否是当前时刻的标记
    //通知状态值[cellCount,cellCount*2):0无1空地糖被取走或agent已发生移动2agent合作3agent被攻击
    //通知状态值[cellCount*2,...):合作或被攻击获得的加糖量（正负都有）
    int *pSpace=(int*)publicSpace;
    //空地
    if(state<=sugarMax){
        if(pSpace[ncells[len*2]]==nowTime && pSpace[cellCount+ncells[len*2]]==1){
            ncells[len]=0;
            return 0;
        }
        if(ncells[0]==0 && rand()*1.0/RAND_MAX>=bankSugRand){
            ncells[len]=0;
            return 0;
        }
        int maxR=((int)sugarRand)*2+1+(((int)sugarRand)<sugarRand);
        state+=rand()%maxR;
        if(state>sugarMax){
            state=sugarMax;
        }
        //糖量达上限，随机产生新生命体
        if(state==sugarMax && rand()*1.0/RAND_MAX<leftRand){
            state=sugarMax+sugarMax;
        }
        ncells[len]=state;
        return 0;
    }
    //生命体
    int id=ncells[len*2];
    if(pSpace[id]==nowTime && (pSpace[cellCount+id]==2||pSpace[cellCount+id]==3)){
        state+=pSpace[cellCount*2+id]-1;
        if(state<=sugarMax){
            state=0;
        }
        ncells[len]=state;
        return 0;
    }
    state-=1;
    if(state<=sugarMax){
        ncells[len]=0;
        return 0;
    }
    int64_t optionalS=0;
    char *optional=(char*)(&optionalS);
    int index=0,blankCount=0;
    double maxV=0;
    //分析利润
    for(int i=1;i<len;++i){
        int nid=ncells[len*2+i];
        double value=0;//预计收益
        if(ncells[i]==0){
            blankCount++;
        }
        if(pSpace[nid]!=nowTime || pSpace[cellCount+nid]==0){
            if(ncells[i]<=sugarMax){
                //吃糖
                value=ncells[i]-1;
            }
        }
        if(value>maxV){
            maxV=value;
            index=0;
            optional[index++]=i;
        }else if(value==maxV){
            optional[index++]=i;
        }
    }
    pSpace[id]=nowTime;
    pSpace[cellCount+id]=0;
    if(maxV>0){
        int i=optional[rand()%index];
        int nid=ncells[len*2+i];
        if(ncells[i]<=sugarMax){
            //吃糖
            ncells[len]=state+ncells[i]-1;
            ncells[0]=i-1;
            ncells[len+i]=0;
            pSpace[nid]=nowTime;
            pSpace[cellCount+nid]=1;
            pSpace[cellCount+id]=1;
            return 1|2;
        }
    }else{
        ncells[len]=state;
        return 0;
    }
}
//糖域模型(长远)
int execute(int *ncells,int len,void *privateSpace,void *publicSpace,int nowTime){
    int sugarMax=9;//单块空地糖量上限
    double sugarRand=0.5,leftRand=0.1,bankSugRand=0.03;//生产糖平均速度（具体大小随机）、生命生成概率、空地开始生产糖概率
    int cooFrom=-1,cooTo=4;//合作收益区间
    double cooComRate=0.5;//合作竞争判断比率，持糖量差距小于cooComRate合作，否则竞争
    double compWast=0.1;//竞争损耗比
    int state=ncells[0];
    int cellCount=ncells[len*3+2];
    //通知状态值[0,cellCount):标记时的时间点//用于判断是否是当前时刻的标记
    //通知状态值[cellCount,cellCount*2):0无1空地糖被取走或agent已发生移动2agent合作3agent被攻击
    //通知状态值[cellCount*2,...):合作或被攻击获得的加糖量（正负都有）
    int *pSpace=(int*)publicSpace;
    //空地
    if(state<=sugarMax){
        if(pSpace[ncells[len*2]]==nowTime && pSpace[cellCount+ncells[len*2]]==1){
            ncells[len]=0;
            return 0;
        }
        if(ncells[0]==0 && rand()*1.0/RAND_MAX>=bankSugRand){
            ncells[len]=0;
            return 0;
        }
        int maxR=((int)sugarRand)*2+1+(((int)sugarRand)<sugarRand);
        state+=rand()%maxR;
        if(state>sugarMax){
            state=sugarMax;
        }
        //糖量达上限，随机产生新生命体
        if(state==sugarMax && rand()*1.0/RAND_MAX<leftRand){
            state=sugarMax+sugarMax;
        }
        ncells[len]=state;
        return 0;
    }
    //生命体
    int id=ncells[len*2];
    if(pSpace[id]==nowTime && (pSpace[cellCount+id]==2||pSpace[cellCount+id]==3)){
        state+=pSpace[cellCount*2+id]-1;
        if(state<=sugarMax){
            state=0;
        }
        ncells[len]=state;
        return 0;
    }
    state-=1;
    if(state<=sugarMax){
        ncells[len]=0;
        return 0;
    }
    int64_t optionalS=0;
    char *optional=(char*)(&optionalS);
    int index=0,blankCount=0;
    double maxV=0;
    //分析利润
    for(int i=1;i<len;++i){
        int nid=ncells[len*2+i];
        double value=0;//预计收益
        if(ncells[i]==0){
            blankCount++;
        }
        if(pSpace[nid]!=nowTime || pSpace[cellCount+nid]==0){
            if(ncells[i]<=sugarMax){
                //吃糖
                value=ncells[i]-1;
            }
        }
        if(value>maxV){
            maxV=value;
            index=0;
            optional[index++]=i;
        }else if(value==maxV){
            optional[index++]=i;
        }
    }
    pSpace[id]=nowTime;
    pSpace[cellCount+id]=0;
    if(maxV>0){
        int i=optional[rand()%index];
        int nid=ncells[len*2+i];
        if(ncells[i]<=sugarMax){
            //吃糖
            ncells[len]=state+ncells[i]-1;
            ncells[0]=i-1;
            ncells[len+i]=0;
            pSpace[nid]=nowTime;
            pSpace[cellCount+nid]=1;
            pSpace[cellCount+id]=1;
            return 1|2;
        }
    }else{
        if(len>1 && blankCount==len-1 && ncells[0]>=32){
            //长远决策，糖量充足可移动
            index=0;
            for(int i=1;i<len;++i){
                int nid=ncells[len*2+i];
                if(pSpace[nid]!=nowTime || pSpace[cellCount+nid]==0){
                    optional[index++]=i;
                }
            }
            if(index>0){
                int i=optional[rand()%index];
                int nid=ncells[len*2+i];
                ncells[0]=i;
                ncells[len]=state-1;
                ncells[len+i]=0;
                pSpace[nid]=nowTime;
                pSpace[cellCount+nid]=1;
                pSpace[cellCount+id]=1;
                return 1|2;
            }
        }
        ncells[len]=state;
        return 0;
    }
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
    int minV=cs[1],index=0;
    cs[index++]=1;
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
            space[1]=(rand()%4)+2;//循环次数K [2,5]
            space[2]=rand();//选择保留原颜色概率
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
//随机智能对群体智能的影响仿真实验2(+决策延迟)
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
    int minV=cs[1],index=0;
    cs[index++]=1;
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
            space[1]=(rand()%4)+2;//循环次数K [2,5]
            space[2]=rand();//保留原颜色概率P
            space[3]=(rand()%4)+1;//决策延迟T帧
        }
    }
    if(space[0]==1){
        //机器人
        if((nowTime%4)!=0){//机器人每隔固定4帧决策一次
            ncells[len]=ncells[0];
            return 0;
        }
        double robotP=0.3;
        if(rand()*1.0/(RAND_MAX+1) < robotP){
            ncells[len]=(rand()%3)+1;
        }else{
            ncells[len]=mostDifferent(ncells,len);
        }
    }else if(space[0]==2){
        //Agent
        int k=space[1],p=space[2],t=space[3];
        //每隔T帧才进行一次决策反映
        if((nowTime%t)!=0){
            ncells[len]=ncells[0];
            return 0;
        }
        //优先选择最不同的颜色
        int newState=mostDifferent(ncells,len);
        //如果发现历史同间隔长度循环选择同一颜色k次，随机(概率p/RAND_MAX)不改变颜色
        int count=space[3+newState*3+0],iTime=space[3+newState*3+1],lastTime=space[3+newState*3+2];
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
