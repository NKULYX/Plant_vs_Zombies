#include "plants_zombies.h"
#include "login.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login login_w;
    login_w.show();
    return a.exec();
}

