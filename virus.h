#ifndef VIRUS_H
#define VIRUS_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QGraphicsScene>

class virus : public QObject,  public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit virus(QObject *parent = nullptr);
    QTimer *timer;
signals:

public slots:
    void update();
};

#endif // VIRUS_H
