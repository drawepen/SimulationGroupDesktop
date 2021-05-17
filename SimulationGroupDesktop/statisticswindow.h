#ifndef STATISTICSWINDOW_H
#define STATISTICSWINDOW_H

#include <QDialog>
#include <QTableWidget>
#include <QSignalMapper>
#include <QtCharts>

namespace Ui {
class StatisticsWindow;
}

template <typename T>
struct MVector{
    T *ts=(T*)malloc(sizeof(T)*256);
    int index=0;
    void push_back(T t){
        ts[index++]=t;
    }
    T find(int i){
        return ts[i];
    }
    T operator [] (const int i)
    {
        return ts[i];
    }
};

class StatisticsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit StatisticsWindow(QWidget *parent = nullptr);
    ~StatisticsWindow();
private:
    void addDataClicked(int index);
    void initComponent(int index);
    void tableClicked(int index);
    void loadOneGroup(QTableWidget *table,int index,double *mXY);
    void initChart();
private slots:
    void on_pushButton_clicked();
    void on_commandLinkButton_clicked();

    void on_addDataButton_clicked();

    void on_delButton_clicked();

    void on_addDataButton_2_clicked();

    void on_delButton_2_clicked();

    void on_tableWidget_cellClicked(int row, int column);

    void on_tableWidget_2_cellClicked(int row, int column);

    void on_pushButton_2_clicked();

private:
    Ui::StatisticsWindow *ui;
//    MVector<int*> tables;
//    MVector<int*> addButtons;
//    MVector<int*> deleteButtons;
    QSignalMapper *signalMapper;

    //统计图
    QChart *nowStateChart=nullptr;
    QPieSeries *nowStateSeries=nullptr;
    QChart *allStateChart=nullptr;
    QValueAxis *allStateAxisX=nullptr,*allStateAxisY=nullptr;
};

#endif // STATISTICSWINDOW_H
