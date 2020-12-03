#ifndef KILLCOVID_H
#define KILLCOVID_H

#include <QObject>
#include <QWidget>
#include <QGraphicsScene>
#include <QTimer>

#include "user.h"
#include <QtWidgets>
#include <QPixmap>
#include "QMediaPlayer"
#include "QSound"
#include "user.h"
#include "player.h"

class killCovid : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit killCovid(user *activeUser, QWidget *parent = nullptr);
    QTimer *timer;
    QWidget *parent;
    user *activeUser;
    QGraphicsPixmapItem* playButton;
    QGraphicsPixmapItem* howTo;
    QGraphicsPixmapItem* settingsButton;
    Player* player;
    QPropertyAnimation* m_anim;
    QGraphicsPixmapItem* heart1;
    QGraphicsPixmapItem* heart2;
    QGraphicsPixmapItem* heart3;
    QGraphicsTextItem* scoreStr;
    QMediaPlayer* music;


    QString state;
    //possiblbe states:
    //mainMenu - when you first start the game
    //pause - tmeporarily pause the game
    //playing - when the player is playing the game
    //gameOver - when the game ends
    std::vector<int> pointSequence;
    int lives = 3;
    int score = 0;
    int speed = 10; //lower is faster

public slots:
    void lifeLost(int points);
    void createVirus();
    void updateScore(int score);
    void endGame();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void keyPressEvent(QKeyEvent*event);


};

#endif // KILLCOVID_H
