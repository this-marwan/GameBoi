#include "scrollingbg.h"
#include <QTimer>
#include <stdlib.h>
#include "stdio.h"
#include<QDebug>
scrollingBg::scrollingBg(QObject *parent,int start_y, int speed) : QObject(parent)
{
    this->setPixmap((QPixmap(":/static_images/killCovid/bg2.png")).scaled(380,698));
    this->setPos(0,start_y);
    this->setZValue(-1);
    QTimer*timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(scroll()));
    timer->start(speed);

}
void scrollingBg::scroll()
{
    int x = this->x();
    int y = this->y();
    if (y > 689){
        x = 0;
        y = 0;
        this->setPos(0,-698);
    }
    else
    {
    this->setPos(x,y+1);
    }
}

void scrollingBg::updateSpeed(int x){
    this->timer->setInterval(x);
}
