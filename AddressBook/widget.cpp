#include "widget.h"

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

    //connect the signal to the slot
    connect(this->AddButton, SIGNAL(clicked(bool)), this, SLOT(AddHandler()));
    connect(this->EditButton, SIGNAL(clicked(bool)), this, SLOT(EditHandler()));
    connect(this->RemoveButton, SIGNAL(clicked(bool)), this, SLOT(RemoveHandler()));
    connect(this->FindButton, SIGNAL(clicked(bool)), this, SLOT(FindHandler()));
    connect(this->LoadFileButton, SIGNAL(clicked(bool)), this, SLOT(LoadFileHandler()));
    connect(this->SaveFileButton, SIGNAL(clicked(bool)), this, SLOT(SaveFileHandler()));
    connect(this->PreButton, SIGNAL(clicked(bool)), this, SLOT(PreviousHandler()));
    connect(this->NextButton, SIGNAL(clicked(bool)), this, SLOT(NextHandler()));
}

void Widget::AddConfirmHandler(){

}

void Widget::AddHandler(){
    //Create a New Widget for user input new Information
    AddWidget = new QWidget;
    AddWidget->setWindowTitle("Add Address Book");

    QLineEdit   *Name = new QLineEdit(AddWidget);
    QTextEdit   *Address = new QTextEdit(AddWidget);

    QLabel      *NameLabel = new QLabel("Name", AddWidget);
    QLabel      *AddressLabel = new QLabel("Address", AddWidget);

    QPushButton *ConfirmButton = new QPushButton("Confirm", AddWidget);
    QPushButton *CancelButton = new QPushButton("Cancel", AddWidget);

    QVBoxLayout *ButtonLayout = new QVBoxLayout;
    ButtonLayout->addWidget(ConfirmButton);
    ButtonLayout->addWidget(CancelButton);

    QGridLayout *AddWidgetLayout = new QGridLayout(AddWidget);
    AddWidgetLayout->addWidget(NameLabel, 0, 0);
    AddWidgetLayout->addWidget(Name, 0, 1);
    AddWidgetLayout->addWidget(AddressLabel, 1, 0);
    AddWidgetLayout->addWidget(Address, 1, 1);
    AddWidgetLayout->addLayout(ButtonLayout, 1, 2);

    connect(ConfirmButton, SIGNAL(clicked(bool)), this, SLOT(AddConfirmHandler()));
    connect(CancelButton, SIGNAL(clicked(bool)), AddWidget, SLOT(close()));

    AddWidget->show();
}

void Widget::EditConfirmHandler(){

}

void Widget::EditHandler(){
    //Create a New Widget for user Modify the information
    EditWidget = new QWidget;
    EditWidget->setWindowTitle("Edit Address Book");

    QLabel      *NameLabel = new QLabel("Name", EditWidget);
    QLabel      *AddressLabel = new QLabel("Address", EditWidget);

    QLineEdit   *Name = new QLineEdit(EditWidget);
    QTextEdit   *Address = new QTextEdit(EditWidget);

    Name->setText(this->NameLine->text());
    Address->setText(this->AddressText->toPlainText());

    QPushButton *ConfirmButton = new QPushButton("Confirm", EditWidget);
    QPushButton *CancelButton = new QPushButton("Cancel", EditWidget);

    QVBoxLayout *ButtonLayout = new QVBoxLayout;
    ButtonLayout->addWidget(ConfirmButton);
    ButtonLayout->addWidget(CancelButton);

    QGridLayout *EditWidgetLayout = new QGridLayout(EditWidget);
    EditWidgetLayout->addWidget(NameLabel, 0, 0);
    EditWidgetLayout->addWidget(Name, 0, 1);
    EditWidgetLayout->addWidget(AddressLabel, 1, 0);
    EditWidgetLayout->addWidget(Address, 1, 1);
    EditWidgetLayout->addLayout(ButtonLayout, 1, 2);

    connect(ConfirmButton, SIGNAL(clicked(bool)), this, SLOT(EditConfirmHandler()));
    connect(CancelButton, SIGNAL(clicked(bool)), EditWidget, SLOT(close()));

    EditWidget->show();
}

void Widget::RemoveHandler(){
    //Delete the Current information show on the window
    //and delete it from the Map List
    //Let the Current window show the Next container's information

}

void Widget::FindComfirmHandler(){

}

void Widget::FindHandler(){
    QWidget *FindWidget = new QWidget;
    FindWidget->setWindowTitle("Find a Contacter");

    QLabel      *SearchName = new QLabel("Search Name", FindWidget);
    QLineEdit   *InputName = new QLineEdit(FindWidget);
    QPushButton *ConfirmButton = new QPushButton("Confirm", FindWidget);
    QPushButton *CancelButton = new QPushButton("Cancel", FindWidget);

    QGridLayout *FindWidgetLayout = new QGridLayout(FindWidget);
    FindWidgetLayout->addWidget(SearchName, 0, 0);
    FindWidgetLayout->addWidget(InputName, 0, 1, 1, 2);
    FindWidgetLayout->addWidget(ConfirmButton, 1, 0, 1, 1);
    FindWidgetLayout->addWidget(CancelButton, 1, 2, 1, 1);

    connect(ConfirmButton, SIGNAL(clicked(bool)), this, SLOT(FindComfirmHandler()));
    connect(CancelButton, SIGNAL(clicked(bool)), FindWidget, SLOT(close()));

    FindWidget->show();
}

void Widget::LoadFileHandler(){

}

void Widget::SaveFileHandler(){

}

void Widget::PreviousHandler(){

}

void Widget::NextHandler(){

}








Widget::~Widget()
{

}
