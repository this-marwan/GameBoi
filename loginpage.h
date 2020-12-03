#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QObject>
#include <QWidget>
#include <QtWidgets>
#include "signupform.h"
#include "welcomepage.h"

/**
 *\file loginpage.h
 *\brief Page where the user can enter his username and password in order to get authenticated and to log in to his account
 *
 * Header for Log in form
 */

class loginPage : public QWidget
{
    Q_OBJECT
public:
    explicit loginPage(QWidget *parent = nullptr);
    QLabel* userName;
    QLabel* password;
    QLabel* error;

    QLineEdit* userNameField;
    QLineEdit* passwordField;

    QPushButton* logInButton;
    QPushButton* signUpButton;
    QPushButton* guestButton;

    signUpForm* signUpPage;

    QGridLayout* topGrid;
    QVBoxLayout* mainV;


public slots:
    void signIn();
    void signUp();
    void playAsGuest();
    bool checkUsername(QString username);
    bool checkPassword(QString username, QString password);



private:
//    bool validateEmail(QString email);
signals:
};

#endif // LOGINPAGE_H
