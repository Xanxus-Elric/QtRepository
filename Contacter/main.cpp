#include "mainwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    //this is the main body of the program
    QApplication a(argc, argv);

    //Create the First window of this program
    MainWidget w;
    w.show();

    return a.exec();
}
