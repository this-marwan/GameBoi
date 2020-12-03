#ifndef SCROLLINGBG_H
#define SCROLLINGBG_H

#include <QObject>
#include <QWidget>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QGraphicsScene>

/**
 *\file scrollingbg.h
 *\brief The background of the Kill Covid game that will be scrolling down
 *
 * Header for The Scrolling background for the Kill Covid Game
 */

class scrollingBg : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit scrollingBg(QObject *parent = nullptr, int start_y = -698,int speed = 40);
    QTimer *timer;
signals:

public slots:
    void scroll();
    void updateSpeed(int x);
};

#endif // SCROLLINGBG_H
