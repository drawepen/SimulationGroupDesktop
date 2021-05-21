#include "controller.h"
#include "data/rule/wlaction.h"
#include "data/rule/voteaction.h"
#include "data/rule/sandaction.h"
#include "data/rule/fireaction.h"
#include "data/rule/isolationaction.h"
#include "tool/ShellTool.h"
#include <sys/time.h>
#include <QSqlError>
#include <QSqlQuery>

int64_t currentTimeUs(){
    //获取一天内计算的微秒时间戳
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec * 1000000 + tv.tv_usec;
}

int64_t millTimeUs(){
    //获取自1970年的毫秒时间戳
    timeb t;
    ftime(&t);
    return t.time * 1000 + t.millitm;
}

Controller::Controller()
{
    dataBase=openSql();
    emptyModel();
}

void Controller::emptyModel(){
    isNewM=false;
    model.initEmpty();
    setModelNeighborRule(model.getNeighborRuleType());
    model.addAction(new WlAction());
//    model.addAction(new VoteAction());
//    model.addAction(new SandAction());
//    model.addAction(new FireAction());
//    model.addAction(new IsolationAction());
//    randomState();
    init();
}

Controller::~Controller(){
    closeSql(dataBase);
}

//数据库
QSqlDatabase Controller::openSql(){
    //建立并打开数据库
    QSqlDatabase dataBase;
    dataBase = QSqlDatabase::addDatabase("QSQLITE");
    dataBase.setDatabaseName("D:/MainDataBase.db");
    if (!dataBase.open())
    {
        qDebug() << "Error: Failed to connect dataBase." << dataBase.lastError();
    }
    //创建表格
    QSqlQuery sqlQuery;
    //TODO 加入初始状态值
    if(!sqlQuery.exec("create table model(id integer PRIMARY KEY autoincrement,name text unique,"
                     "row_count int,col_count int,cell_color text,"
                     "neighbor_rule text,"
                     "actions text,"
                     "is_move int,private_size int,public_size int,"
                     "initial_state text,data_time integer)"))
    {
        qDebug() << "Error: Fail to create table."<< sqlQuery.lastError();
    }
    return dataBase;
}

void Controller::closeSql(QSqlDatabase dataBase){
    dataBase.close();
}

void Controller::init(){
    srand(time(NULL));
    nowTime=runTime=0;
    model.init();
    updateCellAndMap();
    realTimeSpend.clear();
    realTimeSpend.push_back(0);
}

void Controller::updateCellAndMap(){
    model.updateCellAndMap();
    initState();
}

bool Controller::start(){
    return true;
}

bool Controller::suspend(){
    return true;
}

void Controller::runOneFrame(){
    int64_t startTime=currentTimeUs();
    model.update(runTime+1);
    ++runTime;
    nowTime=runTime;
    realTimeSpend.push_back(currentTimeUs()-startTime);
}

void Controller::initState(){
    for(Cell &cell:model.cells){
        cell.update(0,runTime);
    }
    model.statistics(runTime);
}

void Controller::operationOneCell(Cell *cell)
{
    int value=operationValue;
    if(valueType==1){
        value=rand()%abs(operationValue2-operationValue+1)+min(operationValue,operationValue2);
    }else if(valueType==2){
        double sum=0;
        for(ProbValue pv:probValues){
            sum+=pv.probability;
        }
        if(sum>0){
            value=rand()%(abs(probValues.rbegin()->from-probValues.rbegin()->to)+1)+
                    min(probValues.rbegin()->from,probValues.rbegin()->to);
            double rd=rand()*sum/(RAND_MAX+1),now=0;
            for(ProbValue pv:probValues){
                now+=pv.probability;
                if(now>rd){
                    value=rand()%(abs(pv.from-pv.to)+1)+min(pv.from,pv.to);
                    break;
                }
            }
        }else{
            return;//不做操作
        }
    }
    if(operationType==0){
        cell->update(value,nowTime);
    }else if(operationType==1){
        cell->update(cell->getState()+value,nowTime);
    }
}

//点击操作不会生成新的帧，直接修改最后一帧
void Controller::clickCell(int x,int y)
{
    if(nowTime<runTime){
        return;         //回放时不支持修改
    }
    Cell *cell=model.map.cells[y][x];
    operationOneCell(cell);
    model.statistics(nowTime);
}

void Controller::clickCell(int fromX,int fromY,int toX,int toY)
{
    if(nowTime<runTime){
        return;         //回放时不支持修改
    }
    int fX=min(fromX,toX),fY=min(fromY,toY);
    int tX=max(fromX,toX),tY=max(fromY,toY);
    for(int x=fX;x<=tX;++x){
        for(int y=fY;y<=tY;++y){
            Cell *cell=model.map.cells[y][x];
            operationOneCell(cell);
        }
    }
    model.statistics(nowTime);
}

void Controller::allClick()
{
    if(nowTime<runTime){
        return;//回放时不支持修改
    }
    for(Cell &cell:model.cells){
        operationOneCell(&cell);
    }
    model.statistics(nowTime);
}

int Controller::getState(int x,int y){
    return model.getState(x,y,nowTime);
}

//元胞邻居规则
void Controller::setModelNeighborRule(int type)
{
    switch (type) {
    case 0:
        model.setNeighborRule(model.relCoosF,type);
        break;
    case 1:
        model.setNeighborRule(model.relCoosM,type);
        break;
    case 2:
        model.setNeighborRule(model.relCoosME,type);
        break;
    case 3:
        model.setNeighborRule(tempNeighborRule,type);
        break;
    }
}

void Controller::clickNeighbor(int xSub,int ySub)
{
    bool change=false;
    for(auto iter=tempNeighborRule.begin();iter!=tempNeighborRule.end();++iter){
        if(iter->first==xSub && iter->second==ySub){
            tempNeighborRule.erase(iter);
            change=true;
            break;
        }
    }
    if(!change){
        tempNeighborRule.emplace_back(xSub,ySub);
    }
}

//设置模型
void Controller::setCellAction(std::vector<std::string> codes)
{
    model.clearAction();
    std::vector<Action*> actions;
    for(auto code:codes){
        Action *action=new Action();
        action->libExecute=shellTool.buildDll(code);
        actions.push_back(action);
    }
    for(Action *action:actions){
        model.addAction(action);
    }
    model.setActionCodes(codes);
}

int Controller::checkExisModel(std::string name){
    QSqlQuery sqlQuery;
    if(sqlQuery.exec("select id from model where name='"+QString(name.c_str()).append("'"))){
        if(sqlQuery.next()){
            return sqlQuery.value(0).toInt();
        }
    }
    return -1;
}

void Controller::saveModel(std::string name){
    model.setName(name);
    QSqlQuery sqlQuery;

    //插入数据
    QString sql;
    int id=checkExisModel(name);
    if(!sqlQuery.exec("delete from model where name = '"+QString(name.c_str()).append("'")))
    {
        qDebug()<<sqlQuery.lastError();
    }
    if(id!=-1){
        sql.append("INSERT INTO model (id,name,row_count,col_count,cell_color,neighbor_rule,actions,"
            "is_move,private_size,public_size,initial_state,data_time)VALUES(").append(QString::number(id))
                .append(","). append(modelSerialize().c_str()).append(",")
                .append(QString::number(millTimeUs())).append(")");
    }else{
        sql.append("INSERT INTO model (name,row_count,col_count,cell_color,neighbor_rule,actions,"
            "is_move,private_size,public_size,initial_state,data_time)VALUES(")
                .append(modelSerialize().c_str()).append(",")
                .append(QString::number(millTimeUs())).append(")");

    }
    if(!sqlQuery.exec(sql))
    {
        qDebug() << sql;
        qDebug() << sqlQuery.lastError();
    }
}

void Controller::newModel(std::string name){
    if(name.empty()){
        emptyModel();
        init();
    }else{
        QSqlQuery sqlQuery;
        bool ok=sqlQuery.exec("select name,row_count,col_count,cell_color,neighbor_rule,actions,"
                "is_move,private_size,public_size,initial_state from model where name='"+QString(name.c_str()).append("'"));
        if(ok && sqlQuery.next())
        {
            modelDeserialization(sqlQuery);
        }
    }
    isNewM=true;
}

std::vector<std::string> Controller::modelsFromDb(){
    QSqlQuery sqlQuery;
    std::vector<std::string> names;
    if(sqlQuery.exec("select id,name,data_time from model order by data_time desc,id desc")){
        while(sqlQuery.next()){
            string name=sqlQuery.value(1).toString().toStdString();
            names.push_back(name);
        }
    }
    return names;
}

std::string str2Hex(const char *str,int len){
    std::string hexStr;
    for(int i=0;i<len;++i){
        unsigned char c=(unsigned char)str[i];
        int a=(c>>4);
        int b=((unsigned char)(c<<4)>>4);
        hexStr.push_back(a+(a<10?'0':'A'));
        hexStr.push_back(b+(b<10?'0':'A'));
    }
    return hexStr;
}

std::string hex2Str(std::string &hexStr){
    std::string str;
    for(int i=0,len=hexStr.size();i<len;i+=2){
        str.push_back(((hexStr[i]-(hexStr[i]>='A'?'A':'0'))<<4)+(hexStr[i+1]-(hexStr[i+1]>='A'?'A':'0')));
    }
    return str;
}

std::string Controller::modelSerialize(){
    //name,row_count,col_count,cell_color,neighbor_rule,
    //actions,is_move,is_move,private_size,public_size,initial_state
    //基础配置
    std::string data;
    data.append("'").append(model.getName()).append("'");
    data.append(",").append(to_string(model.map.getRowNum()));
    data.append(",").append(to_string(model.map.getColNum()));
    //元胞状态映射
    std::vector<StateColor> &stateColors=model.getState2Color();
    int len=sizeof (StateColor)*stateColors.size();
    char *temp=new char[len+16];
    for(int i=0,len=stateColors.size();i<len;++i){
        ((StateColor*)temp)[i]=stateColors[i];
    }
    data.append(",'").append(str2Hex(temp,len)).append("'");
    delete[] temp;
    //邻域规则
    std::vector<std::pair<int,int>> &nr=model.getNeighborRule();
    len=sizeof (std::pair<int,int>)*nr.size();
    temp=new char[len+32];
    for(int i=0,len=nr.size();i<len;++i){
        ((std::pair<int,int>*)temp)[i]=nr[i];
    }
    ((int*)(temp+len))[0]=model.getNeighborRuleType();
    data.append(",'").append(str2Hex(temp,len+sizeof(int))).append("'");
    delete[] temp;
    //行为规则
    std::vector<std::string> &as=model.getActionCodes();
    string codes;
    for(int i=0,len=as.size();i<len;++i){
        codes.append(str2Hex(as[i].c_str(),as[i].size()));
        codes.append(",");
    }
    data.append(",'").append(codes).append("'");
    //agent
    data.append(",").append(to_string(model.getCellMoveableSwitch()));
    data.append(",").append(to_string(model.getCellSpaceSize()));
    data.append(",").append(to_string(128));
    //初始状态
    int colCount=model.map.getColNum();
    int rowCount=model.map.getRowNum();
    temp=new char[colCount*rowCount*sizeof (int)+32];
    for(int i=0;i<rowCount;++i){
        for(int j=0;j<colCount;++j){
            ((int*)temp)[i*colCount+j]=model.getState(j,i,0);
        }
    }
    data.append(",'").append(str2Hex(temp,colCount*rowCount*sizeof (int))).append("'");
    delete[] temp;
    return data;
}

void Controller::modelDeserialization(QSqlQuery &sqlQuery){
    //name,row_count,col_count,cell_color,neighbor_rule,
    //actions,is_move,private_size,public_size,initial_state
    emptyModel();
    int index=0;
    //基础配置
    model.setName(sqlQuery.value(index++).toString().toStdString());
    model.setCellNum({sqlQuery.value(index++).toInt(),sqlQuery.value(index++).toInt()});
    init();
    //元胞状态图形映射
    std::vector<StateColor> stateColors;
    std::string temp=sqlQuery.value(index++).toString().toStdString();
    std::string str=hex2Str(temp);
    StateColor *sc=(StateColor *)str.c_str();
    for(int i=0,len=str.size()/sizeof (StateColor);i<len;++i){
        stateColors.push_back(sc[i]);
    }
    model.setState2Color(stateColors);
    //邻域规则
    std::vector<std::pair<int,int>> nr;
    temp=sqlQuery.value(index++).toString().toStdString();
    str=hex2Str(temp);
    std::pair<int,int> *ps=(std::pair<int,int> *)str.c_str();
    for(int i=0,len=(str.size()-sizeof(int))/sizeof (std::pair<int,int>);i<len;++i){
        nr.push_back(ps[i]);
    }
    model.setNeighborRule(nr,((char*)(str.c_str()+str.size()-sizeof(int)))[0]);
    //行为规则
    std::vector<std::string> as;
    temp=sqlQuery.value(index++).toString().toStdString();
    string codes;
    for(int i=0,len=temp.size();i<len;++i){
        if(temp[i]==','){
            as.push_back(hex2Str(codes));
            codes.clear();
        }else{
            codes.push_back(temp[i]);
        }
    }
    if(as.size()>0){
        setCellAction(as);
    }
    //agent
    model.setCellMoveableSwitch(sqlQuery.value(index++).toInt());
    model.setCellSpaceSize(sqlQuery.value(index++).toInt());
    sqlQuery.value(index++);
    //初始状态
    int colCount=model.map.getColNum();
    int rowCount=model.map.getRowNum();
    temp=sqlQuery.value(index++).toString().toStdString();
    str=hex2Str(temp);
    int *ss=(int *)str.c_str();
    for(int i=0;i<rowCount;++i){
        for(int j=0;j<colCount;++j){
            model.map.cells[i][j]->update(ss[i*colCount+j],0);
        }
    }
}
