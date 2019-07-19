#include "addissueform.h"
#include "ui_addissueform.h"
#include <QMessageBox>

AddIssueForm::AddIssueForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddIssueForm)
{
    ui->setupUi(this);
}

AddIssueForm::~AddIssueForm()
{
    delete ui;
}

void AddIssueForm::on_OkBtn_clicked()
{
    if ((this->ui->IssueNumEdit->text() == "") && \
        (this->ui->IssueDescEdit->text() == ""))
    {
        QMessageBox::critical(this, "Add Issue Fail", "Both Edit is NULL", QMessageBox::Ok);
        return ;
    }
    else
    {
        this->IssueNumber = this->ui->IssueNumEdit->text();
        this->ui->IssueNumEdit->clear();

        this->IssueDesc = this->ui->IssueDescEdit->text();
        this->ui->IssueDescEdit->clear();

        emit this->IssueAdd();

        this->hide();
    }
}

void AddIssueForm::on_pushButton_2_clicked()
{
    this->ui->IssueNumEdit->clear();
    this->ui->IssueDescEdit->clear();

    this->hide();
}
