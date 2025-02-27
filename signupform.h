#ifndef SIGNUPFORM_H
#define SIGNUPFORM_H

#include <QObject>
#include <QWidget>
#include <QtWidgets>
/**
 *\file signupform.h
 *\brief Page where the user can enter his information in order to create an account
 *
 * Header for sign up form
 */
class signUpForm : public QWidget
{
    Q_OBJECT
public:
    explicit signUpForm(QWidget *parent = nullptr);
    QLabel* userName;
    QLabel* firstName;
    QLabel* lastName;
    QLabel* dateOfBirth;
    QLabel* gender;
    QLabel* email;
    QLabel* password;
    QLabel* confirmPassword;
    QLabel* profilePic;

    QLineEdit* userNameField;
    QLineEdit* firstNameField;
    QLineEdit* lastNameField;
    QLineEdit* emailField;
    QLineEdit* passwordField;
    QLineEdit* confirmPasswordField;
    QLineEdit* profilePicField;

    QCalendarWidget* dateField;
    QRadioButton* genderFieldMale;
    QRadioButton* genderFieldFemale;

    QLabel* error;

    QPushButton* browseButton;
    QPushButton* submitButton;
    QPushButton* backButton;

    QVBoxLayout* mainV;
    QVBoxLayout* radioV;
    QGridLayout* topGrid;

public slots:
    void goBack();
    void signUp();
    void browsePic();

private:
    bool validateEmail(QString email);
    bool checkUsername(QString username);
signals:
};

#endif // SIGNUPFORM_H
