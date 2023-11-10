#include "DefenseGame.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DefenseGame w;
    w.show();
    return a.exec();
}
