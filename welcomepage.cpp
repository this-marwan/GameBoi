#include "loginpage.h"
#include <signupform.h>
#include <welcomepage.h>

welcomePage::welcomePage(QWidget *parent) : QWidget(parent)
{

    userName = new QLabel("Welcome");
    generic = new QLabel("Welcome");
    //end of top grid
    mainV = new QVBoxLayout;

    mainV->addWidget(userName);
    this->resize(600, 400);


    setLayout(mainV);
}
