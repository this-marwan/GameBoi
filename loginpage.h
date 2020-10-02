#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QObject>
#include <QWidget>
#include <QtWidgets>
#include "signupform.h"
#include "welcomepage.h"

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
