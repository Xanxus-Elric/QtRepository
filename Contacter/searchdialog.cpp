#include "searchdialog.h"

SearchDialog::SearchDialog(QWidget *parent) :
    QDialog(parent)
{
    QLabel *NamePrompt = new QLabel("Search Name: ", this);
    this->SearchName = new QLineEdit(this);
    this->ConfirmBtn = new QPushButton("Search", this);

    QHBoxLayout *MainLayout = new QHBoxLayout(this);
    MainLayout->addWidget(NamePrompt);
    MainLayout->addWidget(this->SearchName);
    MainLayout->addWidget(this->ConfirmBtn);

}

void SearchDialog::SearchConfirmHandle(){
    if (this->SearchName->text().isEmpty()){
        QMessageBox::critical(this,
                              "Search Contacter Error",
                              "Search Name is Empty");
        return ;
    }
    else{
        emit SearchFinishSignal();
        this->SearchName->clear();
        this->close();
    }
}

QString SearchDialog::GetSearchName(){
    return this->SearchName->text();
}

SearchDialog::~SearchDialog()
{

}
