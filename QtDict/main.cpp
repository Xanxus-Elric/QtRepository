#include "dictwidget.h"
#include <QApplication>
#include <QTextCodec>
#include <QProgressDialog>
#include <QtSql>
#include <QFile>
#include <QThread>

int main(int argc, char *argv[])
{
    //Language Support for Chinese UTF-8
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);

    QApplication a(argc, argv);

    QFile DbFile("./DictDatabase");
    if (!DbFile.exists()){
        //Need Convert Txt File to Db File
        QFile TxtFile(":/Text/dict.txt");

        if (!TxtFile.open(QIODevice::ReadOnly | QIODevice::Text)){
            qDebug() << "Open Text File Fail";
            return -1;
        }
        else{
            qDebug() << "Open Text File Success";
            int FileLines = 0;
            QProgressDialog ReadFileBar;
            ReadFileBar.setRange(0, 0);
            QThread ReadBarThread;

            ReadFileBar.moveToThread(&ReadBarThread);
            ReadFileBar.exec();
            ReadBarThread.start();

            while(!TxtFile.atEnd()){
                TxtFile.readLine();
                FileLines++;
                qDebug() << FileLines;
                ReadFileBar.update();
            }
        }
    }
    else{
        //Open the Db File
    }

//    //if the Database isn't exist, Convert Txt File to Db File
//    QSqlDatabase DictDb = QSqlDatabase::addDatabase("QSQLITE");
//    DictDb.setDatabaseName("./DictDatabase");
//    if (DictDb.open()){
//        qDebug() << "Open Db Success";

//        QFile DictFile(":/Text/dict.txt");
//        if (!DictFile.open(QIODevice::ReadOnly | QIODevice::Text)){
//            qDebug() << "Open Txt File Fail";
//            return -1;
//        }else{
//            qDebug() << "Open Txt File Success";
//            int TotalLines = 0;

//            while(!DictFile.atEnd()){
//                qDebug() << "1";
//                DictFile.readLine();
//                TotalLines++;
//            }
//            qDebug() << TotalLines << "Lines on File";

//            QProgressDialog ConvertDialog;
//            ConvertDialog.setRange(0, 0);
//            ConvertDialog.setLabelText("Set up the Dict Database");
//            ConvertDialog.exec();

//            int CurrentLines = 0;
//            //while(!DictFile.atEnd()){
//                ConvertDialog.setValue(50);
//                CurrentLines++;
//            //}
//        }
//    }
//    else{
//        qDebug() << "Open Db Fail";
//        return -1;
//    }


    //DictWidget w;
    //w.show();

    return a.exec();
}
