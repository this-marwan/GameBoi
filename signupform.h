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
    QLabel* firstName;
    QLabel* lastName;
    QLabel* username;
    QLabel* dateOfBirth;
    QLabel* gender;

    QLabel* email;
    QLabel* password;

    QLineEdit* firstNameField;
    QLineEdit* lastNameField;
    QLineEdit* usernameField;
    QLineEdit* emailField;
    QLineEdit* passwordField;

    QDateEdit* dateField;
    QRadioButton* genderFieldMale;
    QRadioButton* genderFieldFemale;

    QTextEdit* textField;

    QPushButton* finishButton;
    QPushButton* refreshButton;

    QVBoxLayout* mainV;
    QVBoxLayout* radioV;
    QGridLayout* topGrid;

public slots:
    void signUp();

signals:
};

#endif // SIGNUPFORM_H
