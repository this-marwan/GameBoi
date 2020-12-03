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

    int highScore = 0;
    int currentScore = 0;

    int highScoreReversi = 0;
    int currentScoreReversi = 0;
    user();

    user(QString firstName,
    QString lastName,
    QString username,
    QString password,
    QString birthdate,
    QString gender,
    QString email,
    QString profilePicture,
    int currentScore = 0,
    int highScore = 0,
    int highScoreReversi = 0,
    int currentScoreReversi = 0)
    {
       this->firstName = firstName;
       this->lastName = lastName;
       this->username = username;
       this->password = password;
       this->birthdate = birthdate;
       this->gender = gender;
       this->email = email;
       this->profilePicture = profilePicture;
       this->currentScore = currentScore;
       this->highScore = highScore;
       this->currentScoreReversi = currentScoreReversi;
       this->highScore = highScoreReversi;
    };

};

#endif // USER_H
