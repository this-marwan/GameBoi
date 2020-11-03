#ifndef KILLCOVID_H
#define KILLCOVID_H

#include <QObject>
#include <QWidget>
#include <QGraphicsScene>
#include <QTimer>

#include "user.h"

class killCovid : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit killCovid(user *activeUser, QObject *parent = nullptr);
    QTimer *timer;

public slots:
    void createVirus();


};

#endif // KILLCOVID_H
