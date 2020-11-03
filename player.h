#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>

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
