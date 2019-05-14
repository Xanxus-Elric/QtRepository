#include "dictwidget.h"
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QString>
#include <QStringList>
#include <QSqlQuery>
#include <QProgressDialog>

bool DictWidget::ConvertFileToDb(){
    //Firstly, judge whether the Database file exists or not
    this->DictDb = QSqlDatabase::addDatabase("QSQLITE");

    QFile DbFile("./DictDatabase");
    if (DbFile.exists()){
        qDebug() << "Db File Exists";

        this->DictDb.setDatabaseName("./DictDatabase");

        if (this->DictDb.open()){
            qDebug() << "Open Db Success";
            return true;
        }
        else{
            qDebug() << "Open Db Fail";
            return false;
        }
    }
    else{
        qDebug() << "File doesn't Exists";
        //Need to convert the Txt File to Db File
        this->DictDb.setDatabaseName("./DictDatabase");

        if (this->DictDb.open()){
            qDebug() << "Open Db Success";

            QSqlQuery query;
            query.exec("create table Dict(word varchar(20), definition varchar(500))");

            QFile Dict(":/Text/dict.txt");

            if (!Dict.open(QIODevice::ReadOnly | QIODevice::Text)){
                qDebug() << "Open File Fail";
                return false;
            }

            while(!Dict.atEnd()){
                QString TempLine = Dict.readLine();
                QStringList TempList = TempLine.split(":");
                QString QueryStr = "insert into Dict values('" + TempList.at(0) + "','" + TempList.at(1) + "')";
                query.exec(QueryStr);
            }

            return true;
        }
        else{
            qDebug() << "Open Db Fail";
            return false;
        }
    }
}

DictWidget::DictWidget(QWidget *parent)
    : QWidget(parent)
{
    this->SearchWord = new QLineEdit(this);
    this->SearchWord->setPlaceholderText("Search Word");

    this->SearchBtn = new QPushButton("Search", this);

    this->SearchResult = new QTextEdit(this);
    this->SearchResult->setReadOnly(true);

    QHBoxLayout *FirstLayout = new QHBoxLayout();
    FirstLayout->addWidget(this->SearchWord);
    FirstLayout->addWidget(this->SearchBtn);

    QGridLayout *MainLayout = new QGridLayout(this);
    MainLayout->addLayout(FirstLayout, 0, 0);
    MainLayout->addWidget(this->SearchResult);

    if (!ConvertFileToDb()){
        return ;
    }

    connect(this->SearchBtn, SIGNAL(clicked(bool)), this, SLOT(Search()));
}

void DictWidget::Search(){

}

DictWidget::~DictWidget()
{

}
