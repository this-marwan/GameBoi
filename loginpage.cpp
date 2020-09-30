#include "loginpage.h"
#include <signupform.h>

loginPage::loginPage(QWidget *parent) : QWidget(parent)
{

    signUpPage = new signUpForm();

    logInButton = new QPushButton("Log In");
    signUpButton = new QPushButton("Sign Up");
    guestButton = new QPushButton("Play as guest");

    userName = new QLabel("Username");
    userNameField = new QLineEdit();

    password = new QLabel("Password");
    passwordField = new QLineEdit();
    passwordField->setEchoMode(QLineEdit::Password);

    error = new QLabel("Error:");
    error->setStyleSheet("QLabel {color : red;}");
    error->setVisible(false);

    topGrid = new QGridLayout;
    mainV = new QVBoxLayout;

    //start of top grid

    topGrid->addWidget(userName,0,0);
    topGrid->addWidget(userNameField,0,1);

    topGrid->addWidget(password,1,0);
    topGrid->addWidget(passwordField,1,1);

    mainV->addItem(topGrid);
    mainV->addWidget(error,1,0);
    mainV->addWidget(logInButton,2,0);
    mainV->addWidget(signUpButton,3,0);
    mainV->addWidget(guestButton,4,0);

    setLayout(mainV);

    QObject::connect(logInButton, SIGNAL(clicked(bool)), this, SLOT(signIn()));
    QObject::connect(signUpButton, SIGNAL(clicked(bool)), this, SLOT(signUp()));

}
//check this for JSON interactions : https://stackoverflow.com/questions/15893040/how-to-create-read-write-json-files-in-qt5

void loginPage::signIn()
{
    //check user exists
    error->setText("Error: Username doesn't exist.");
    error->setVisible(true);

    //check if password is correct
    error->setText("Error: incorrect password.");
    error->setVisible(true);
};

void loginPage::signUp()
{
    //take to you to the sign up page
//    signUpPage->show();
//    this->hide();
};


