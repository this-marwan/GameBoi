#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QGraphicsScene>
#include <QTimer>
#include <stdlib.h>
#include "stdio.h"
#include "virus.h"
#include "killcovid.h"
#include "vaccine.h"
#include "qdebug.h"

virus::virus(QObject *parent) : QObject(parent)
{

    this->setPixmap((QPixmap(":/static_images/killCovid/virus-solid.png")).scaled(80,80, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    int randomPosition = rand()%350;
    this->setPos(randomPosition,0);
    this->setZValue(10);
    this->timer = new QTimer(this);
    QObject::connect(this->timer, SIGNAL(timeout()), this, SLOT(update()));
    this->timer->start(100);

}

void virus::die(){
}

void virus::update()
{
    int x = this->x();
    int y = this->y();

    QList<QGraphicsItem *> list = collidingItems() ;

    foreach(QGraphicsItem * i , list)
    {
        vaccine * item= dynamic_cast<vaccine *>(i);
        if (item)
        {
            scene()->removeItem(this);
            delete this;
            return;
        }
    }


    if (y > scene()->height() ){
        scene()->removeItem(this);
        emit virusMissed();
        delete this;
    }
    this->setPos(x,y+10);
}
