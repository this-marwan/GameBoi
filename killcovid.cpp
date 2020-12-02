#include <QApplication>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "QGraphicsPixmapItem"
#include <QTimer>
#include <algorithm>
#include "random"
#include "QMediaPlayer"
#include "killcovid.h"
#include "scrollingbg.h"
#include "virus.h"
#include "player.h"
#include "welcomepage.h"
#include "gameover.h"
#include "QSound"
#include "QMediaPlaylist"



#include "QDebug"

killCovid::killCovid(user *activeUser, QWidget *parent)
{
    this->parent = parent;
    this->activeUser = activeUser;

    //Set game state
    this->state = "mainMenu";

    //Start music
    //QMediaPlaylist *playlist = new QMediaPlaylist();
    //playlist->addMedia(QUrl(":qrc/static_images/killCovid/bg_audio.wav"));
    //playlist->setPlaybackMode(QMediaPlaylist::Loop);

    //this->music = new QMediaPlayer();
    //this->music->setVolume(50);
    //this->music->setPlaylist(playlist);
    //this->music->play();



    this->song = new QSound("qrc:/static_images/killCovid/bg_audio.wav");
    song->setLoops(-1);
    song->play();


    //generate sequence of viruses we will show (sum = 150)
    int a = 13;
    int b = 11;
    int c = 8;
    for(int i = 0; i < a; i++){
    this->pointSequence.push_back(3);
    }
    for(int i = 0; i < b; i++){
    this->pointSequence.push_back(5);
    }
    for(int i = 0; i < c; i++){
    this->pointSequence.push_back(7);
    }
    //shuffle our sequence to have a unique game every time
//    auto rng = std::default_random_engine {20};
    std::random_shuffle(this->pointSequence.begin(), this->pointSequence.end());

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

    //score display
    this->score = 0;
    this->scoreStr = new QGraphicsTextItem();
    this->scoreStr->setPos(5,40);
    this->scoreStr->setPlainText(QString("Score: %1").arg(this->score));
    this->scoreStr->hide();
    this->addItem(scoreStr);

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

    //add how-to panel
    howTo = new QGraphicsPixmapItem();
    howTo->setPixmap((QPixmap(":/static_images/killCovid/howTo.png")));
    howTo->setPos(this->width()/2 - 125,this->height()/2 + 50);
    this->addItem(howTo);

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
    timer->start(3000);


}
void killCovid::endGame(){

    song->stop();

    int score = this->score;

    if (score>this->activeUser->highScore)
    {
        this->activeUser->highScore = score;
        if (this->activeUser->username != "guest"){ //if not a guest we need to update the database

            //update the user score in the database
            QString val;
            QFile file;
            file.setFileName("../gameOne/users.json");
            file.open(QIODevice::ReadWrite | QIODevice::Text);
            val = file.readAll();

            QJsonDocument doc;
            doc = QJsonDocument::fromJson(val.toUtf8());

            QJsonObject RootObject = doc.object();
            QJsonObject usersObject = RootObject["users"].toObject();
            QJsonObject userObject = usersObject[this->activeUser->username].toObject();
            userObject["high_score"] = score;

            //update JSON
            userObject.insert("high_score",score);
            usersObject[this->activeUser->username] = userObject;
            RootObject["users"] = usersObject;
            doc.setObject(RootObject);

            file.resize(0);
            file.write(doc.toJson());
            file.close();
        }
    }

    this->activeUser->currentScore = score;

    gameOver *gameover = new gameOver(this->activeUser);
    gameover->show();
    delete views().first();
//    delete this;
}

void killCovid::updateScore(int score){

    this->score += score;
    this->scoreStr->setPlainText(QString("Score: %1").arg(this->score));

    if(this->score > 50){
        this->speed = 6;
    }

    if(this->score > 100){
        this->speed = 3;
    }

    if (this->score == 150)
    {
        this->state = "gameOver";
        this->endGame();
    }
}


void killCovid::lifeLost(int points){
    qDebug() << "points2 " << points;

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
        this->endGame();
    }

    this->pointSequence.push_back(points);
}

void killCovid::createVirus(){

    if (this->state == "playing")
    {
        int newVirusPoint = this->pointSequence.back();
        this->pointSequence.pop_back();
        qDebug() << newVirusPoint;
        virus* virus = new class virus(newVirusPoint, this->speed);
        int w = this->width() - 40;
        int randx = rand()%w;
        virus->setPos(20+randx ,-10);
        this->addItem(virus);
        QObject::connect(virus, SIGNAL(virusMissed(int)), this, SLOT(lifeLost(int)));
        QObject::connect(virus, SIGNAL(virusHit(int)), this, SLOT(updateScore(int)));

    }
}

void killCovid::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if (playButton->isSelected())
    {
    //play button pressed
    playButton->hide();//hide button
    howTo->hide();//hide howTo panel

    this->heart1->show();
    this->heart2->show();
    this->heart3->show();

    this->scoreStr->show();

    this->player->show();
    this->m_anim->start();

    this->player->setFocus();
    this->state = "playing";
    }

}

void killCovid::keyPressEvent(QKeyEvent*event){
    if(event->key() == Qt::Key_F1){
        //play button pressed
        playButton->hide();//hide button
        howTo->hide();//hide howTo panel

        this->heart1->show();
        this->heart2->show();
        this->heart3->show();

        this->scoreStr->show();

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

