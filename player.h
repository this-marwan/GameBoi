#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>

/**
 *\file player.h
 *\brief The player class for the first game "Kill Covid"
 *
 * The object of focus which is the player
 */

class Player : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY (qreal y READ y WRITE setY)
public:
    explicit Player(QObject *parent = nullptr);
    void keyPressEvent(QKeyEvent*event);
    void shoot();

signals:

};

#endif // PLAYER_H
