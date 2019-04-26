#include "widget.h"

//this is the Mainwindow of this program
//though this window, we can go to another window

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    qDebug() << "Enter the Program" << endl;

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
    this->EditOptForm = new EditWidget;
    this->FindOptForm = new FindWidget;

    //connect the signal to the slot function
    connect(this->AddButton, SIGNAL(clicked(bool)), this, SLOT(Add()));
    connect(this->AddOptForm, SIGNAL(AddConfirmSignal()), this, SLOT(GetAddInfo()));

    connect(this->EditButton, SIGNAL(clicked(bool)), this, SLOT(Edit()));
    connect(this->EditOptForm, SIGNAL(EditConfirmSignal()), this, SLOT(GetEditInfo()));

    connect(this->FindButton, SIGNAL(clicked(bool)), this, SLOT(Find()));


//    connect(this->RemoveButton, SIGNAL(clicked(bool)), this, SLOT(RemoveHandler()));
//    connect(this->LoadFileButton, SIGNAL(clicked(bool)), this, SLOT(LoadFileHandler()));
//    connect(this->SaveFileButton, SIGNAL(clicked(bool)), this, SLOT(SaveFileHandler()));
//    connect(this->PreButton, SIGNAL(clicked(bool)), this, SLOT(PreviousHandler()));
//    connect(this->NextButton, SIGNAL(clicked(bool)), this, SLOT(NextHandler()));
}

void Widget::GetAddInfo(){
    QMapIterator<QString, QString> i(this->AddressMap);
    int MsgRet;

    //if the User Input the Correct information on the Add Dialog
    //Collect these information
    this->NameLine->setText(this->AddOptForm->GetName());
    this->AddressText->setText(this->AddOptForm->GetAddress());

    if (this->AddressMap.contains(this->NameLine->text())){
        //the Contacter is already existed
        MsgRet = QMessageBox::warning(this,
                             "Add Contacter Warning",
                             "The Contacter is Already existed",
                             QMessageBox::Reset,
                             QMessageBox::Cancel);

        if (MsgRet == QMessageBox::Reset){
            //override it
            this->AddressMap.insert(this->NameLine->text(),
                                    this->AddressText->toPlainText());
        }
        else{
            //do nothing
            return ;
        }
    }
    else{
        this->AddressMap.insert(this->NameLine->text(),
                                this->AddressText->toPlainText());
    }
}

void Widget::Add(){

    this->AddOptForm->exec();
}

void Widget::GetEditInfo(){
    //Get the Information of the Contacter
    this->NameLine->setText(this->EditOptForm->GetName());
    this->AddressText->setText(this->EditOptForm->GetAddress());
}

void Widget::Edit(){
    if (this->NameLine->text().isEmpty() ||
            this->AddressText->toPlainText().isEmpty()){
        QMessageBox::critical(this,
                              "Edit Contacter Error",
                              "The Name or Address is Empty, Please Check",
                              QMessageBox::Ok);
    }
    else{
        this->EditOptForm->SetName(this->NameLine->text());
        this->EditOptForm->SetAddress(this->AddressText->toPlainText());
        this->EditOptForm->exec();
    }
}

void Widget::Find(){

    this->FindOptForm->show();
}

Widget::~Widget()
{

}
