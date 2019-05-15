#include "convertwidget.h"
#include <QLabel>
#include <QPushButton>
#include <QProgressBar>
#include <QGridLayout>
#include <QThread>
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QtSql>
#include <QSqlQuery>
#include <QStringList>
#include "dictwidget.h"

QT_BEGIN_NAMESPACE
class DictWidget;
QT_END_NAMESPACE

ReadOpt::ReadOpt(const QString FileName){
    this->DictFile = new QFile(FileName);
    if (this->DictFile->exists()){
        qDebug() << "File exists";
        this->FileExist = true;
        return ;
    }
    else{
        qDebug() << "File doesn't exist";
        this->FileExist = false;
        return ;
    }
}

void ReadOpt::GetFileLines(){
    if (this->FileExist){
        if (this->DictFile->open(QIODevice::ReadOnly | QIODevice::Text)){
            this->FileLines = 0;
            while(!this->DictFile->atEnd()){
                this->DictFile->readLine();
                this->FileLines++;
            }
            this->DictFile->close();
            emit ReadFinish(this->FileLines);
        }
        else{
            qDebug() << "Open File Fail";
            emit ReadFinish(-1);
            return ;
        }
    }
}

ConvertWidget::ConvertWidget(QWidget *parent) : QWidget(parent)
{
    QFile Judge("./DictDatabase");
    if(Judge.exists()){
        this->hide();
        this->Dict = new DictWidget(this);
        this->Dict->show();
    }
    else{
        qDebug() << "not exist";
        this->resize(400, 100);

        this->PromptLabel = new QLabel("First Use, Prepare the Dictionary", this);
        this->CancelButton = new QPushButton("Cancel", this);

        this->ConvertProgress = new QProgressBar(this);
        this->ConvertProgress->setRange(0, 0);
        this->ConvertProgress->setTextVisible(false);
        this->setWindowTitle("Setup Dictionary Database");

        QGridLayout *MainLayout = new QGridLayout(this);
        MainLayout->addWidget(this->PromptLabel, 0, 0, 1, 1);
        MainLayout->addWidget(this->ConvertProgress, 1, 0, 1, 1);
        MainLayout->addWidget(this->CancelButton, 3, 0, 1, 1, Qt::AlignRight);

        this->ReadFile = new ReadOpt(":/Text/dict.txt");
        if (!this->ReadFile->FileExist){
            this->close();
            return ;
        }

        this->ReadThread = new QThread(this);
        this->ReadFile->moveToThread(this->ReadThread);

        connect(this->ReadThread, SIGNAL(started()), this->ReadFile, SLOT(GetFileLines()));
        connect(this->ReadFile, SIGNAL(ReadFinish(int)), this, SLOT(GetReadResult(int)));
        connect(this->ReadFile, SIGNAL(ReadFinish(int)), this->ReadThread, SLOT(quit()));

        this->ReadThread->start();
    }
}

void ConvertWidget::GetReadResult(int FileLines){
    if (FileLines < 0){
        qDebug() << "Read Dictionary File Error";
        return ;
    }

    qDebug() << "Lines Of File is " << FileLines;

    this->ConvertProgress->setRange(0, FileLines);
    this->ConvertProgress->setTextVisible(true);

    this->Convert = new ConvertOpt();
    this->ConvertThread = new QThread(this);
    this->Convert->moveToThread(this->ConvertThread);

    this->Dict = new DictWidget(this);

    connect(this->ConvertThread, SIGNAL(started()), this->Convert, SLOT(ConvertDb()));
    connect(this->Convert, SIGNAL(SendCurrentLines(int)), this->ConvertProgress, SLOT(setValue(int)));
    connect(this->Convert, SIGNAL(ConvertFinish()), this->ConvertThread, SLOT(quit()));
    connect(this->Convert, SIGNAL(ConvertFinish()), this->Dict, SLOT(show()));
    connect(this->Convert, SIGNAL(ConvertFinish()), this, SLOT(hide()));


    this->ConvertThread->start();
}

void ConvertOpt::ConvertDb(){
    //open the Txt File
    QFile TxtFile(":/Text/dict.txt");
    if (!TxtFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "Open File Fail";
        return ;
    }

    //Setup a Database
    QSqlDatabase DictDb = QSqlDatabase::addDatabase("QSQLITE");
    DictDb.setDatabaseName("./DictDatabase");

    if (!DictDb.open()){
        qDebug() << "Open Database fail";
        return ;
    }

    QSqlQuery query;
    query.exec("create table Dict(word varchar(20), definition varchar(500))");

    int CurrentLine = 0;

    while(!TxtFile.atEnd()){
        QString TempLine = TxtFile.readLine();
        QStringList TempList = TempLine.split(":");
        QString queryStr = "insert into Dict values('" + TempList.at(0) + "','" + TempList.at(1) + "')";
        query.exec(queryStr);
        CurrentLine++;
        if (CurrentLine % 500){
            emit SendCurrentLines(CurrentLine);
        }
    }
    DictDb.close();

    emit ConvertFinish();

    TxtFile.close();
}

