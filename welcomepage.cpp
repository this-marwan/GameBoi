#include "loginpage.h"
#include <signupform.h>
#include <welcomepage.h>
#include "user.h"
#include <QPixmap>
#include "killcovid.h"

welcomePage::welcomePage(user *activeUser, QWidget *parent) : QWidget(parent)
{
    this->activeUser = activeUser;
    userName = new QLabel();
    profilePicture = new QLabel();
    if (this->activeUser->birthdate == QDate::currentDate().toString()){
    userName->setText("Happy birthday!");
    }
    else{
    userName->setText("Welcome, " + this->activeUser->username);
    }

    profilePicture->setPixmap((QPixmap(this->activeUser->profilePicture)).scaled(40,40));
    profilePicture->setFixedHeight(40);
    profilePicture->setFixedWidth(40);

    QWidget *lineB = new QWidget;
    lineB->setFixedHeight(2);
    lineB->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    lineB->setStyleSheet(QString("background-color: #c0c0c0;"));

    gameOne = new QPushButton();
    gameOne->setFixedHeight(200);
    gameOne->setFixedWidth(100);
    gameOne->setStyleSheet("border-image:url(:/static_images/COVID.png);");

    gameTwo = new QPushButton();
    gameTwo->setFixedHeight(200);
    gameTwo->setFixedWidth(100);
    gameTwo->setStyleSheet("border-image:url(:/static_images/Reversi.png);");

    mainV = new QVBoxLayout;
    topGrid = new QGridLayout;
    bottomGrid = new QGridLayout;

    topGrid->addWidget(profilePicture,0,0);
    topGrid->addWidget(userName,0,1);

    bottomGrid->setSpacing(10);
    bottomGrid->setRowStretch(0, 4);
    bottomGrid->setRowStretch(1, 4);
//    bottomGrid->setRowStretch(0, 4);

    bottomGrid->addWidget(gameOne,0,0);
    bottomGrid->addWidget(gameTwo,0,1);

    generic = new QLabel("Top Score: 0\nYour High Score: 0");
    generic1 = new QLabel("Top Score: 0\nYour High Score: 0");

    bottomGrid->addWidget(generic,1,0);
    bottomGrid->addWidget(generic1,1,1);


    mainV->addItem(topGrid);
    mainV->addWidget(lineB);

    //add games display here
    mainV->addItem(bottomGrid);


    setLayout(mainV);
    QObject::connect(gameOne, SIGNAL(clicked(bool)), this, SLOT(startKillCovid()));

}

bool welcomePage::startKillCovid()
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
