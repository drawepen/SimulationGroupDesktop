#include "ShellTool.h"
#include<stdlib.h>
#include <io.h>
#include <fstream>
#include <direct.h>
#include<QLibrary>
#include<QFile>

ShellTool::ShellTool()
{

}

FUN ShellTool::buildDll(std::string code){
    check();
    char cs[1024+code.size()];
    //生成代码
    sprintf(cs,"%s/%s.cpp",rootPath.c_str(),libFileName);
    FILE *fp = fopen(cs,"w");
    sprintf(cs,templateCpp,code.c_str());
    fprintf(fp,"%s",cs);
    fclose(fp);
    if(library!=nullptr){
        library->unload();//先释链接，才能修改文件
    }
    //生成dll
    system((rootPath+"/build.bat "+rootPath).c_str());
    //更新方法句柄
    sprintf(cs,"%s/release/%s.dll",rootPath.c_str(),libFileName);
    library = new QLibrary( cs );//加载dll，当前目录
    return (FUN)library->resolve(libFunName);
    return NULL;
}

void ShellTool::setRootPath(char *path){
    char *end=strrchr(path,'\\');
    if(end==NULL||end==nullptr){
        end=strrchr(path,'/');
    }
    if(end!=NULL&&end!=nullptr){
        rootPath=std::string(path,end);
    }
    rootPath+="/build";
    printf("rootPath=%s\n",rootPath.c_str());fflush(stdout);
}

bool isExistPath(std::string path)
{
    if (access(path.c_str(), 0) == -1)
    {
#ifdef WIN32
        int flag = _mkdir(path.c_str());
#endif
#ifdef linux
        int flag = mkdir(dir.c_str(), 0777);
#endif
        return false;
    }else{
        return true;
    }
}

void copyFile(std::string fileFrom,std::string fileTo){
    QFile::copy(fileFrom.c_str(), fileTo.c_str());
    /*
    FILE *fp = fopen(fileTo.c_str(),"w");
    QFile file(fileFrom.c_str());
    if(file.open(QIODevice::ReadOnly))//以只读方式打开
    {
        char buffer[1024+16];
        int64_t lineLen = file.read(buffer,1024);
        if(lineLen != -1)
        {
            buffer[lineLen]=0;
            fprintf(fp,"%s",buffer);
        }
    }
    file.close();
    fclose(fp); //*/
}

void ShellTool::check(){
    if(!isExistPath(rootPath)){
        copyFile(":/file/build/resources/ActionLib/ActionLib.h",rootPath+"/ActionLib.h");
        copyFile(":/file/build/resources/ActionLib/ActionLib.pro",rootPath+"/ActionLib.pro");
        copyFile(":/file/build/resources/ActionLib/ActionLib_global.h",rootPath+"/ActionLib_global.h");
        copyFile(":/file/build/resources/ActionLib/build.bat",rootPath+"/build.bat");
    }
}
//
std::string ShellTool::buildDll2(std::string code,std::string pathName,std::string funName)
{
    int index=pathName.find_last_of('.');
    std::string prefixName=(index==std::string::npos)?pathName:pathName.substr(0,index);
    std::string path=prefixName.substr(0,(index=prefixName.find_last_of('\\'))!=std::string::npos?index:0);
    std::string relName=prefixName.substr((index=prefixName.find_last_of('\\'))!=std::string::npos?index+1:0);
    char cs[1024+code.size()];
    FILE *fp;
    if(path.size()>0){
        sprintf(cs,"mkdir -p %s",path.c_str());
        printf("%s\n",cs);fflush(stdout);
        system(cs);
    }
    //生成源文件
    fp = fopen(pathName.c_str(),"w");
//    sprintf(cs,templateCpp,code.c_str());
    fprintf(fp,"%s",cs);
    fclose(fp);
    //生成def文件
    sprintf(cs,"%s.def",prefixName.c_str());
    fp = fopen(cs,"w");
//    fprintf(fp,templateDel,relName.c_str(),relName.c_str(),funName.c_str());
    fclose(fp);
    return build(pathName);
}

std::string ShellTool::build(std::string pathName)
{
    int index=pathName.find_last_of('.');
    std::string prefixName=(index==std::string::npos)?pathName:pathName.substr(0,index);
    char cs[4096];
    int ci=sprintf(cs,shellBuildObj,pathName.c_str(),prefixName.c_str());
    cs[ci++]='\n';
    sprintf(cs+ci,shellBuildDll,prefixName.c_str(),prefixName.c_str());
    runVsShell(cs);
    return prefixName+".dll";
}

void ShellTool::runVsShell(char *shell){
    std::string str="call E:\\Software_installation\\VS2010\\VC\\bin\\vcvars32.bat\n";
    str+=shell;
    str="E:\\Workbench\\Qt\\SimulationGroupDesktop\\build-SimulationGroupDesktop-Desktop_Qt_6_0_2_MinGW_64_bit-Debug\\debug\\lib\\build.bat";
    system(str.c_str());
}
