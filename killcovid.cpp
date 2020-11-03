#include <QApplication>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "QGraphicsPixmapItem"
#include <QTimer>
#include "killcovid.h"
#include "scrollingbg.h"
#include "player.h"

#include "QDebug"

killCovid::killCovid(user *activeUser, QObject *parent)
{
    //Set game state
    this->state = "mainMenu";

    //Create a scrolling background
    scrollingBg* bg =  new scrollingBg();
    scrollingBg* bg1 =  new scrollingBg(NULL, -3);

    this->addItem(bg);
    this->addItem(bg1);
    this->setSceneRect(0,0,390,620);

    //Add play button
    playButton = new QGraphicsPixmapItem();
    playButton->setPixmap((QPixmap(":/static_images/killCovid/play-circle-solid.svg")).scaled(100,100));
    playButton->setPos(this->width()/2 - 50,this->height()/2 - 50);
    playButton->setFlag(QGraphicsItem::ItemIsSelectable,true);
    this->addItem(playButton);

    //add Player
    this->player = new Player();
    this->player->setPos(this->width()/2 - 40,this->height()+10);
    this->player->setFlag(QGraphicsItem::ItemIsFocusable);
    this->player->hide();
    this->addItem(this->player);

    //animation to enter the player
    this->m_anim = new QPropertyAnimation(this->player, "y" , this->player);
    this->m_anim->setDuration(1000);
    this->m_anim->setStartValue(this->height() + 50);
    this->m_anim->setEndValue(this->height() - 50);
    this->m_anim->setEasingCurve(QEasingCurve::Linear);

    //When game starts add these
    QTimer *timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(createVirus()));
    timer->start(2000);

}
void killCovid::createVirus(){



//    rubbish* rubbish = new class rubbish();
//    this->addItem(rubbish);
}

void killCovid::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if (playButton->isSelected())
    {
    //play button pressed
    playButton->hide();//hide button
    this->player->show();
    this->m_anim->start();
    this->player->setFocus();
    this->state = "playing";
    }

}

void killCovid::keyPressEvent(QKeyEvent*event){
    if(event->key() == Qt::Key_F1){
    //F1 button pressed
    playButton->hide();//hide button
    this->player->show();
    this->m_anim->start();
    this->player->setFocus();
    this->state = "playing";
    }

    int x = this->player->x();
    int y = this->player->y();
    //limit the player's movement to stay on the screen
    if(event->key() == Qt::Key_Right && x < 420){
        this->player->setPos(x+20,y);
    }
    if(event->key() == Qt::Key_Left && x > 80){
        this->player->setPos(x-20,y);
    }
    if(event->key() == Qt::Key_Space && this->state == "playing"){
    this->player->shoot();
    }

}

