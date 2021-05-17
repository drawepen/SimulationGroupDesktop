#include "statisticswindow.h"
#include "ui_statisticswindow.h"

StatisticsWindow::StatisticsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StatisticsWindow)
{
    ui->setupUi(this);
//    signalMapper=new QSignalMapper(this);//debug模式下报错
//    connect(signalMapper, SIGNAL(mapped(int)), this, SIGNAL(addDataClicked(int)));
    ui->tableWidget->verticalHeader()->setMinimumWidth(16);
    ui->tableWidget->setColumnWidth(0,60);
    ui->tableWidget->setColumnWidth(1,60);
    ui->tableWidget->setColumnWidth(2,ui->tableWidget->width()-136-2);

    ui->tableWidget_2->verticalHeader()->setMinimumWidth(16);
    ui->tableWidget_2->setColumnWidth(0,60);
    ui->tableWidget_2->setColumnWidth(1,60);
    ui->tableWidget_2->setColumnWidth(2,ui->tableWidget_2->width()-136-2);

//    tables.push_back((int*)ui->tableWidget);
//    addButtons.push_back((int*)ui->addDataButton);
//    deleteButtons.push_back((int*)ui->delButton);

//    tables.push_back((int*)ui->tableWidget_2);
//    addButtons.push_back((int*)ui->addDataButton_2);
//    deleteButtons.push_back((int*)ui->delButton_2);

    ui->tableWidget_2->setVisible(false);
    ui->addDataButton_2->setVisible(false);
    ui->delButton_2->setVisible(false);

    //统计图
    initChart();
}

StatisticsWindow::~StatisticsWindow()
{
    delete ui;
}

void StatisticsWindow::initChart(){
    allStateChart=new QChart();
    allStateChart->setAnimationOptions(QChart::AllAnimations);//设置动画
    allStateChart->layout()->setContentsMargins(0, 0, 0, 0);//设置外边界
    allStateChart->setMargins(QMargins(2, 2, 2, 2));//设置内边界
    allStateChart->setBackgroundRoundness(4);//设置背景区域圆角
    allStateChart->legend()->setVisible(true);

    allStateAxisX=new QValueAxis();
    allStateAxisX->setRange(0,60);
    allStateAxisX->setGridLineVisible(true);
    allStateAxisX->setTickCount(10);     //标记的个数
    allStateAxisX->setMinorTickCount(4); //次标记的个数

    allStateAxisY=new QValueAxis();
    allStateAxisY->setRange(0,0);
    allStateAxisY->setGridLineVisible(true);
    allStateAxisY->setTickCount(5+1);
    allStateAxisY->setMinorTickCount(4);

    allStateChart->addAxis(allStateAxisX, Qt::AlignBottom);
    allStateChart->addAxis(allStateAxisY, Qt::AlignLeft);

    ui->graphicsView->setChart(allStateChart);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
}

void StatisticsWindow::on_pushButton_clicked()
{
//    int index=tables.size();
//    QTableWidget *table=new QTableWidget();
//    QPushButton *addButton=new QPushButton();
//    QPushButton *deleteButton=new QPushButton();

//    tables.push_back(table);
//    addButtons.push_back(addButton);
//    deleteButtons.push_back(deleteButton);

    ui->tableWidget_2->setVisible(true);
    ui->addDataButton_2->setVisible(true);
    ui->delButton_2->setVisible(true);
}

void StatisticsWindow::initComponent(int index){
//    QTableWidget *table=tables[index];
//    QPushButton *addButton=addButtons[index];
//    QPushButton *delButton=deleteButtons[index];
//    int width=180,height=320;
//    int x=10+index*(200),y=30;
////    table->setGeometry(x,y,width,height);
//    table->verticalHeader()->setMinimumWidth(16);
//    table->setColumnWidth(0,60);
//    table->setColumnWidth(1,60);
//    table->setColumnWidth(2,table->width()-136-2);
////    signalMapper->setMapping(addButton,index);
////    signalMapper->setMapping(delButton,-index-1);
}

void StatisticsWindow::addDataClicked(int index){
    if(index<0){
        index=-index-1;
        QTableWidget *tableWidget;
        if(index==0){
            tableWidget=ui->tableWidget;
        }else if(index==1){
            tableWidget=ui->tableWidget_2;
        }
        tableWidget->setRowCount(0);
        if(index==1){
            ui->tableWidget_2->setVisible(false);
            ui->addDataButton_2->setVisible(false);
            ui->delButton_2->setVisible(false);
        }
        return;
    }
    QTableWidget *tableWidget;
    if(index==0){
        tableWidget=ui->tableWidget;
    }else if(index==1){
        tableWidget=ui->tableWidget_2;
    }
    int row=tableWidget->rowCount();
    tableWidget->insertRow(row);
    tableWidget->setItem(row,0,new QTableWidgetItem("0"));
    tableWidget->setItem(row,1,new QTableWidgetItem("0"));
    tableWidget->item(row,0)->setTextAlignment(Qt::AlignCenter);
    tableWidget->item(row,1)->setTextAlignment(Qt::AlignCenter);
    QTableWidgetItem *item1=new QTableWidgetItem("删除");
    item1->setTextAlignment(Qt::AlignCenter);
    item1->setTextColor(Qt::red);
    tableWidget->setItem(row,2,item1);
}

void StatisticsWindow::tableClicked(int index){
    QTableWidget *tableWidget;
    if(index==0){
        tableWidget=ui->tableWidget;
    }else if(index==1){
        tableWidget=ui->tableWidget_2;
    }
    if(tableWidget->currentItem()->column()==2){
        int row=tableWidget->currentItem()->row();
        tableWidget->removeRow(row);
    }
}

void StatisticsWindow::loadOneGroup(QTableWidget *table,int index,double *mXY){
    QLineSeries *series=new QLineSeries();
    if(index < allStateChart->series().size()){
        series=(QLineSeries*)allStateChart->series().at(index);
        series->clear();//???报错
    }else{
        series=new QLineSeries();
    }

    int rowCount=table->rowCount();
    double minY=INT32_MAX,maxY=INT32_MIN;
    double minX=INT32_MAX,maxX=INT32_MIN;
    for(int i=0;i<rowCount;++i){
        if(table->item(i,0)!=NULL && table->item(i,1)!=NULL){
            double x=table->item(i,0)->text().toDouble();
            double y=table->item(i,1)->text().toDouble();
            series->append(x,y);
            maxX=std::max(maxX,x);minX=std::min(minX,x);
            maxY=std::max(maxY,y);minY=std::min(minY,y);
        }
    }
    if(minY<=maxY){
        int len=series->count();
        if(index>0){
            maxX= std::max(maxX,mXY[0]); minX=std::min(minX,mXY[1]);
            maxY= std::max(maxY,mXY[2]); minY=std::min(minY,mXY[3]);
            len=std::max(len,(int)mXY[4]);
        }
        mXY[0]=maxX;mXY[1]=minX;
        mXY[2]=maxY;mXY[3]=minY;
        series->setName(QString::number(index+1));
        allStateAxisX->setRange(minX,maxX);
        allStateAxisY->setRange(minY,maxY);
        allStateChart->addSeries(series);
        if(len<=10){
            allStateAxisX->setTickCount(len);//标记的个数
        }
        allStateChart->setAxisX(allStateAxisX,series);
        allStateChart->setAxisY(allStateAxisY,series);
        mXY[4]=len;
    }
}

void StatisticsWindow::on_commandLinkButton_clicked()
{
    initChart();
    double *mXY=new double[5];
    if(ui->tableWidget->isVisible()){
        loadOneGroup(ui->tableWidget,0,mXY);
    }
    if(ui->tableWidget_2->isVisible()){
        loadOneGroup(ui->tableWidget_2,1,mXY);
    }
    delete[] mXY;
}

void StatisticsWindow::on_addDataButton_clicked()
{
    addDataClicked(0);
}

void StatisticsWindow::on_delButton_clicked()
{
    addDataClicked(-1);
}

void StatisticsWindow::on_addDataButton_2_clicked()
{
    addDataClicked(1);
}

void StatisticsWindow::on_delButton_2_clicked()
{
    addDataClicked(-2);
}

void StatisticsWindow::on_tableWidget_cellClicked(int row, int column)
{
    tableClicked(0);
}

void StatisticsWindow::on_tableWidget_2_cellClicked(int row, int column)
{
    tableClicked(1);
}

void StatisticsWindow::on_pushButton_2_clicked()
{
    QDateTime localTime(QDateTime::currentDateTimeUtc().toLocalTime());
    QString fileName = QFileDialog::getSaveFileName(this,
                  tr("保存统计图(当前状态)"),localTime.toString("yyyyMMddhhmmss")+".png",
                  tr("*.png;; *.jpg;; *.gif;; *.bmp;; *.tif")); //选择路径
    if(!fileName.isEmpty()){
         QImage image = ui->graphicsView->grab().toImage();
         image.save(fileName);
     }
}
