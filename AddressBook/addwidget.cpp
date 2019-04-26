#include "addwidget.h"

//Create the Add Widget
AddWidget::AddWidget(QWidget *parent) : QWidget(parent)
{
    QLabel *NamePrompt = new QLabel("Please Input Name: ");
    QLabel *AddressPrompt = new QLabel("Please Input Address: ");

    this->Name = new QLineEdit(this);
    this->Address = new QTextEdit(this);

    this->ConfirmButton = new QPushButton("Confirm");
    this->CancelButton = new QPushButton("Cancel");

    QHBoxLayout *ButtonLayout = new QHBoxLayout;
    ButtonLayout->addWidget(ConfirmButton);
    ButtonLayout->addWidget(CancelButton);

    QGridLayout *MainLayout = new QGridLayout(this);
    MainLayout->addWidget(NamePrompt, 0, 0);
    MainLayout->addWidget(this->Name, 1, 0);
    MainLayout->addWidget(AddressPrompt, 3, 0);
    MainLayout->addWidget(this->Address, 4, 0);
    MainLayout->addLayout(ButtonLayout, 7, 0);

}

