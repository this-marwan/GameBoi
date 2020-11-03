#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QGraphicsScene>
#include <QTimer>
#include <stdlib.h>
#include "stdio.h"
#include "virus.h"

virus::virus(QObject *parent) : QObject(parent)
{

    this->setPixmap((QPixmap(":/static_images/killCovid/virus-solid.png")).scaled(80,80, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    int randomPosition = rand()%350;
    this->setPos(randomPosition,0);
    this->setZValue(10);
    QTimer*timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(20);

}

void virus::update()
{
    int x = this->x();
    int y = this->y();
    if (y > 1000 || !scene()->collidingItems(this).isEmpty()){
        scene()->removeItem(this);
        delete this;
    }
    this->setPos(x,y+5);
}
