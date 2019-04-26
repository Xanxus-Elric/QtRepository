#include "addwidget.h"

//Create the Add Widget
AddWidget::AddWidget(QDialog *parent) : QDialog(parent)
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

    connect(this->ConfirmButton, SIGNAL(clicked(bool)), this, SLOT(ConfirmHandle()));
}

QString AddWidget::GetName(){
    return this->Name->text();
}

QString AddWidget::GetAddress(){
    return this->Address->toPlainText();
}

void AddWidget::ConfirmHandle(){
    if (this->Name->text().isEmpty() || this->Address->toPlainText().isEmpty()){
        QMessageBox::critical(this,
                              "Add New Contacter Error",
                              "The Name or Address is empty, Check it and Try Again",
                              QMessageBox::Ok);
    }
    else{
        emit AddConfirmSignal();
        this->close();
    }
}


