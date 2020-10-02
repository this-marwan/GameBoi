#ifndef WELCOMEPAGE_H
#define WELCOMEPAGE_H

#include <QObject>
#include <QWidget>
#include <QtWidgets>

#include "user.h"

class welcomePage : public QWidget
{
    Q_OBJECT
public:
    explicit welcomePage(QWidget *parent = nullptr);
    QPushButton* submitButton;
    QLabel* userName;
    QLabel* generic;
    QVBoxLayout* mainV;

signals:
};

#endif // WELCOMEPAGE_H
