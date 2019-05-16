#include "maindictwidget.h"
#include <QProgressBar>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QDebug>
#include <QThread>
#include <QFile>
#include <QMessageBox>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QStringList>

void PrepareOpt::PrepareRead()
{
    QFile DictFile(":/Text/dict.txt");

    if (DictFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        this->TotalLines = 0;
        while(!DictFile.atEnd()){
            DictFile.readLine();
            this->TotalLines++;
        }
        emit SendTotalLines(this->TotalLines);
    }
}

void ConvertOpt::ConvertDb(){
    QSqlDatabase DictDb = QSqlDatabase::addDatabase("QSQLITE");

    DictDb.setDatabaseName("./DictDatabase");

    if (DictDb.open()){
        QSqlQuery query;
        query.exec("create table Dict(word varchar(20), definition varchar(500))");

        QFile DictFile(":/Text/dict.txt");
        if (DictFile.open(QIODevice::ReadOnly | QIODevice::Text)){
            QString     TempString;
            QStringList TempList;
            QString     queryStr;
            int CurrentLines = 0;

            while(!DictFile.atEnd()){
                TempString = DictFile.readLine();
                TempList = TempString.split(":");
                queryStr = "insert into Dict values('" + TempList.at(0) + "','" + TempList.at(1) + "')";
                query.exec(queryStr);
                CurrentLines ++;
                emit ReportLines(CurrentLines);
            }
        }
        else{
            qDebug() << "Open Dict File fail";
        }
    }
    else{
        qDebug() << "Open Database fail";
    }

    DictDb.close();
    emit CloseThread();
}

MainDictWidget::MainDictWidget(QWidget *parent)
    : QWidget(parent)
{
    this->resize(500, 100);
    this->ConvertBar = new QProgressBar(this);
    this->ConvertBar->setRange(0, 0);
    this->ConvertBar->setTextVisible(false);
    //this->ConvertBar->setTextVisible(false);
    this->CancelBtn = new QPushButton("Cancel", this);
    this->PromptLabel = new QLabel("First Use, Prepare the Dictionary, Please wait a moment");

    QGridLayout *MainLayout = new QGridLayout(this);
    MainLayout->addWidget(this->PromptLabel, 0, 0);
    MainLayout->addWidget(this->ConvertBar, 1, 0);
    MainLayout->addWidget(this->CancelBtn, 2, 0, 1, 1, Qt::AlignRight);

    //Create the Prepare Operation, and run it on the other thread
    this->prepare = new PrepareOpt();
    this->prepareThread = new QThread(this);
    this->prepare->moveToThread(this->prepareThread);

    //create the Convert Operation, and run it on the other thread
    this->convert = new ConvertOpt();
    this->convertThread = new QThread(this);
    this->convert->moveToThread(this->convertThread);

    connect(this->prepareThread, SIGNAL(started()), this->prepare, SLOT(PrepareRead()));
    connect(this->prepare, SIGNAL(SendTotalLines(int)), this, SLOT(StartConvertThread(int)));
    connect(this->convertThread, SIGNAL(started()), this->convert, SLOT(ConvertDb()));
    connect(this->convert, SIGNAL(CloseThread()), this, SLOT(ShowSearchMainAfterConvert()));

    //according the status of the ConvertOpt, repaint the progress Bar
    //when the value come to 100%, close the ConvertWidget, and show the Search Widget
    connect(this->convert, SIGNAL(ReportLines(int)), this->ConvertBar, SLOT(setValue(int)));

    this->prepareThread->start();
}

void MainDictWidget::StartConvertThread(int TotalLines)
{
    qDebug() << "Total Lines " << TotalLines;
    this->prepareThread->quit();
    this->ConvertBar->setRange(0, TotalLines);
    this->ConvertBar->setTextVisible(true);
    this->convertThread->start();
}

void MainDictWidget::ShowSearchMainAfterConvert()
{
    this->convertThread->quit();

    QMessageBox::information(this, "Setup Database success", "Establish the Dictionary Database Complete, Click \"OK\" to Use");

    this->SearchMain = new SearchWidget();
    this->SearchMain->show();
    this->hide();
}

MainDictWidget::~MainDictWidget()
{
    if (this->prepareThread->isRunning()){
        this->prepareThread->quit();
    }

    if (this->convertThread->isRunning()){
        this->convertThread->quit();
    }
}
