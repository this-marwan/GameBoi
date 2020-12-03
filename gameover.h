
#include <QObject>
#include <QWidget>
#include <QtWidgets>
#include "user.h"

/**
 *\file gameover.h
 *\brief What happens when the game of a user ends
 *
 * Header for when the Game is Over
 */

class gameOver : public QWidget
{
    Q_OBJECT
public:
    explicit gameOver(user *activeUser = nullptr,QWidget *parent = nullptr);
    user* activeUser;
    QPushButton* tryAgain;
    QPushButton* mainMenu;

    QLabel* gameOv;
    QLabel* scoreLabel;
    QLabel* highscoreLabel;

    QGridLayout* topGrid;
    QGridLayout* bottomGrid;

    QVBoxLayout* mainV;

public slots:

    bool tryAgainBool();
    bool mainMenuBool();


signals:
};

