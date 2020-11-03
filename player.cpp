#include "player.h"
#include "vaccine.h"

Player::Player(QObject *parent) : QObject(parent)
{

this->setPixmap((QPixmap(":/static_images/killCovid/syringe-solid.png")).scaled(80,80, Qt::KeepAspectRatio, Qt::SmoothTransformation));
this->setRotation(135);
this->setZValue(10);
}

void Player::keyPressEvent(QKeyEvent*event){
int x = this->x();
int y = this->y();
//limit the player's movement to stay on the screen
if(event->key() == Qt::Key_Right && x < 420){
    this->setPos(x+20,y);
}
if(event->key() == Qt::Key_Left && x > 80){
    this->setPos(x-20,y);
}

if(event->key() == Qt::Key_Space){
//shoot
    shoot();
}

}

void Player::shoot(){
    vaccine* drop = new class vaccine();
    drop->setPos(this->x()-20,this->y());
    scene()->addItem(drop);

}
