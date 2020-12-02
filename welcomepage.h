#ifndef WELCOMEPAGE_H
#define WELCOMEPAGE_H

#include <QObject>
#include <QWidget>
#include <QtWidgets>
#include <QPixmap>

#include "user.h"

class welcomePage : public QWidget
{
    Q_OBJECT
public:
    explicit welcomePage(user *activeUser = nullptr, QWidget *parent = nullptr);
    user* activeUser;
    QPushButton* gameOne;
    QPushButton* gameTwo;

    QPixmap* profilePicturePath;
    QLabel* profilePicture;
    QLabel* userName;
    QLabel* generic;
    QLabel* generic1;

    QGridLayout* topGrid;
    QGridLayout* bottomGrid;

    QVBoxLayout* mainV;

public slots:
//    bool settings();
    bool startKillCovid();
    bool startReversi();
//    bool checkPassword(QString username, QString password);

signals:
};

#endif // WELCOMEPAGE_H
