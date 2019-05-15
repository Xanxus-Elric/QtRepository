#include <QApplication>
#include <QTextCodec>
#include <QtSql>
#include <QFile>
#include "convertwidget.h"

int main(int argc, char *argv[])
{
    //Language Support for Chinese UTF-8
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);

    QFile DbFile("./DictDatabase");
    bool NeedConvert = false;

    if (!DbFile.exists()){
        //the Db File isn't exist, need convert
        NeedConvert = true;
    }

    QApplication a(argc, argv);

    ConvertWidget convertWidget;
    convertWidget.show();

    return a.exec();
}
