#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "src/controller.h"
#include "statisticswindow.h"
#include <QMainWindow>
#include <QTimer>
#include <QtCharts>
//WARNING:注意循环引用头文件

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(char *path,QWidget *parent = nullptr);
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
    int oldValueType=0;
    QString oldTableText;
    int tableChanging=0;
    int operationWinHeight=41;

    //窗口缩放控制
    int winZoomType=0;  //1右窗口//2右下窗口
    int winZoomOriX,winZoomOriY;
    int mousePressState=0;//0无操作1按下2释放3移动中
    int startCellX,startCellY;

    //统计
    QChart *nowStateChart=nullptr;
    QPieSeries *nowStateSeries=nullptr;
    QChart *allStateChart=nullptr;
    std::unordered_map<int,QLineSeries*> allStateSeries;
    QValueAxis *allStateAxisX=nullptr,*allStateAxisY=nullptr,*allStateAxisY2=nullptr;
    int maxStatistic=INT32_MIN;
    int specialEffType=0;
    StatisticsWindow *statisticswindow=nullptr;

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
    void on_modelSet_triggered();
    void on_useDoc_triggered();
    void on_exportMapImage_triggered();
    void on_exportNowStaImage_triggered();
    void on_exportAllStaImage_triggered();
    void on_seniorOperationSwitch_triggered();
    void on_action_rs_triggered();
    void on_modelnew_triggered();
    void on_actionModelSave_triggered();

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

    void on_resetButton_clicked();

    void on_addOperationButton_clicked();

    void on_seniorOperationTable_itemChanged(QTableWidgetItem *item);

    void on_seniorOperationTable_itemSelectionChanged();

    void on_seniorOperationTable_cellClicked(int row, int column);

private:
    void updateProgress();
    void clickEvent(QPoint &point);
    void showState();
    void updateChart();
    void initChart();
    void monitorDyn();
    void monitorFix();
};


#endif // MAINWINDOW_H
