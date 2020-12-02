#include "gameover.h"
#include <welcomepage.h>
#include "welcomepage.h"
#include "user.h"
#include <QPixmap>
#include "killcovid.h"
#include <string>
#include <iostream>

using namespace std;

gameOver::gameOver(user *activeUser, QWidget *parent) : QWidget(parent)
{

    this->activeUser = activeUser;
    gameOv = new QLabel();

    gameOv->setText("Game Over!");

    QWidget *lineB = new QWidget;
    lineB->setFixedHeight(2);
    lineB->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    lineB->setStyleSheet(QString("background-color: #c0c0c0;"));

    tryAgain = new QPushButton("Try again");
    tryAgain->setFixedHeight(50);
    tryAgain->setFixedWidth(100);

    mainMenu = new QPushButton("Main Menu");
    mainMenu->setFixedHeight(50);
    mainMenu->setFixedWidth(100);

    mainV = new QVBoxLayout;
    topGrid = new QGridLayout;
    bottomGrid = new QGridLayout;

    topGrid->addWidget(gameOv,0,1);

    bottomGrid->setSpacing(10);
    bottomGrid->setRowStretch(0, 4);
    bottomGrid->setRowStretch(1, 4);
//    bottomGrid->setRowStretch(0, 4);

    bottomGrid->addWidget(tryAgain,0,0);
    bottomGrid->addWidget(mainMenu,0,1);


    QString s1 = QString::number(this->activeUser->currentScore);
    QString s2 = QString::number(this->activeUser->highScore);

    QString ss1 = QString("You scored: %1").arg(s1);
    QString ss2 = QString("HighScore :%2").arg(s2);


    scoreLabel = new QLabel(ss1);
    highscoreLabel = new QLabel(ss2);

    bottomGrid->addWidget(scoreLabel,1,0);
    bottomGrid->addWidget(highscoreLabel,1,1);


    mainV->addItem(topGrid);
    mainV->addWidget(lineB);

    //add games display here
    mainV->addItem(bottomGrid);


    setLayout(mainV);
    QObject::connect(tryAgain, SIGNAL(clicked(bool)), this, SLOT(tryAgainBool()));
    QObject::connect(mainMenu, SIGNAL(clicked(bool)), this, SLOT(mainMenuBool()));

}

bool gameOver::tryAgainBool()
{
    QGraphicsView* view = new QGraphicsView();

    killCovid* scene1 = new killCovid(this->activeUser,this);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff );
    view->setScene(scene1);
    view->setFixedSize(400,640);
    view->show();
    this->hide();

    return true;

};

bool gameOver::mainMenuBool()
{

    welcomePage *window1 = new welcomePage(activeUser);
    window1->show();
    this->hide();

    return true;

};

