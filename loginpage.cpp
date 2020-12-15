#include "loginpage.h"
#include <signupform.h>
#include <welcomepage.h>

/**
 *\file loginpage.cpp
 *\brief Page where the user can enter his username and password in order to get authenticated and to log in to his account
 *
 * Implements the Log in form
 */
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
    QObject::connect(guestButton, SIGNAL(clicked(bool)), this, SLOT(playAsGuest()));

}
//check this for JSON interactions : https://stackoverflow.com/questions/15893040/how-to-create-read-write-json-files-in-qt5

void loginPage::signIn()
{
    //check if a field is missing
    if (userNameField->text().isEmpty() || passwordField->text().isEmpty()){
    error->setText("Error: Fill missing fields");
    error->setVisible(true);
    return;
    }
    //check user exists
    if (checkUsername(userNameField->text())){
    error->setText("Error: Username doesn't exist.");
    error->setVisible(true);
    return;
    }
    //check if password is correct
    //hash our password

    QString password = passwordField->text();
    QByteArray hash =  QCryptographicHash::hash(password.toUtf8(),QCryptographicHash::Sha1);
    password = hash;

    if (checkPassword(userNameField->text(), password)){
        QString username = userNameField->text();
        QString val;
        QFile file;
        file.setFileName("../gameOne/users.json");
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        val = file.readAll();
        file.close();

        QJsonDocument doc;
        doc = QJsonDocument::fromJson(val.toUtf8());

        QJsonObject jObj = doc.object();
        jObj = jObj["users"].toObject();

        //get the user object
        jObj = jObj[username].toObject();
        user* activeUser;
        activeUser = new user(
                    jObj["first_name"].toString(),
                    jObj["last_name"].toString(),
                    username,
                    password,
                    jObj["birthdate"].toString(),
                    jObj["gender"].toString(),
                    jObj["email"].toString(),
                    jObj["profile_picture"].toString(),
                    jObj["current_score"].toInt(),
                    jObj["high_score"].toInt());


       welcomePage *window1 = new welcomePage(activeUser);
       window1->show();
       this->close();
    }
    else
    {
        error->setText("Error: incorrect password.");
        error->setVisible(true);
        return;
    }
};

void loginPage::signUp()
{
    signUpForm *window1 = new signUpForm;
    window1->show();
    this->close();

};

void loginPage::playAsGuest()
{
    user* activeUser;
    activeUser = new user(
                "guest",
                "",
                "guest",
                "",
                "",
                "",
                "",
                ":/static_images/default_pp.png",
                0,
                0);

    welcomePage *window1 = new welcomePage(activeUser);
    window1->show();
    this->close();
    this->deleteLater();

};

bool loginPage::checkUsername(QString username){
    //return fasle if Username exits else returns true
    QString val;
    QFile file;
    file.setFileName("../gameOne/users.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();

    QJsonDocument doc;
    doc = QJsonDocument::fromJson(val.toUtf8());

    QJsonObject jObj = doc.object();
    jObj = jObj["users"].toObject();
    if (jObj.keys().contains(username)){
        return false;
    }
    return true;
}

bool loginPage::checkPassword(QString username, QString password){
    //function that checks if given password macths our records
    //returns true if the passwords match
    QString val;
    QFile file;
    file.setFileName("../gameOne/users.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();

    QJsonDocument doc;
    doc = QJsonDocument::fromJson(val.toUtf8());

    QJsonObject jObj = doc.object();
    jObj = jObj["users"].toObject();

    if (jObj.keys().contains(username)){
        //get the user object
        jObj = jObj[username].toObject();

        if (password == jObj["password"].toString())
        {
            return true;
        }
    }
    return false;
}

