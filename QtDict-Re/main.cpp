#include "maindictwidget.h"
#include "searchwidget.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QFile DbFile("./DictDatabase");

    if (DbFile.exists()){
        QApplication a(argc, argv);
        SearchWidget s;
        s.show();
        return a.exec();
    }
    else{
        QApplication a(argc, argv);
        MainDictWidget w;
        w.show();
        return a.exec();
    }
}
