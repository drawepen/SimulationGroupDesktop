#ifndef SHOWFRAME_H
#define SHOWFRAME_H
#include <QFrame>
#include "src/controller.h"

class ShowFrame : public QFrame
{
public:
    ShowFrame(QWidget *parent);
    void setController(Controller *controller){
        this->controller=controller;
    }
protected:
    void paintEvent(QPaintEvent *event);

private:
    Controller *controller;
};

#endif // SHOWFRAME_H
