#include <QApplication>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "QGraphicsPixmapItem"
#include <QTimer>
#include "killcovid.h"
#include "scrollingbg.h"
#include "virus.h"
#include "player.h"

#include "QDebug"

killCovid::killCovid(user *activeUser, QObject *parent)
{
    //Set game state
    this->state = "mainMenu";

    //number of lives left
    this->lives = 3;
    this->heart1 = new QGraphicsPixmapItem();
    this->heart1->setPixmap((QPixmap(":/static_images/killCovid/heart-solid.png")).scaled(30,30));
    this->heart1->setPos(5,5);
    this->heart1->hide();
    this->addItem(heart1);

    this->heart2 = new QGraphicsPixmapItem();
    this->heart2->setPixmap((QPixmap(":/static_images/killCovid/heart-solid.png")).scaled(30,30));
    this->heart2->setPos(40,5);
    this->heart2->hide();
    this->addItem(heart2);

    this->heart3 = new QGraphicsPixmapItem();
    this->heart3->setPixmap((QPixmap(":/static_images/killCovid/heart-solid.png")).scaled(30,30));
    this->heart3->setPos(75,5);
    this->heart3->hide();
    this->addItem(heart3);

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
    timer->start(4000);

}


void killCovid::lifeLost(){

    this->lives -= 1;
    if (lives == 2){
        this->heart3->setPixmap((QPixmap(":/static_images/killCovid/heart-solid-dead.png")).scaled(30,30));
    } else if (lives == 1)
    {
        this->heart2->setPixmap((QPixmap(":/static_images/killCovid/heart-solid-dead.png")).scaled(30,30));
    }
    else if (lives <= 0)
    {
        this->heart1->setPixmap((QPixmap(":/static_images/killCovid/heart-solid-dead.png")).scaled(30,30));
    }

    if (lives == 0)
    {
        this->state = "gameOver";
    }
    qDebug() << "deady";
}

void killCovid::createVirus(){

    if (this->state == "playing")
    {
        virus* virus = new class virus(this);
        int w = this->width() - 40;
        int randx = rand()%w;
        virus->setPos(20+randx ,-10);
        this->addItem(virus);
        QObject::connect(virus, SIGNAL(virusMissed()), this, SLOT(lifeLost()));

    }
}

void killCovid::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if (playButton->isSelected())
    {
    //play button pressed
    playButton->hide();//hide button

    this->heart1->show();
    this->heart2->show();
    this->heart3->show();

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

