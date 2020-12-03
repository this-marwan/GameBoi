#include <QTimer>
#include <stdlib.h>
#include "stdio.h"
#include "vaccine.h"
#include "virus.h"

#include "qdebug.h"

vaccine::vaccine(QObject *parent) : QObject(parent)
{
    this->setPixmap((QPixmap(":/static_images/killCovid/tint-solid.png")).scaled(40,40, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    this->setRotation(180);
//    this->setZValue(10);
    this->timer = new QTimer(this);
    QObject::connect(this->timer, SIGNAL(timeout()), this, SLOT(update()));
    this->timer->start(10);

}

void vaccine::update()
{
    int x = this->x();
    int y = this->y();

//    QList<QGraphicsItem *> list = collidingItems() ;

//    foreach(QGraphicsItem * i , list)
//    {
//        virus * item= dynamic_cast<virus *>(i);
//        if (item)
//        {
//            scene()->removeItem(this);
//            delete i;
//            delete this;
//            return;
//        }
//    }

    if (y < -20){
        scene()->removeItem(this);
        delete this;
        return;
    }
    this->setPos(x,y-1);
}
