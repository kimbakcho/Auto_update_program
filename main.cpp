#include "mainwidet.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Mainwidet w;
    w.show();
    if(!w.getStart_popup_flag()){
        w.close();
    }
    return a.exec();
}
