#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "modelsetting.h"
#include "modelexamples.h"
#include "src/data/model.h" //???引用头文件报错找不到方法[已解决：makefile文件中被引用的文件要在前声明]
#include <math.h>
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QPixmap>

MainWindow::MainWindow(char *path,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    controller.setRootPath(path);
    ui->setupUi(this);
    ui->mapShowFrame->setController(&controller);
    setMouseTracking(true);  //激活鼠标追踪
    ui->centralwidget->setMouseTracking(true);
    ui->mapShowFrame->setMouseTracking(true);
    ui->toolFrame->setMouseTracking(true);

    timer.stop();
    connect(&timer,&QTimer::timeout,this,&MainWindow::timerUpdate);

    ui->speedSlider->setValue(controller.getSpeed());
    ui->speedShowLabel->setText(QString::number(controller.getSpeed(), 10));
    //操作
    ui->operationTypeCombo->setCurrentIndex(controller.getOperationType());
    ui->operationValueSpin->setValue(controller.getOperationValue());
    ui->operationValueSpin2->setValue(controller.getOperationValue2());
    ui->intervalSymbolLable->setVisible(controller.getOperationType()==2);
    ui->operationValueSpin2->setVisible(controller.getOperationType()==2);
    ui->randButton->setChecked(false);
    ui->nextFrameButton->setToolTip("下一帧");
    ui->lastFrameButton->setToolTip("上一帧");
    ui->resetButton->setToolTip("重置");
    ui->curTypeButton1->setToolTip("无操作");
    ui->curTypeButton2->setToolTip("单元胞");
    ui->curTypeButton3->setToolTip("全区");
    ui->curTypeButton4->setToolTip("选区");
    ui->speedSlider->setToolTip("速度调控");

    QIcon icon1,icon2,icon3,icon4;
    icon1.addFile(tr(":/image/cur/resources/resizeApi1.ico"));
    ui->curTypeButton1->setIcon(icon1);
    ui->curTypeButton1->setIconSize(QSize(26,26));
    icon2.addFile(tr(":/image/cur/resources/cur_set.ico"));
    ui->curTypeButton2->setIcon(icon2);
    ui->curTypeButton2->setIconSize(QSize(26,26));
    icon3.addFile(tr(":/image/cur/resources/resizeApi3.ico"));
    ui->curTypeButton3->setIcon(icon3);
    ui->curTypeButton3->setIconSize(QSize(26,26));
    icon4.addFile(tr(":/image/cur/resources/cur_enlarge.ico"));
    ui->curTypeButton4->setIcon(icon4);
    ui->curTypeButton4->setIconSize(QSize(26,26));
    curType=controller.getCurType();
    switch (curType) {
    case 1:
        ui->curTypeButton1->setChecked(true);
        break;
    case 2:
        ui->curTypeButton2->setChecked(true);
        break;
    case 3:
        ui->curTypeButton3->setChecked(true);
        break;
    case 4:
        ui->curTypeButton4->setChecked(true);
        break;
    }

    ui->stateTable->verticalHeader()->setMinimumWidth(16);
    ui->stateTable->setColumnWidth(0,80);
    ui->stateTable->setColumnWidth(1,ui->stateTable->width()-96-2);

    QIcon icon;
    icon.addFile(tr(":/image/button/resources/reset.png"));
    ui->resetButton->setIcon(icon);
    ui->resetButton->setIconSize(ui->resetButton->size()-QSize(4,4));

    ui->label_6->setVisible(false);
    ui->label_7->setVisible(false);
    ui->cpuUseLabel->setVisible(false);
    ui->ramUseLabel->setVisible(false);

    oldValueType=controller.getValueType();
    ui->seniorOperationTable->setVisible(false);
    ui->addOperationButton->setVisible(false);
    on_addOperationButton_clicked();

    initChart();
    updateChart();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initChart(){
    //WARNING释放旧控件的内存会报错,可能重新设置会自动释放内存，暂时不释放，待解决
    allStateSeries.clear();
    maxStatistic=INT32_MIN;
    specialEffType=0;

    allStateChart=new QChart();
    allStateChart->setAnimationOptions(QChart::AllAnimations);//设置动画
    allStateChart->layout()->setContentsMargins(0, 0, 0, 0);//设置外边界
    allStateChart->setMargins(QMargins(0, 0, 0, 0));//设置内边界
    allStateChart->setBackgroundRoundness(4);//设置背景区域圆角
    allStateChart->legend()->setVisible(true);

    allStateAxisX=new QValueAxis();
    allStateAxisX->setRange(0,60);
    allStateAxisX->setGridLineVisible(true);
    allStateAxisX->setTickCount(6+1);     //标记的个数
    allStateAxisX->setMinorTickCount(4); //次标记的个数

    allStateAxisY=new QValueAxis();
    allStateAxisY->setRange(0,0);
    allStateAxisY->setGridLineVisible(true);
    allStateAxisY->setTickCount(5+1);
    allStateAxisY->setMinorTickCount(4);

    allStateAxisY2=new QValueAxis();
    allStateAxisY2->setRange(0,1);
    allStateAxisY2->setGridLineVisible(true);
    allStateAxisY2->setTickCount(5+1);
    allStateAxisY2->setMinorTickCount(4);

    allStateChart->addAxis(allStateAxisX, Qt::AlignBottom);
    allStateChart->addAxis(allStateAxisY, Qt::AlignLeft);
    allStateChart->addAxis(allStateAxisY2,Qt::AlignRight);

    ui->graphicsView->setChart(allStateChart);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    //饼状图
    nowStateChart = new QChart();
    nowStateSeries = new QPieSeries();

    nowStateChart->addSeries(nowStateSeries);
    nowStateChart->setAnimationOptions(QChart::AllAnimations);//设置动画
    nowStateChart->layout()->setContentsMargins(0, 0, 0, 0);//设置外边界
    nowStateChart->setMargins(QMargins(0, 0, 0, 0));//设置内边界
    nowStateChart->setBackgroundRoundness(4);//设置背景区域圆角
    nowStateChart->legend()->hide();//不显示图例

    ui->graphicsView_3->setChart(nowStateChart);
    ui->graphicsView_3->setRenderHint(QPainter::Antialiasing);//抗锯齿处理
}

void MainWindow::updateChart(){
    //TODO添加是否显示，仅添加点，不显示
//    if(ui->graphicsView->isVisible())
    if(specialEffType==0){
        specialEffType=1;
    }else if(specialEffType==1){
        allStateChart->setAnimationOptions(QChart::NoAnimation);
        nowStateChart->setAnimationOptions(QChart::NoAnimation);
        specialEffType=2;
    }
    //当前状态
    nowStateSeries->clear();
    std::vector<std::pair<int,int>> &statistics=controller.getStatistics();
    int sum=0,maxS=INT32_MIN;
    for(std::pair<int,int> statistic:statistics){
        sum+=statistic.second;
    }
    QList<QPieSlice *> slices;
    for(std::pair<int,int> statistic:statistics){
        QPieSlice *slice=new QPieSlice(QString::number(statistic.first)+":"+QString::number(statistic.second)+
                                       ","+QString::number(statistic.second*100.0/sum,'f',1)+"%",statistic.second);
        QColor color=QColor(rand()%256,rand()%256,rand()%256);
        slice->setColor(color);
        QFont font=slice->labelFont();
        font.setPointSize(8);
        slice->setLabelFont(font);
        slices.append(slice);
        maxS=std::max(maxS,statistic.second);
    }
    nowStateSeries->append(slices);
    nowStateSeries->setLabelsVisible();
    nowStateChart->update();

    //全状态
    if(controller.getNowTime()==controller.getRunTime()){
        bool deleteMaxS=false;
        for(std::pair<int,int> statistic:statistics){
            QLineSeries *series;
            auto iter=allStateSeries.find(statistic.first);
            if(iter!=allStateSeries.end()){
                series=iter->second;
            }else{
                series=new QLineSeries();
                series->setName(QString::number(statistic.first));
                allStateChart->addSeries(series);

                allStateChart->setAxisX(allStateAxisX,series);
                allStateChart->setAxisY(allStateAxisY,series);
                allStateSeries.insert(std::pair<int,QLineSeries*>(statistic.first,series));
            }
            int vX=controller.getRunTime();
            if(series->count()==0 || series->at(series->count()-1).x()!=vX){
                series->append(vX,statistic.second);
            }else{
                if(series->at(series->count()-1).y()==maxStatistic){
                    deleteMaxS=true;
                }
                series->replace(series->count()-1,QPointF(vX,statistic.second));
            }
        }
        if(maxS>maxStatistic){
            allStateChart->axisY()->setRange(0,maxS);
            if(maxS<=sum){
                allStateAxisY2->setRange(0,maxS*100.0/sum);
            }
            maxStatistic=maxS;
        }else if(deleteMaxS){
            int maxV=INT32_MIN;
            for(auto iter:allStateSeries){
                QLineSeries *series=iter.second;
                for(QPointF point:series->pointsVector()){
                    if(point.y()>maxV){
                        maxV=point.y();
                    }
                }
            }
            allStateChart->axisY()->setRange(0,maxV);
            if(maxV<=sum){
                allStateAxisY2->setRange(0,maxV*100.0/sum);
            }
            maxStatistic=maxV;
        }
    }
    if(controller.getNowTime()>60){
        allStateChart->axisX()->setRange(0,controller.getNowTime());
    }

    allStateChart->update();
}
//鼠标事件
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QPoint point=event->pos();
    if(event->button()==Qt::LeftButton)
    {
        QPoint point1=point - ui->centralwidget->pos()- ui->mapShowFrame->pos();
        mousePressState=1;
        clickEvent(point1);
        //窗口缩放
        winZoomType=0;
        switch (1) {
        case 1:{
            QPoint point1=point-ui->centralwidget->pos()-
                    ui->mapShowFrame->pos()-ui->widget_6->pos();
            int x=point1.x(),y=point1.y();
            if (x>=0 && x<ui->widget_6->width() && y>=0 && y<ui->widget_6->height())
            {
                winZoomType=1;
                winZoomOriX=point.x();
                winZoomOriY=point.y();
                break;
            }
        }
        case 2:{
            QPoint point1=ui->widget_7->mapFromGlobal(QCursor().pos());
            int x=point1.x(),y=point1.y();
            if (x>=0 && x<ui->widget_7->width() && y>=0 && y<ui->widget_7->height())
            {
                winZoomType=2;
                winZoomOriX=point.x();
                winZoomOriY=point.y();
                break;
            }
        }
        }
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    QPoint point=event->pos() - ui->centralwidget->pos() -ui->mapShowFrame->pos();
    if(event->buttons() & Qt::LeftButton)
    {
        clickEvent(point);
        //窗口缩放
        switch (winZoomType) {
        case 1:{
            QPoint point=event->pos();
            int relX=point.x()-winZoomOriX;
            if(relX!=0 && !(relX<0 && ui->mapShowFrame->width()<=ui->mapShowFrame->minimumWidth())
                    && !(relX>0 && ui->frame->minimumWidth()<=0)){
                winZoomOriX=point.x();
                winZoomOriY=point.y();
                ui->frame->setMinimumWidth(ui->frame->minimumWidth()-relX);
            }
        }
            break;
        case 2:{
            QPoint point=event->pos();
            int relY=point.y()-winZoomOriY;
            if(relY!=0 && !(relY<0 && ui->graphicsView_3->height()<=80)
                    && !(relY>0 && ui->graphicsView->height()<=66)){
                winZoomOriX=point.x();
                winZoomOriY=point.y();
                ui->graphicsView->setMinimumHeight(ui->graphicsView->height()-relY);
                ui->graphicsView->setMaximumHeight(ui->graphicsView->minimumHeight());
            }
        }
            break;
        }
    }
    int x=point.x();
    int y=point.y();
    int cellWidth,cellHeight;
    cellWidth=ui->mapShowFrame->width()/controller.getCellColNum();
    cellHeight=ui->mapShowFrame->height()/controller.getCellRowNum();
    cellWidth=cellHeight=min(cellWidth,cellHeight);
    if(cellWidth==0){
        return;
    }
    int cellX=x/cellWidth;
    int cellY=y/cellHeight;
    if(x>=0 && cellX<controller.getCellColNum() && cellX!=this->cellX)
    {
        ui->cellXSpin->setValue(cellX);
    }
    if(y>=0 && cellY<controller.getCellRowNum() && cellY!=this->cellY)
    {
        ui->cellYSpin->setValue(cellY);
    }
    //TODO去除重复update
    ui->mapShowFrame->update();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event){
    if(event->button()==Qt::LeftButton)
    {
        winZoomType=0;
        if(curType==4){
            if(mousePressState!=0){
                QPoint point1=event->pos() - ui->centralwidget->pos()- ui->mapShowFrame->pos();
                mousePressState=2;
                clickEvent(point1);
            }
        }else{
            if(mousePressState!=0){
                controller.setStartCellXY(-1,-1);
                mousePressState=0;
            }
        }
    }else if(event->button()==Qt::RightButton){
        if(curType==4 && mousePressState!=0){
            controller.setStartCellXY(-1,-1);
            mousePressState=0;
            ui->mapShowFrame->update();
        }
    }
}

void MainWindow::timerUpdate()
{
    controller.selfAddNowTime();//TODO改为自增一帧，可播放历史快照
    updateProgress();
    monitorFix();
}

//绘图
void MainWindow::paintEvent(QPaintEvent *qPaintEvent)
{
//    ui->mapShowFrame->update();
}

//播放控件
void MainWindow::on_startPushButton_clicked()
{
    if(startButtion==1 || startButtion==3){
        timer.start(1000/controller.getSpeed());
        ui->startPushButton->setText("II");
        startButtion=2;
    }else if(startButtion==2){
        timer.stop();
        ui->startPushButton->setText("▶");
        startButtion=3;
    }
}

void MainWindow::on_speedSlider_valueChanged(int arg1)
{
    controller.setSpeed(ui->speedSlider->maximum()/(std::max(ui->speedSlider->maximum()-arg1,1))*arg1);
    ui->speedShowLabel->setText(QString::number(controller.getSpeed(), 10));
    if(timer.isActive()){
        timer.start(1000/controller.getSpeed());
    }
}

void MainWindow::on_nextFrameButton_clicked()
{
    timerUpdate();
    if(controller.getNowTime()==controller.getRunTime()){
        monitorFix();
    }
}

void MainWindow::on_lastFrameButton_clicked()
{
    controller.selfSubNowTime();
    updateProgress();
}

void MainWindow::on_progressSlider_valueChanged(int arg1)
{
    controller.setNowTime(arg1);
    ui->nowTimeLabel->setText(QString::number(controller.getNowTime(),10));
    //TODO去除重复update
    ui->mapShowFrame->update();
    updateChart();
}

void MainWindow::updateProgress(){
    ui->runTimeLabel->setText(QString::number(controller.getRunTime(),10));
    ui->progressSlider->setMaximum(controller.getRunTime());
    ui->progressSlider->setValue(controller.getNowTime());
    monitorDyn();
}

void MainWindow::reShowMap()
{
    ui->nowTimeLabel->setText(QString::number(controller.getNowTime(),10));
    ui->runTimeLabel->setText(QString::number(controller.getRunTime(),10));
    ui->progressSlider->setValue(controller.getNowTime());
    initChart();//TODO注意释放内存
    updateChart();
}
//操作
void MainWindow::clickEvent(QPoint &point)
{
    if(winZoomType!=0){
        return;
    }
    int cellColNum,cellRowNum,cellWidth,cellHeight;
    cellColNum=controller.getCellColNum();
    cellRowNum=controller.getCellRowNum();
    cellWidth=ui->mapShowFrame->width()/cellColNum;
    cellHeight=ui->mapShowFrame->height()/cellRowNum;
    cellWidth=cellHeight=min(cellWidth,cellHeight);

    int x=point.x();
    int y=point.y();
    int cellX=x/cellWidth;
    int cellY=y/cellHeight;
    if(x>=0 && cellX<cellColNum && y>=0 && cellY<cellRowNum)
    {
        bool change=false;
        if(curType==2){
            controller.clickCell(cellX,cellY);
            change=true;
        }else if(curType==3){
            controller.allClick();
            change=true;
        }else if(curType==4){
            if(mousePressState==1){
                startCellX=cellX;
                startCellY=cellY;
                controller.setStartCellXY(startCellX,startCellY);
                ui->mapShowFrame->update();
                mousePressState=3;
            }else if(mousePressState==2){
                controller.clickCell(startCellX,startCellY,cellX,cellY);
                controller.setStartCellXY(-1,-1);
                change=true;
            }
        }
        showState();
        if(change){
            ui->mapShowFrame->update();
            updateChart();
        }
    }
    if(mousePressState==2){
        controller.setStartCellXY(-1,-1);
        mousePressState=0;
    }
}

void MainWindow::showState()
{
    int rowCount=ui->stateTable->rowCount();
    if(rowCount!=1){
        ui->stateTable->setRowCount(1);
        for(int i=0;i<1;++i){
            QTableWidgetItem *item=new QTableWidgetItem("-");
            item->setTextAlignment(Qt::AlignCenter);
            ui->stateTable->setItem(i,0,item);
        }
    }
    if(cellX>=0&&cellX<controller.getCellColNum() && cellY>=0 && cellY<=controller.getCellRowNum()){
        for(int i=0;i<1;++i){
            ui->stateTable->item(i,0)->setText(QString::number(controller.getState(cellX,cellY)));
        }
    }else{
        for(int i=0;i<1;++i){
            ui->stateTable->item(i,0)->setText("-");
        }
    }
}

void MainWindow::on_operationTypeCombo_activated(int index)
{
    controller.setOperationType(index);
}

void MainWindow::on_operationValueSpin_valueChanged(int arg1)
{
    controller.setOperationValue(arg1);
}

void MainWindow::on_cellXSpin_valueChanged(int arg1)
{
    if(cellX!=arg1)
    {
        cellX=arg1;
        showState();
    }
}

void MainWindow::on_cellYSpin_valueChanged(int arg1)
{
    if(cellY!=arg1)
    {
        cellY=arg1;
        showState();
    }
}

void MainWindow::on_operationValueSpin2_valueChanged(int arg1)
{
    controller.setOperationValue2(arg1);
}

void MainWindow::on_randButton_clicked(bool checked)
{
    ui->intervalSymbolLable->setVisible(checked);
    ui->operationValueSpin2->setVisible(checked);
    controller.setValueType(checked);
}

void MainWindow::on_curTypeButton1_clicked(bool checked)
{
    if(checked){
        curType=1;
        controller.setCurType(1);
        ui->curTypeButton2->setChecked(false);
        ui->curTypeButton3->setChecked(false);
        ui->curTypeButton4->setChecked(false);
        ui->mapShowFrame->setCursor(Qt::ArrowCursor);
        ui->frame_2->setMinimumHeight(0);
    }
}

void MainWindow::on_curTypeButton2_clicked(bool checked)
{
    if(checked){
        curType=2;
        controller.setCurType(2);
        ui->curTypeButton1->setChecked(false);
        ui->curTypeButton3->setChecked(false);
        ui->curTypeButton4->setChecked(false);
        ui->mapShowFrame->setCursor(Qt::PointingHandCursor);
//        ui->mapShowFrame->setCursor(QCursor(QPixmap(":/image/cur/resources/cur_set.ico"),-1,-1));
        ui->frame_2->setMinimumHeight(operationWinHeight);
    }
}

void MainWindow::on_curTypeButton3_clicked(bool checked)
{
    if(checked){
        curType=3;
        controller.setCurType(3);
        ui->curTypeButton1->setChecked(false);
        ui->curTypeButton2->setChecked(false);
        ui->curTypeButton4->setChecked(false);
        ui->mapShowFrame->setCursor(Qt::OpenHandCursor);
        ui->frame_2->setMinimumHeight(operationWinHeight);
    }
}

void MainWindow::on_curTypeButton4_clicked(bool checked)
{
    if(checked){
        curType=4;
        controller.setCurType(4);
        ui->curTypeButton1->setChecked(false);
        ui->curTypeButton2->setChecked(false);
        ui->curTypeButton3->setChecked(false);
        ui->mapShowFrame->setCursor(Qt::CrossCursor);
        ui->frame_2->setMinimumHeight(operationWinHeight);
    }
}

void MainWindow::on_resetButton_clicked()
{
    if (QMessageBox::question(this, "提示", "确定要重置吗?", QMessageBox::Yes|QMessageBox::No) == QMessageBox::Yes) {
        if(startButtion==2){
            timer.stop();
            ui->startPushButton->setText("▶");
            startButtion=1;
        }
        controller.init();
        reShowMap();
    }
}

//菜单
void MainWindow::on_modelSet_triggered()
{
    if(startButtion==2){
        timer.stop();
        ui->startPushButton->setText("▶");
        startButtion=3;
    }

    ModelSetting *ms=new ModelSetting(nullptr,this);
    ms->setWindowModality(Qt::ApplicationModal);//在关闭当前窗口前无法操作其他窗口
    ms->setAttribute(Qt::WA_DeleteOnClose,true);
    ms->show();
}

void MainWindow::on_exportMapImage_triggered()
{
    QDateTime localTime(QDateTime::currentDateTimeUtc().toLocalTime());
    QString fileName = QFileDialog::getSaveFileName(this,
                 tr("保存地图"),localTime.toString("yyyyMMddhhmmss")+".png",
                 tr("*.png;; *.jpg;; *.gif;; *.bmp;; *.tif")); //选择路径
    if(!fileName.isEmpty()){
        QImage image = ui->mapShowFrame->grab().toImage();
        image.save(fileName);
    }
}

void MainWindow::on_exportNowStaImage_triggered()
{
    QDateTime localTime(QDateTime::currentDateTimeUtc().toLocalTime());
    QString fileName = QFileDialog::getSaveFileName(this,
                  tr("保存统计图(当前状态)"),localTime.toString("yyyyMMddhhmmss")+".png",
                  tr("*.png;; *.jpg;; *.gif;; *.bmp;; *.tif")); //选择路径
    if(!fileName.isEmpty()){
         QImage image = ui->graphicsView_3->grab().toImage();
         image.save(fileName);
     }
}

void MainWindow::on_exportAllStaImage_triggered()
{
    QDateTime localTime(QDateTime::currentDateTimeUtc().toLocalTime());
    QString fileName = QFileDialog::getSaveFileName(this,
                  tr("保存统计图(全状态)"),localTime.toString("yyyyMMddhhmmss")+".png",
                  tr("*.png;; *.jpg;; *.gif;; *.bmp;; *.tif")); //选择路径
    if(!fileName.isEmpty()){
         QImage image = ui->graphicsView->grab().toImage();
         image.save(fileName);
     }
}

void MainWindow::on_useDoc_triggered()
{
    //...
}

void MainWindow::on_seniorOperationSwitch_triggered()
{
    if(controller.getValueType()==2){
        controller.setValueType(oldValueType);
        ui->seniorOperationSwitch->setText("高级操作：关");
        operationWinHeight=41;
        ui->frame_2->setMinimumHeight(operationWinHeight);
        ui->frame_2->setMaximumHeight(operationWinHeight);
        ui->graphicsView->setMinimumHeight(ui->graphicsView->minimumHeight()+60);
        ui->graphicsView->setMaximumHeight(ui->graphicsView->minimumHeight());
        ui->seniorOperationTable->setVisible(false);
        ui->addOperationButton->setVisible(false);
    }else{
        oldValueType=controller.getValueType();
        controller.setValueType(2);
        ui->seniorOperationSwitch->setText("高级操作：开");
        operationWinHeight+=60;
        ui->frame_2->setMinimumHeight(operationWinHeight);
        ui->frame_2->setMaximumHeight(operationWinHeight);
        ui->graphicsView->setMinimumHeight(ui->graphicsView->minimumHeight()-60);
        ui->graphicsView->setMaximumHeight(ui->graphicsView->minimumHeight());
        ui->seniorOperationTable->setVisible(true);
        ui->addOperationButton->setVisible(true);
    }
//    ui->seniorOperationSwitch->setVisible(true);
    ui->menu_3->setVisible(true);
}

void MainWindow::on_action_rs_triggered(){
    if(statisticswindow==nullptr){
        statisticswindow=new StatisticsWindow();
    }
    statisticswindow->show();
    statisticswindow->raise();
}

void MainWindow::on_modelnew_triggered(){
    ModelExamples *me=new ModelExamples(nullptr,this);
    me->setWindowModality(Qt::ApplicationModal);//在关闭当前窗口前无法操作其他窗口
    me->setAttribute(Qt::WA_DeleteOnClose,true);
    me->show();
}

void MainWindow::on_actionModelSave_triggered(){
    bool ok;
    QString text = QInputDialog::getText(this, tr("保存模型"),tr("请输入模型名称"), QLineEdit::Normal,controller.getModelName().c_str(), &ok);
    if (ok && !text.isEmpty())
    {
        if(controller.checkExisModel(text.toStdString())!=-1){
            QMessageBox::StandardButton btn = QMessageBox::question(this, "提示", "模型以存在，是否覆盖?", QMessageBox::Yes|QMessageBox::No);
            if (btn != QMessageBox::Yes) {
                return;
            }
        }
        controller.saveModel(text.toStdString());
    }
}

//监控
void MainWindow::monitorDyn()
{
    ui->timeSpend->setText(QString().setNum(controller.getTimeSpend()*1.0/1000,'f',3));
}

DWORD getWinMemUsage(){
    MEMORYSTATUS ms;
    ::GlobalMemoryStatus(&ms);
    return ms.dwMemoryLoad*ms.dwAvailPhys/100;
}

void MainWindow::monitorFix()
{
//    ui->ramUseLabel->setText(QString::number(getWinMemUsage()/1000000)+"MB,"+"%");
//    ui->cpuUseLabel->setText(QString::number(getWinCpuUsage())+"%");
}

void MainWindow::on_addOperationButton_clicked()
{
    int row = ui->seniorOperationTable->rowCount();
    ui->seniorOperationTable->insertRow(row);

    QTableWidgetItem *item0=new QTableWidgetItem("0");
    QTableWidgetItem *item1=new QTableWidgetItem("0");
    QTableWidgetItem *item2=new QTableWidgetItem("1");
    QTableWidgetItem *item3=new QTableWidgetItem("删除");
    item0->setTextAlignment(Qt::AlignCenter);
    item1->setTextAlignment(Qt::AlignCenter);
    item2->setTextAlignment(Qt::AlignCenter);
    item3->setTextAlignment(Qt::AlignCenter);
    item3->setForeground(QBrush(Qt::red));
    item3->setFlags(item0->flags() & (~Qt::ItemIsEditable));

    ui->seniorOperationTable->blockSignals(true);
    tableChanging=1;
    ui->seniorOperationTable->setItem(row,0,item0);//没有默认QTableWidgetItem，需要先添加
    ui->seniorOperationTable->setItem(row,1,item1);
    tableChanging=0;
    ui->seniorOperationTable->setItem(row,2,item2);
    ui->seniorOperationTable->setItem(row,3,item3);
    ui->seniorOperationTable->blockSignals(false);
    on_seniorOperationTable_itemChanged(item2);
}

void MainWindow::on_seniorOperationTable_itemChanged(QTableWidgetItem *item)
{
    if(item==NULL){
        return;
    }
    if(item->column()==3){
        return;
    }else if(item->column()==2){
        QRegExp reg(QString("([0-9]\\.\\d+)|([1-9]\\d+\\.\\d+)|([0-9])|([1-9][0-9]+)"));
        if(!reg.exactMatch(item->text())){
            item->setText(oldTableText);
            return;
        }
    }else{
        QRegExp reg(QString("(-?[1-9][0-9]+)|(-?[0-9])"));
        if(!reg.exactMatch(item->text())){
            item->setText(oldTableText);
            return;
        }
    }
    if(tableChanging==0){
        int row=item->row();
        QString text0=ui->seniorOperationTable->item(row,0)->text();
        QString text1=ui->seniorOperationTable->item(row,1)->text();
        QString text2=ui->seniorOperationTable->item(row,2)->text();
        controller.setProbValues(row,text0.toInt(),text1.toInt(),text2.toDouble());
    }
}

void MainWindow::on_seniorOperationTable_itemSelectionChanged()
{
    if(ui->seniorOperationTable->currentItem()!=NULL){
        oldTableText=ui->seniorOperationTable->currentItem()->text();
    }
}

void MainWindow::on_seniorOperationTable_cellClicked(int row, int column)
{
    if(column==3){
        QMessageBox::StandardButton btn = QMessageBox::question(this, "提示", "确定要删除吗?", QMessageBox::Yes|QMessageBox::No);
        if (btn == QMessageBox::Yes) {
            ui->seniorOperationTable->removeRow(row);
            controller.removeProbValues(row);
        }
    }
}
