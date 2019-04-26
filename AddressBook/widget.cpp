#include "widget.h"

//Create the Main Window of this program
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    //set up the UI Page on this Constructor function
    QLabel *NamePrompt = new QLabel("Name", this);
    QLabel *AddressPrompt = new QLabel("Address", this);

    this->NameLine = new QLineEdit(this);
    this->AddressText = new QTextEdit(this);

    this->AddButton         = new QPushButton("Add", this);
    this->EditButton        = new QPushButton("Edit", this);
    this->RemoveButton      = new QPushButton("Remove", this);
    this->FindButton        = new QPushButton("Find", this);
    this->LoadFileButton    = new QPushButton("Load", this);
    this->SaveFileButton    = new QPushButton("Save", this);
    this->PreButton         = new QPushButton("Previos", this);
    this->NextButton        = new QPushButton("Next", this);

    QVBoxLayout *OptButtonLayout = new QVBoxLayout;
    OptButtonLayout->addWidget(this->AddButton);
    OptButtonLayout->addWidget(this->EditButton);
    OptButtonLayout->addWidget(this->RemoveButton);
    OptButtonLayout->addWidget(this->FindButton);
    OptButtonLayout->addWidget(this->LoadFileButton);
    OptButtonLayout->addWidget(this->SaveFileButton);

    QHBoxLayout *PreNextLayout = new QHBoxLayout;
    PreNextLayout->addWidget(this->PreButton);
    PreNextLayout->addWidget(this->NextButton);

    QGridLayout *MainLayout = new QGridLayout(this);
    MainLayout->addWidget(NamePrompt, 0, 0);
    MainLayout->addWidget(this->NameLine, 0, 1);
    MainLayout->addWidget(AddressPrompt, 1, 0);
    MainLayout->addWidget(this->AddressText, 1, 1);
    MainLayout->addLayout(OptButtonLayout, 1, 2);
    MainLayout->addLayout(PreNextLayout, 2, 1);
    //Setup UI Page Over Here

    //the mainwindow just show the information, user can only add the new container when click Add
    this->NameLine->setReadOnly(true);
    this->AddressText->setReadOnly(true);

    this->AddOptForm = new AddWidget;
    this->AddOptForm->show();

    this->EditOptForm = new EditWidget;
    this->EditOptForm->show();

    this->FindOptForm = new FindWidget;
    this->FindOptForm->show();

//    //connect the signal to the slot
//    connect(this->AddButton, SIGNAL(clicked(bool)), this, SLOT(AddHandler()));
//    connect(this->EditButton, SIGNAL(clicked(bool)), this, SLOT(EditHandler()));
//    connect(this->RemoveButton, SIGNAL(clicked(bool)), this, SLOT(RemoveHandler()));
//    connect(this->FindButton, SIGNAL(clicked(bool)), this, SLOT(FindHandler()));
//    connect(this->LoadFileButton, SIGNAL(clicked(bool)), this, SLOT(LoadFileHandler()));
//    connect(this->SaveFileButton, SIGNAL(clicked(bool)), this, SLOT(SaveFileHandler()));
//    connect(this->PreButton, SIGNAL(clicked(bool)), this, SLOT(PreviousHandler()));
//    connect(this->NextButton, SIGNAL(clicked(bool)), this, SLOT(NextHandler()));
}

Widget::~Widget()
{

}
