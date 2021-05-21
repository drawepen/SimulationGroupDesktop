#include "action.h"
//DEBUG
int mostDifferent(int *ncells,int len){
    long long c1=0;
    int sNum=3;
    char *cs=(char*)(&c1);
    for(int i=1;i<len;++i){
        cs[ncells[i]]++;
    }
    if(cs[ncells[0]]==0){
        return ncells[0];
    }
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
    return minI;
}
int executeD(int *ncells,int len,void *privateSpace,void *publicSpace,int nowTime){
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
        }
        space[1]=space[2]=0;
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
        //如果发现历史半循环颜色选择（颜色的间隔时长相同）4次，不改变颜色
        int index=space[1],hl=space[2];
        printf("index=%d,hl=%d\n",index,hl);fflush(stdout);
        int *history=space+3;
        int count=0,step=-1;
        for(int i=index-1;i!=index;--i){
            if(i<0){
                if(hl>=16){
                    i=16-1;
                }else{
                    break;
                }
            }
            if(history[i]==newState){
                if(step==-1){
                    step=(index-i)%16;
                }else{
                    if(((index-i)%step)==0){
                        count+=1;
                    }else{
                        break;
                    }
                }
            }
            if(count>=4){
                newState=ncells[0];
                break;
            }
        }
        //记录过去16帧的数据
        hl=std::max(index+1,hl);
        index=(index+1)%16;
        history[index]=newState;
        space[1]=index;space[2]=hl;
        ncells[len]=newState;
    }
    return 0;
}
//~DEBUG
Action::Action()
{

}
int *ncells=(int*)malloc(sizeof(int)*4096);
void *publicSpace=malloc(1024*10240);
void Action::execute(Cell &cell,int nowTime)
{
    int lastTime=nowTime-1;
    int index=0;
    ncells[index++]=cell.getState(lastTime);
    for(Cell *nc:cell.neighbors){
        ncells[index++]=nc->getState(lastTime);
    }
    int len=index;
    ncells[index++]=cell.getState(nowTime);
    for(Cell *nc:cell.neighbors){
        ncells[index++]=nc->getState(nowTime);
    }
    ncells[index++]=cell.id;
    for(Cell *nc:cell.neighbors){
        ncells[index++]=nc->id;
    }
    ncells[index++]=cell.spaceSize;
    ncells[index++]=1024*10240;
//    for(int i=0;i<len;++i){
//        printf("%d ",states[i]);
//    }printf("|");
//    for(int i=0;i<len;++i){
//        printf("%d ",states[i+len]);
//    }printf("|");
//    int type=libExecute(ncells,len,cell.space,publicSpace,nowTime);
    int type=executeD(ncells,len,cell.space,publicSpace,nowTime);
//    for(int i=0;i<len;++i){
//        printf("%d ",states[i]);
//    }printf("\n");fflush(stdout);

    if((type&1)==1){
        index=len+1;
        for(Cell *nc:cell.neighbors){
            nc->update(ncells[index++],nowTime);
        }
    }
    if(cellMoveableSwitch && (type&10)==10 && ncells[0]>=0 && ncells[0]<cell.neighbors.size()){
        swap(cell.mapX,cell.neighbors[ncells[0]]->mapX);
        swap(cell.mapY,cell.neighbors[ncells[0]]->mapY);
    }
    cell.update(ncells[len],nowTime);
}
