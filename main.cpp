#include <QApplication>
#include <signupform.h>
#include <loginpage.h>
#include <welcomepage.h>

int main(int argc, char **argv)
{
    QApplication app (argc, argv);

    //check if a user.json file exists, else create one
     QString val;
        QFile file;
     file.setFileName("../gameOne/users.json");
     if (!file.open(QIODevice::ReadWrite)) {
             QTextStream stream(&file);
             stream << "{ \"number_of_users\": 0, \n \"users\": {\n}\n}" << endl;
         }


    loginPage *window = new loginPage();
    window->show();
    return app.exec();
}
