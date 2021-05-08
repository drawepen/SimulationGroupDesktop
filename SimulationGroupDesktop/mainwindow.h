#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "src/controller.h"
#include <QMainWindow>
#include <QTimer>
//WARNING:注意循环引用头文件

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void reShowMap();
public:
    Controller controller;
private:
    Ui::MainWindow *ui;
    //播放
    QTimer timer;
    int startButtion=1;//1开始 2暂停 3继续
    //操作
    int cellX=0,cellY=0;
    int curType=1;      //光标类型:1普通,2单元胞设值,3全元胞设值,4缩放地图

    //窗口缩放控制
    int winZoomType=0;  //1右窗口
    int winZoomOriX,winZoomOriY;

protected:
    void paintEvent(QPaintEvent *event);
    void timerUpdate();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private slots:
    void on_startPushButton_clicked();
    void on_nextFrameButton_clicked();
    void on_lastFrameButton_clicked();
    void on_progressSlider_valueChanged(int arg1);
    void on_speedSlider_valueChanged(int arg1);
    void on_modelset_triggered();
    void on_useDoc_triggered();

    void on_operationTypeCombo_activated(int index);

    void on_operationValueSpin_valueChanged(int arg1);

    void on_cellXSpin_valueChanged(int arg1);

    void on_cellYSpin_valueChanged(int arg1);

    void on_operationValueSpin2_valueChanged(int arg1);

    void on_randButton_clicked(bool checked);

    void on_curTypeButton1_clicked(bool checked);

    void on_curTypeButton2_clicked(bool checked);

    void on_curTypeButton3_clicked(bool checked);

    void on_curTypeButton4_clicked(bool checked);

private:
    void updateProgress();
    void clickEvent(QPoint &point);
    void showState();
};


#endif // MAINWINDOW_H
