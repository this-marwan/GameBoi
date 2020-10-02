#include <QApplication>
#include <signupform.h>
#include <loginpage.h>

int main(int argc, char **argv)
{
    QApplication app (argc, argv);

    loginPage window;
    window.show();
    return app.exec();
}
