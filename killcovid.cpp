#include <QApplication>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "QGraphicsPixmapItem"
#include <QTimer>
#include "killcovid.h"
#include "scrollingbg.h"

killCovid::killCovid(user *activeUser, QObject *parent)
{
    scrollingBg* bg =  new scrollingBg();
    scrollingBg* bg1 =  new scrollingBg(NULL, 0);

    QTimer *timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(createVirus()));
    timer->start(2000);


//    this->setBackgroundBrush(QBrush(QImage(":/static_images/bg.png").scaledToHeight(689).scaledToWidth(400)));
    this->addItem(bg);
    this->addItem(bg1);
//    bg->setPos(0,0);

    this->setSceneRect(0,0,390,620);


//    player->setFlag(QGraphicsItem::ItemIsFocusable);
//    player->setFocus();
}
void killCovid::createVirus(){
//    rubbish* rubbish = new class rubbish();
//    this->addItem(rubbish);
}
