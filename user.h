#ifndef USER_H
#define USER_H

#include <QObject>
#include <QWidget>

class user
{
    Q_OBJECT
public:
    user();

    String firstName;
    String lastNames;

    String username;
    String password;

    String birthdate;
    String gender;
    String email;
    String profilePicture;

    int highScore;
};

#endif // USER_H
