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

/**
 *\file reversi.h
 *\brief The Game Scene class of the Second game "Reversi"
 *
 * Header for The Game Scene class of Reversi
 */


class Reversi : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Reversi(user *activeUser, QWidget *parent = nullptr);
    QTimer *timer;
    QWidget *parent;

    //player score board
    QGridLayout* playerBoard;

    QGraphicsPixmapItem* playerOneBox;
    QGraphicsPixmapItem* playerTwoBox;

    QGraphicsTextItem* playerOneLabel;
    QGraphicsTextItem* playerTwoLabel;

    QGraphicsTextItem* playerOneScoreLabel;
    QGraphicsTextItem* playerTwoScoreLabel;

    QGraphicsTextItem* playerOneDiscsLabel;
    QGraphicsTextItem* playerTwoDiscsLabel;

    QGraphicsTextItem* playerOneTimerLabel;
    QGraphicsTextItem* playerTwoTimerLabel;

    //player properties
    int playerOneScore = 0;
    int playerTwoScore = 0;

    int playerOneDiscsLeft = 3; //two are already placed for them on the board
    int playerTwoDiscsLeft = 3;


    QGraphicsPixmapItem* playButton;
    QGraphicsPixmapItem* playAgainButton;
    QGraphicsPixmapItem* returnToMenuButton;


    QTimer *timerOne; //timer for playrOne
    QTimer *timerTwo; //timer for playerTwo

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

    void endGame();
    void togglePlayers();
    void placeNewToken(int position);
    void redrawGrid(bool hint = false);
    void showHints();
    void updateScore();
    bool checkMoveIsValid(int position);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
//    void keyPressEvent(QKeyEvent*event);


};

#endif // KILLCOVID_H
