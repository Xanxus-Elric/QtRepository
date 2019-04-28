#include "adddialog.h"

AddDialog::AddDialog(QWidget *parent) :
    QDialog(parent)
{
    //Set the Dialog Title
    this->setWindowTitle("Add a New Contacter");

    //Add the Widget to the Form
    QLabel *NamePrompt = new QLabel("Please Input Contacter's Name", this);
    QLabel *AddressPrompt = new QLabel("Please Input Contacter's Address", this);

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
    connect(this->ConfirmBtn, SIGNAL(clicked(bool)), this, SLOT(AddConfirmHandle()));
    connect(this->CancelBtn, SIGNAL(clicked(bool)), this, SLOT(AddCancelHandle()));
}

void AddDialog::AddConfirmHandle(){
    //Judge if the LineEdit or TextEdit is Empty
    if (this->NameInput->text().isEmpty() ||
        this->AddressInput->toPlainText().isEmpty()){
        QMessageBox::critical(this,
                              "Add Contacter Error",
                              "Name or Address is Empty");

        return ;
    }
    else{
        //send the Signal to MainWidget, let it get the Name and Address
        emit AddFinishSignal();
        this->AddCancelHandle();
    }
}

QString AddDialog::GetName(){
    return this->NameInput->text();
}

QString AddDialog::GetAddress(){
    return this->AddressInput->toPlainText();
}

void AddDialog::AddCancelHandle(){
    this->NameInput->clear();
    this->AddressInput->clear();
    this->NameInput->setFocus();
    this->close();
}

AddDialog::~AddDialog()
{

}
