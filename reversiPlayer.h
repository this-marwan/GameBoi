#ifndef REVERSIPLAYER_H
#define REVERSIPLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>

class reversiPlayer : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY (qreal y READ y WRITE setY)
public:
    explicit reversiPlayer(QObject *parent = nullptr, bool color = false);
    bool myTurn = false;
    int tokensWon = 0; //how many tokens on the baord belong to the player
    int tokenLeft = 32; //how many tokens does the player have left
    bool color; //false is white
                //true is black
//    void keyPressEvent(QKeyEvent*event);
//    void shoot();


signals:

};

#endif // PLAYER_H
