#include "loginpage.h"
#include <signupform.h>
#include <welcomepage.h>
#include "user.h"
#include <QPixmap>

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

    mainV = new QVBoxLayout;
    topGrid = new QGridLayout;

    topGrid->addWidget(profilePicture,0,0);
    topGrid->addWidget(userName,0,1);

    mainV->addItem(topGrid);
    mainV->addWidget(lineB);

    //add games display here


    setLayout(mainV);
}
