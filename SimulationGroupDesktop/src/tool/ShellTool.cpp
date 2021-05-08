#include "ShellTool.h"
#include<stdlib.h>
#include<QLibrary>

ShellTool::ShellTool()
{

}
FUN ShellTool::buildDll(std::string code){
    char cs[1024+code.size()];
    //生成代码
    sprintf(cs,"%s\\%s.cpp",libPath,libFileName);
    FILE *fp = fopen(cs,"w");
    sprintf(cs,templateCpp,code.c_str());
    fprintf(fp,"%s",cs);
    fclose(fp);

    if(library!=nullptr){
        library->unload();//先释链接，才能修改文件
    }
    //生成dll
    system("E:\\Workbench\\Projects\\GraduatedCourseDesign\\LibProjects\\ActionLib\\build.bat");
    //更新方法句柄
    sprintf(cs,"%s\\release\\%s.dll",libPath,libFileName);
    library = new QLibrary( cs );//加载dll，当前目录
    return (FUN)library->resolve(libFunName);
}

std::string buildDll2(std::string code,std::string pathName,std::string funName)
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
//    return build(pathName);
    return "";
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
