#ifndef VIRUS_H
#define VIRUS_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QGraphicsScene>

/**
 *\file virus.h
 *\brief The virus class for the first game "Kill Covid"
 *
 * Generates viruses and takes care of their behaviours
 */

class virus : public QObject,  public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit virus(int points = 3,int speed = 10, QObject *parent = nullptr);
    QTimer *timer;
    int points;
    int speed;
signals:
void virusMissed(int points = 3);
void virusHit(int points = 3);
public slots:
    void update();
    void die();
};

#endif // VIRUS_H
