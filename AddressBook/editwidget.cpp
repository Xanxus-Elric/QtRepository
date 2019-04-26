#include "editwidget.h"

EditWidget::EditWidget(QDialog *parent) : QDialog(parent)
{
    QLabel *NamePrompt = new QLabel("Edit the Name:", this);
    QLabel *AddressPrompt = new QLabel("Edit the Address: ", this);

    //when initialize the LineEdit, Need Get information from QMap
    this->NameLine = new QLineEdit(this);
    //when initialize the TextEdit, Need Get Information form QMap
    this->AddressText = new QTextEdit(this);

    this->ConfirmButton = new QPushButton("Confirm", this);
    this->CancelButton = new QPushButton("Cancel", this);

    QHBoxLayout *ButtonLayout = new QHBoxLayout;
    ButtonLayout->addWidget(this->ConfirmButton);
    ButtonLayout->addWidget(this->CancelButton);

    QGridLayout *MainLayout = new QGridLayout(this);
    MainLayout->addWidget(NamePrompt, 0, 0);
    MainLayout->addWidget(this->NameLine, 1, 0);
    MainLayout->addWidget(AddressPrompt, 3, 0);
    MainLayout->addWidget(this->AddressText, 4, 0);
    MainLayout->addLayout(ButtonLayout, 7, 0);

    connect(this->ConfirmButton, SIGNAL(clicked(bool)), this, SLOT(ConfirmHandle()));
}

void EditWidget::SetName(QString Name){
    this->NameLine->setText(Name);
}

void EditWidget::SetAddress(QString Address){
    this->AddressText->setText(Address);
}

void EditWidget::ConfirmHandle(){
    if (this->NameLine->text().isEmpty() ||
            this->AddressText->toPlainText().isEmpty()){
        QMessageBox::critical(this,
                              "Edit Contacter Error",
                              "The Name or Address is Empty, Check it and Try Again",
                              QMessageBox::Ok);
    }
    else{
        emit EditConfirmSignal();
        this->close();
    }
}

QString EditWidget::GetName(){
    return this->NameLine->text();
}

QString EditWidget::GetAddress(){
    return this->AddressText->toPlainText();
}
