#ifndef SIGNUPFORM_H
#define SIGNUPFORM_H

#include <QObject>
#include <QWidget>
#include <QtWidgets>

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

    QTextEdit* textField;

    QPushButton* submitButton;

    QVBoxLayout* mainV;
    QVBoxLayout* radioV;
    QGridLayout* topGrid;

public slots:
    void signUp();

private:
    bool validateEmail(QString email);
signals:
};

#endif // SIGNUPFORM_H
