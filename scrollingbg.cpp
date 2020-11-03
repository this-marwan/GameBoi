#include "scrollingbg.h"
#include <QTimer>
#include <stdlib.h>
#include "stdio.h"
#include<QDebug>
scrollingBg::scrollingBg(QObject *parent,int start_y, int speed) : QObject(parent)
{
    this->setPixmap((QPixmap(":/static_images/bg.png")).scaled(380,698));
    this->setPos(0,start_y);
    QTimer*timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(speed);

}
void scrollingBg::update()
{
    int x = this->x();
    int y = this->y();
    if (y > 689){
        x = 0;
        y = 0;
        this->setPos(0,-698);
        qDebug() << y;
    }
    else
    {
    this->setPos(x,y+5);
    }
}
