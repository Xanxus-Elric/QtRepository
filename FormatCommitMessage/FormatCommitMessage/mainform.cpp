#include "mainform.h"
#include "ui_mainform.h"
#include <QString>
#include <QDebug>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QDateTime>

MainForm::MainForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainForm)
{
    ui->setupUi(this);

    QObject::connect(&this->Add, SIGNAL(IssueAdd()), this, SLOT(Slot_AddSignal()));
}

MainForm::~MainForm()
{
    delete ui;
}


void MainForm::on_AddBtn_clicked()
{
    this->Add.show();
}

void MainForm::Slot_AddSignal()
{
    int CurrentRow = this->ui->tableWidget->rowCount();
    qDebug() << CurrentRow;

    this->ui->tableWidget->setRowCount(CurrentRow + 1);

    QTableWidgetItem *IssueNumberItem = new QTableWidgetItem(this->Add.IssueNumber.trimmed());
    QTableWidgetItem *IssueDescItem = new QTableWidgetItem(this->Add.IssueDesc.trimmed());

    this->ui->tableWidget->setItem(CurrentRow, 0, IssueNumberItem);
    this->ui->tableWidget->setItem(CurrentRow, 1, IssueDescItem);
}

void MainForm::on_ConvertButton_clicked()
{
    this->ui->FormatMessage->clear();

    if (this->ui->tableWidget->rowCount() == 0){
        QMessageBox::critical(this, "Fail", "Issue List is NULL");
        return ;
    }

    if (this->ui->PlaceGroup->checkedButton() == 0){
        QMessageBox::critical(this, "Fail", "No Place Name select");
        return ;
    }

    if (this->ui->MemberGroup->checkedButton() == 0){
        QMessageBox::critical(this, "Fail", "No Member Name select");
        return ;
    }

    if (this->ui->LabelMarkerEdit->text() == "")
    {
        QMessageBox::critical(this, "Fail", "No Label Marker Add");
        return ;
    }

    int CurrentRow = this->ui->tableWidget->rowCount();
    int LoopFlag = 0;

    QString Head_Str = "**  [M00x]";
    QString IssueStr = "     Issue   : ";
    QString LabelStr = "     Label   : ";
    QString File_Str = "     File    : ";

    this->ui->FormatMessage->append(Head_Str);

    for (LoopFlag = 0; LoopFlag < CurrentRow; LoopFlag++)
    {
        QString TempStr = IssueStr;
        QString IssueNumber = this->ui->tableWidget->item(LoopFlag, 0)->text();
        QString IssueDesc = this->ui->tableWidget->item(LoopFlag, 1)->text();

        TempStr += ("EIP:" + IssueNumber + "    " + IssueDesc);
        this->ui->FormatMessage->append(TempStr);
    }

    QRadioButton *Place = qobject_cast<QRadioButton *>(this->ui->PlaceGroup->checkedButton());
    QRadioButton *Member = qobject_cast<QRadioButton *>(this->ui->MemberGroup->checkedButton());

    QString PlaceName = Place->objectName();
    QString MemberName = Member->objectName();
    QString CurrentTime = QDateTime::currentDateTime().toString("yyyyMMdd");

    if (PlaceName == "User")
        LabelStr += this->ui->UserDefineEdit->text();
    else
        LabelStr += PlaceName;

    LabelStr += ("_D" + CurrentTime + "_" + MemberName);

    LabelStr += ("_" + this->ui->LabelMarkerEdit->text());

    this->ui->FormatMessage->append(LabelStr);

    File_Str += (this->ui->FileDescEdit->text());

    this->ui->FormatMessage->append(File_Str);

    this->ui->tableWidget->clear();
    this->ui->tableWidget->setRowCount(0);
    this->ui->PlaceGroup->checkedButton()->setChecked(false);
    this->ui->MemberGroup->checkedButton()->setChecked(false);
    this->ui->UserDefineEdit->clear();
    this->ui->FileDescEdit->clear();
    this->ui->LabelMarkerEdit->clear();
}

void MainForm::on_pushButton_clicked()
{
    int row=this->ui->tableWidget->row(this->ui->tableWidget->selectedItems().at(0));
    this->ui->tableWidget->removeRow(row);
}
