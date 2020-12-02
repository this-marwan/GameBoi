#ifndef REVERSI_H
#define REVERSI_H

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
#include "reversiPlayer.h"


class Reversi : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Reversi(user *activeUser, QWidget *parent = nullptr);
    QTimer *timer;
    QWidget *parent;

    //player score board
    QGridLayout* playerBoard;
    QVBoxLayout* playerOneBox;
    QVBoxLayout* playerTwoBox;

    QLabel* playerOneLabel;
    QLabel* playerTwoLabel;

    QGraphicsPixmapItem* playButton;

    QTimer *timerOne; //timer for playrOne
    QTimer *timerTwo; //timer for playerTwo

    reversiPlayer* playerOne; //black player
    reversiPlayer* playerTwo; //white player

    int activePlayer = 0; //The player with the active turn now (either one or two)

    user *activeUser; //for score keeping if need be

    std::vector<QGraphicsPixmapItem*> gridTiles;
    int gridState[8][8] = {};

    QMediaPlayer* music;
    QSound* song;

    QString state;
    //possiblbe states:
    //mainMenu - when you first start the game
    //pause - tmeporarily pause the game
    //playing - when the player is playing the game
    //gameOver - when the game ends

public slots:
//    void lifeLost(int points);
//    void createVirus();
//    void updateScore(int score);
//    void endGame();
    void togglePlayers();
    void placeNewToken(int position);
    void redrawGrid();
    bool checkMoveIsValid(int position);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
//    void keyPressEvent(QKeyEvent*event);


};

#endif // KILLCOVID_H
