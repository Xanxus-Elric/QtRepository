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
#include <QIcon>

DictWidget::DictWidget(QWidget *parent)
    : QWidget(parent)
{
    QIcon DictIcon(":/Icon/DictIcon.png");

    this->setMinimumSize(400, 300);
    this->setWindowTitle("Dictionary");
    this->setWindowIcon(DictIcon);
    //First Part, Setup the UI Page
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

    //Second Part, Open the Database
    this->DictDb = QSqlDatabase::addDatabase("QSQLITE");
    this->DictDb.setDatabaseName("./DictDatabase");

    if (!this->DictDb.open()){
        qDebug() << "Open Dictionary Database Fail";
        return ;
    }

    //Third Part, Connect Signal-Slot
    connect(this->SearchBtn, SIGNAL(clicked(bool)), this, SLOT(Search()));
}

void DictWidget::Search(){
    //Get the text on line Edit
    QString TempStr = this->SearchWord->text();
    TempStr = TempStr.toLower();
    QString QueryStr = "select * from Dict where word = '" + TempStr + "'";
    QSqlQuery query;
    query.exec(QueryStr);

    if (query.next()){
        this->SearchResult->setText(query.value("definition").toString());
    }
    else{
        this->SearchResult->setText("No Result Found");
    }
}

DictWidget::~DictWidget()
{

}
