#ifndef WELCOMEPAGE_H
#define WELCOMEPAGE_H

#include <QObject>
#include <QWidget>
#include <QtWidgets>
#include <QPixmap>

#include "user.h"

class welcomePage : public QWidget
{
    Q_OBJECT
public:
    explicit welcomePage(user *activeUser = nullptr, QWidget *parent = nullptr);
    user* activeUser;
    QPushButton* submitButton;
    QPixmap* profilePicturePath;
    QLabel* profilePicture;
    QLabel* userName;
    QLabel* generic;

    QGridLayout* topGrid;
    QVBoxLayout* mainV;

signals:
};

#endif // WELCOMEPAGE_H
