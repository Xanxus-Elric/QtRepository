#include "findwidget.h"

FindWidget::FindWidget(QWidget *parent) : QWidget(parent)
{
    QLabel  *SearchName = new QLabel("Search Name: ", this);

    this->InputName = new QLineEdit(this);
    this->SearchButton = new QPushButton("Search", this);

    QHBoxLayout *MainLayout = new QHBoxLayout(this);
    MainLayout->addWidget(SearchName);
    MainLayout->addWidget(this->InputName);
    MainLayout->addWidget(this->SearchButton);
}

