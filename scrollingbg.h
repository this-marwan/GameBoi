#ifndef SCROLLINGBG_H
#define SCROLLINGBG_H

#include <QObject>
#include <QWidget>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QGraphicsScene>

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
