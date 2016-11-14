#include "mainwidet.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Mainwidet w;
    w.show();

    return a.exec();
}
