#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.setGeometry(0,0,200,250);
    w.resize(200,250);
    w.show();
    return a.exec();
}
