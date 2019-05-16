#include "searchwidget.h"
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QGridLayout>
#include <QString>

SearchWidget::SearchWidget(QWidget *parent) : QWidget(parent)
{
    this->setMinimumSize(400, 300);

    this->SearchInput = new QLineEdit(this);
    this->SearchInput->setPlaceholderText("Input Search Word");

    this->SearchBtn = new QPushButton("Search", this);

    this->ResultText = new QTextEdit(this);

    QGridLayout *MainLayout = new QGridLayout(this);
    MainLayout->addWidget(this->SearchInput, 0, 0, 1, 3);
    MainLayout->addWidget(this->SearchBtn, 0, 3, 1, 1);
    MainLayout->addWidget(this->ResultText, 1, 0, 1, 4);

    this->DictDb = QSqlDatabase::addDatabase("QSQLITE");
    this->DictDb.setDatabaseName("./DictDatabase");

    if (!DictDb.open()){
        qDebug() << "open Database fail";
    }

    connect(this->SearchBtn, SIGNAL(clicked(bool)), this, SLOT(Search()));
}

void SearchWidget::Search()
{
    //search the word on the Database which provided by MainDictWidget
    QString TempStr = this->SearchInput->text();
    TempStr = TempStr.toLower();
    QString QueryStr = "select * from Dict where word = '" + TempStr + "'";
    QSqlQuery query;
    query.exec(QueryStr);

    if (query.next()){
        this->ResultText->setText(query.value("definition").toString());
    }
    else{
        this->ResultText->setText("No Result Found");
    }
}
