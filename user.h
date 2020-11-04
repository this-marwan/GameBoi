#ifndef USER_H
#define USER_H

#include <QObject>
#include <QWidget>

class user : public QObject
{
    Q_OBJECT
    public:
    QString firstName;
    QString lastName;

    QString username;
    QString password;

    QString birthdate;
    QString gender;
    QString email;
    QString profilePicture;

    user();

    user(QString firstName,
    QString lastName,
    QString username,
    QString password,
    QString birthdate,
    QString gender,
    QString email,
    QString profilePicture)
    {
       this->firstName = firstName;
       this->lastName = lastName;
       this->username = username;
       this->password = password;
       this->birthdate = birthdate;
       this->gender = gender;
       this->email = email;
       this->profilePicture = profilePicture;
    };

    int highScore = 0;
    int currentScore = 0;
};

#endif // USER_H
