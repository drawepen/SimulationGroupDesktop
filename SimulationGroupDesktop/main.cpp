#include "mainwindow.h"
#include <QApplication>
#include <QStyleFactory>

//TODO 最后处理，封装成的方法的代码再拆开重复写
int main(int argc, char *argv[])
{
    if(QT_VERSION>=QT_VERSION_CHECK(5,6,0))
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setStyle(QStyleFactory::create("fusion"));
    QApplication a(argc, argv);
    MainWindow w(argv[0]);
    w.show();
    return a.exec();
}
