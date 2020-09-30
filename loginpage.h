#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QObject>
#include <QWidget>
#include <QtWidgets>
#include "signupform.h"

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


private:
//    bool validateEmail(QString email);
signals:
};

#endif // LOGINPAGE_H
