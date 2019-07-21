#include "mainform.h"
#include "ui_mainform.h"
#include <QString>
#include <QDebug>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QDateTime>
#include <QStringList>

MainForm::MainForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainForm)
{
    ui->setupUi(this);

    //Set the Application's Icon
    this->MainIcon.addFile("./ConvertIcon.ico");
    this->setWindowIcon(this->MainIcon);

    //Set some prompt in the line edit
    this->ui->IssueDescEdit->setPlaceholderText("Press 'TAB' to continue input Issue, Press 'ENTER' to convert commit message!");
    this->ui->ModuleGroupEdit->setPlaceholderText("'LEM' for 'Lenovo Module'");
    this->ui->MemberNameEdit->setPlaceholderText("'EY' for 'EdwardYang'");
    this->ui->LabelMarkerEdit->setPlaceholderText("For Example, '01'");

    //Set configuration of some item
    this->ui->ModuleGroupEdit->setFocus();
    this->NoLabel = true;
}

MainForm::~MainForm()
{
    delete ui;
}

void MainForm::on_IssueNumberEdit_returnPressed()
{
    this->ui->IssueDescEdit->setFocus();
}

void MainForm::on_IssueDescEdit_returnPressed()
{
    QString Head_Str = "**  [M00x]";
    QString IssueStr = "     Issue  : EIP:";
    QString LabelStr = "     Label  : ";
    QString File_Str = "     File   : ";

    this->ui->ConvertResultEdit->clear();

    this->ui->ConvertResultEdit->append(Head_Str);

    for (int i = 0; i < this->IssueList.length(); i++){
        this->ui->ConvertResultEdit->append(this->IssueList.at(i));
    }

    QString IssueNumber = this->ui->IssueNumberEdit->text().trimmed();
    QString IssueDesc = this->ui->IssueDescEdit->text().trimmed();
    QString TempStr = "";

    if (IssueDesc.isEmpty()){
        QMessageBox::warning(this, "Add Issue Fail!", "The Issue Description is Empty!");
        return ;
    }

    if (IssueNumber.isEmpty()){
        TempStr = (IssueStr + IssueDesc);
    }
    else{
        TempStr = (IssueStr + IssueNumber + "    " + IssueDesc);
    }

    this->ui->ConvertResultEdit->append(TempStr);

    if (!this->NoLabel){
        LabelStr += this->ui->ModuleGroupEdit->text().trimmed();
        LabelStr += ("_D" + QDateTime::currentDateTime().toString("yyyyMMdd") + "_");
        LabelStr += this->ui->MemberNameEdit->text().trimmed();
        LabelStr += ("_" + this->ui->LabelMarkerEdit->text().trimmed());
    }

    this->ui->ConvertResultEdit->append(LabelStr);

    this->ui->ConvertResultEdit->append(File_Str);

    this->ui->ConvertResultEdit->selectAll();
    this->ui->ConvertResultEdit->copy();

    this->ui->ConvertResultEdit->append("The Commit Message has been copyed to clipboard!\n");

    this->ui->ModuleGroupEdit->setEnabled(true);
    this->ui->ModuleGroupEdit->clear();
    this->ui->ModuleGroupEdit->setFocus();

    this->ui->MemberNameEdit->setEnabled(true);
    this->ui->MemberNameEdit->clear();

    this->ui->LabelMarkerEdit->setEnabled(true);
    this->ui->LabelMarkerEdit->clear();

    this->ui->IssueDescEdit->clear();
    this->ui->IssueNumberEdit->clear();

    this->IssueList.clear();
}

void MainForm::on_ModuleGroupEdit_returnPressed()
{
    this->ui->ConvertResultEdit->clear();

    if (this->ui->ModuleGroupEdit->text().isEmpty()){
        int result = QMessageBox::warning(this, "Will not Create Label!", "Will Not Create the Label", QMessageBox::Ok, QMessageBox::Cancel);
        if (result == QMessageBox::Ok){
            this->ui->IssueNumberEdit->setFocus();

            this->ui->ModuleGroupEdit->setEnabled(false);
            this->ui->MemberNameEdit->setEnabled(false);
            this->ui->LabelMarkerEdit->setEnabled(false);
        }
        else{
            return ;
        }
    }
    else{
        this->ui->MemberNameEdit->setFocus();
        this->NoLabel = false;
    }
}

void MainForm::on_MemberNameEdit_returnPressed()
{
    if (this->ui->MemberNameEdit->text().isEmpty()){
        int result = QMessageBox::warning(this, "Will not Create Label!", "Will Not Create the Label", QMessageBox::Ok, QMessageBox::Cancel);
        if (result == QMessageBox::Ok){
            this->ui->IssueNumberEdit->setFocus();

            this->ui->ModuleGroupEdit->setEnabled(false);
            this->ui->MemberNameEdit->setEnabled(false);
            this->ui->LabelMarkerEdit->setEnabled(false);
        }
        else{
            return ;
        }
    }
    else{
        this->ui->LabelMarkerEdit->setFocus();
        this->NoLabel = false;
    }
}

void MainForm::on_LabelMarkerEdit_returnPressed()
{
    if (this->ui->LabelMarkerEdit->text().isEmpty()){
        int result = QMessageBox::warning(this, "Will not Create Label!", "Will Not Create the Label", QMessageBox::Ok, QMessageBox::Cancel);
        if (result == QMessageBox::Ok){
            this->ui->IssueNumberEdit->setFocus();

            this->ui->ModuleGroupEdit->setEnabled(false);
            this->ui->MemberNameEdit->setEnabled(false);
            this->ui->LabelMarkerEdit->setEnabled(false);
        }
        else{
            return ;
        }
    }
    else{
        this->ui->IssueNumberEdit->setFocus();
        this->NoLabel = false;
    }
}

void MainForm::on_IssueDescEdit_editingFinished()
{
    if (!this->ui->ConvertResultEdit->hasFocus()){
        return ;
    }
    else{
        QString IssueStr = "     Issue  : EIP:";
        QString IssueNumber = this->ui->IssueNumberEdit->text().trimmed();
        QString IssueDesc = this->ui->IssueDescEdit->text().trimmed();
        QString TempStr = "";

        if (IssueDesc.isEmpty()){
            QMessageBox::warning(this, "Add Issue Fail!", "The Issue Description is Empty!");
            return ;
        }

        if (IssueNumber.isEmpty()){
            TempStr = (IssueStr + IssueDesc);
        }
        else{
            TempStr = (IssueStr + IssueNumber + "    " + IssueDesc);
        }

        this->IssueList << TempStr;
        this->ui->ConvertResultEdit->append(TempStr.trimmed());

        this->ui->IssueNumberEdit->clear();
        this->ui->IssueDescEdit->clear();
        this->ui->IssueNumberEdit->setFocus();
    }
}
