#include <QApplication>
#include <signupform.h>

int main(int argc, char **argv)
{
    QApplication app (argc, argv);
    signUpForm window;
    window.show();
    return app.exec();
}
