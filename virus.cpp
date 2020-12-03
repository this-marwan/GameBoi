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

virus::virus(int points, int speed, QObject *parent) : QObject(parent)
{
    this->points = points;
    if(speed <= 0) {speed = 1;};
    this->speed = speed;

    if (points == 3)
    {
    this->setPixmap((QPixmap(":/static_images/killCovid/virus-solid_3.png")).scaled(80,80, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
    else if (points == 5)
    {
    this->setPixmap((QPixmap(":/static_images/killCovid/virus-solid_5.png")).scaled(60,60, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
    else if (points == 7)
    {
    this->setPixmap((QPixmap(":/static_images/killCovid/virus-solid_7.png")).scaled(40,40, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }

    int randomPosition = rand()%350;
    this->setPos(randomPosition,0);
    this->setZValue(10);
    this->timer = new QTimer(this);
    QObject::connect(this->timer, SIGNAL(timeout()), this, SLOT(update()));
    this->timer->start(speed);

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
            emit virusHit(this->points);
            delete i;
            delete this;
            return;
        }
    }


    if (y > scene()->height() ){
        scene()->removeItem(this);
        qDebug() << "points2 " << this->points;
        emit virusMissed(this->points);
        delete this;
        return;
    }
    this->setPos(x,y+1);
}
