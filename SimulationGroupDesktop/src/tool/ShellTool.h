#ifndef SHELLTOOL_H
#define SHELLTOOL_H
#include <string>
#include <QLibrary>
typedef int (* FUN)(int*,int,int);
class ShellTool
{
public:
    ShellTool();
    FUN buildDll(std::string code);
    FUN libExecute;
private:
    char *shellBuildObj="cl /c %s /Fo\"%s.obj\"";
    char *shellBuildDll="Link /dll %s.obj /def:%s.def";
    char *defaultFileName="code";

    char *templateDel=";\n"
               "; %s module-definition file\n"
               ";\n"
               "LIBRARY         %s.dll\n"
               "EXPORTS\n"
               "                %s @1 PRIVATE";//文件前缀名 文件前缀名 方法名
    char *templateCpp="#include \"ActionLib.h\"\n%s";
    char *templateCpp2="#include <iostream>\n"
               "#include <objbase.h>\n"
               "#define MYDLLTEST_API __declspec(dllexport)\n"
               "MYDLLTEST_API %s\n"
               "\n"
               "BOOL APIENTRY DllMain(HANDLE hModule, DWORD dwReason, void* lpReserved)\n"
               "{\n"
               "\tif(dwReason == DLL_PROCESS_ATTACH){\n"
               "\t\tprintf(\"Dll is attached!22\\n\");\n"
               "\t}else if(dwReason == DLL_PROCESS_DETACH){\n"
               "\t\tprintf(\"Dll is detached!22\\n\");\n"
               "\t}\n"
               "\treturn true;\n"
               "}";//%s "MYDLLTEST_API void FuncInDll(void);\n"
    char *libPath="E:\\Workbench\\Projects\\GraduatedCourseDesign\\LibProjects\\\ActionLib";
    char *libFileName="ActionLib";
    char *libFunName="execute";

    QLibrary *library;
private:
    std::string build(std::string pathName);
    void runVsShell(char *shell);
};

#endif // SHELLTOOL_H
