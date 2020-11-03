#ifndef KILLCOVID_H
#define KILLCOVID_H

#include <QObject>
#include <QWidget>
#include <QGraphicsScene>
#include <QTimer>

#include "user.h"
#include <QtWidgets>
#include <QPixmap>

#include "user.h"
#include "player.h"

class killCovid : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit killCovid(user *activeUser, QObject *parent = nullptr);
    QTimer *timer;


    QGraphicsPixmapItem* playButton;
    QGraphicsPixmapItem* settingsButton;
    Player* player;
    QPropertyAnimation* m_anim;
    QGraphicsPixmapItem* heart1;
    QGraphicsPixmapItem* heart2;
    QGraphicsPixmapItem* heart3;

    QString state;
    //possiblbe states:
    //mainMenu - when you first start the game
    //pause - tmeporarily pause the game
    //playing - when the player is playing the game
    //gameOver - when the game ends
    int lives;

public slots:
    void lifeLost();
    void createVirus();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void keyPressEvent(QKeyEvent*event);


};

#endif // KILLCOVID_H
