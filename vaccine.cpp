#include <QTimer>
#include <stdlib.h>
#include "stdio.h"
#include "vaccine.h"

vaccine::vaccine(QObject *parent) : QObject(parent)
{
    this->setPixmap((QPixmap(":/static_images/killCovid/tint-solid.png")).scaled(40,40, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    this->setRotation(180);
    this->setZValue(10);
    QTimer*timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(20);

}

void vaccine::update()
{
    int x = this->x();
    int y = this->y();
    if (y < -20 || scene()->collidingItems(this).count() > 2){
        scene()->removeItem(this);
        delete this;
    }
    this->setPos(x,y-5);
}
