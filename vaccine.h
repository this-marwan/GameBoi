#ifndef VACCINE_H
#define VACCINE_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QGraphicsScene>

/**
 *\file vaccine.h
 *\brief The vaccine class for the first game "Kill Covid"
 *
 * Takes care of the vaccine's behaviour
 */
class vaccine : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit vaccine(QObject *parent = nullptr);
    QTimer *timer;

signals:

public slots:
    void update();

};

#endif // VACCINE_H
