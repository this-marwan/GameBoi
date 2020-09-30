#include <QApplication>
#include <signupform.h>
//#include <mainmenu.h>

int main(int argc, char **argv)
{
    QApplication app (argc, argv);
//    mainMenu widow;
    signUpForm window;
    window.show();
    return app.exec();
}
