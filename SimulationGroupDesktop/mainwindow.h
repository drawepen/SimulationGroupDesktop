#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QPoint offset;//存储鼠标与label位置差值
    int lastcellx=-1,lastcelly=-1;//存储鼠标移动事件中上一个细胞位置
    int startcellx=-1,startcelly=-1;//存储即将改变的矩形起点
    bool startcell=false;


protected:
    void paintEvent(QPaintEvent *event);
    void timerUpdate();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private slots:
    void on_startPushButton_clicked();
    void on_pausePushButton_clicked();
    void on_speedSlider_valueChanged(int arg1);
};


#endif // MAINWINDOW_H
