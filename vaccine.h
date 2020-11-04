#ifndef VACCINE_H
#define VACCINE_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QGraphicsScene>

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
