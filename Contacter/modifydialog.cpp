#include "modifydialog.h"

ModifyDialog::ModifyDialog(QWidget *parent) :
    QDialog(parent)
{
    //Set the Window Title
    this->setWindowTitle("Modify Contacter's Information");

    //Add Widget to the Form
    QLabel *NamePrompt = new QLabel("Please Modify Contacter's Name", this);
    QLabel *AddressPrompt = new QLabel("Please Modify Contacter's Address", this);

    this->NameInput = new QLineEdit(this);
    this->AddressInput = new QTextEdit(this);

    this->ConfirmBtn = new QPushButton("Confirm", this);
    this->CancelBtn = new QPushButton("Cancel", this);

    //Set the Layout
    QHBoxLayout *BtnLayout = new QHBoxLayout();
    BtnLayout->addWidget(this->ConfirmBtn);
    BtnLayout->addWidget(this->CancelBtn);

    QGridLayout *MainLayout = new QGridLayout(this);
    MainLayout->addWidget(NamePrompt, 0, 0);
    MainLayout->addWidget(this->NameInput, 1, 0);
    MainLayout->addWidget(AddressPrompt, 2, 0);
    MainLayout->addWidget(this->AddressInput, 3, 0);
    MainLayout->addLayout(BtnLayout, 6, 0);

    //connect the Handle
    connect(this->ConfirmBtn, SIGNAL(clicked(bool)), this, SLOT(ModifyConfirmHandle()));
    connect(this->CancelBtn, SIGNAL(clicked(bool)), this, SLOT(ModifyCancelHandle()));
}

void ModifyDialog::ModifyConfirmHandle(){
    //Check if the LineEdit or TextEdit is Empty
    if (this->NameInput->text().isEmpty() ||
        this->AddressInput->toPlainText().isEmpty()){
        QMessageBox::critical(this,
                              "Modify Contacter's Information Error",
                              "Name or Address is Empty");
        return ;
    }
    else{
        emit ModifyFinishSignal();
        this->ModifyCancelHandle();
    }
}

void ModifyDialog::SetName(QString Name){
    this->NameInput->setText(Name);
}

QString ModifyDialog::GetName(){
    return this->NameInput->text();
}

void ModifyDialog::SetAddress(QString Address){
    this->AddressInput->setText(Address);
}

QString ModifyDialog::GetAddress(){
    return this->AddressInput->toPlainText();
}

void ModifyDialog::ModifyCancelHandle(){
    this->NameInput->clear();
    this->AddressInput->clear();
    this->close();
}

ModifyDialog::~ModifyDialog()
{
}
