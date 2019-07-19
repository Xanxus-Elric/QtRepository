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

    this->MainIcon.addFile("./ConvertIcon.ico");
    this->setWindowIcon(this->MainIcon);

<<<<<<< HEAD
    this->ui->NumberEdit->setFocus();

=======
>>>>>>> 6f039d58c335fbb9afe5f2de6252e01731a95f98
    this->ui->CreateLabel->setEnabled(false);

    this->ui->tableWidget->setSelectionBehavior ( QAbstractItemView::SelectRows); //设置选择行为，以行为单位
    this->ui->tableWidget->setSelectionMode ( QAbstractItemView::SingleSelection);

<<<<<<< HEAD
    this->ui->DescEdit->setPlaceholderText("Press 'Enter' to Confirm Issue Number and Issue Description!");
=======
    this->ui->DescEdit->setPlaceholderText("Press 'Enter' to confirm input");
>>>>>>> 6f039d58c335fbb9afe5f2de6252e01731a95f98
}

MainForm::~MainForm()
{
    delete ui;
}

void MainForm::on_ConvertButton_clicked()
{
    int CurrentRow = this->ui->tableWidget->rowCount();
    bool CreateLabel = true;

    QAbstractButton *PlaceSelect = this->ui->PlaceGroup->checkedButton();
    QAbstractButton *MemberSelect = this->ui->MemberGroup->checkedButton();
    QString         LabelString = this->ui->LabelMarkerEdit->text();

    QString Head_Str = "**  [M00x]";
    QString IssueStr = "     Issue   : ";
    QString LabelStr = "     Label   : ";
    QString File_Str = "     File    : ";

    this->ui->FormatMessage->clear();

    if (CurrentRow == 0){
        QMessageBox::critical(this, "Fail", "Issue List is Empty");
        return ;
    }

    if (PlaceSelect == 0 || MemberSelect == 0 || LabelString == ""){
        int Result = QMessageBox::warning(this, "Warning", "Will Not create the Label", QMessageBox::Ok, QMessageBox::Cancel);
        if (Result == QMessageBox::Cancel){
            CreateLabel = false;
            return ;
        }
    }

    this->ui->FormatMessage->append(Head_Str);
<<<<<<< HEAD

    QString TempStr;
    QString IssueNumber;
    QString IssueDesc;
    QTableWidgetItem *ColumnFirst;
    QTableWidgetItem *ColumnSecond;

    for (int LoopFlag = 0; LoopFlag < CurrentRow; LoopFlag++)
    {
        TempStr = IssueStr;

        ColumnFirst = this->ui->tableWidget->item(LoopFlag, 0);
        ColumnSecond = this->ui->tableWidget->item(LoopFlag, 1);

        if (ColumnFirst){
            IssueNumber = ColumnFirst->text();
        }else{
            IssueNumber = "";
        }

=======

    QString TempStr;
    QString IssueNumber;
    QString IssueDesc;
    QTableWidgetItem *ColumnFirst;
    QTableWidgetItem *ColumnSecond;

    for (int LoopFlag = 0; LoopFlag < CurrentRow; LoopFlag++)
    {
        TempStr = IssueStr;

        ColumnFirst = this->ui->tableWidget->item(LoopFlag, 0);
        ColumnSecond = this->ui->tableWidget->item(LoopFlag, 1);

        if (ColumnFirst){
            IssueNumber = ColumnFirst->text();
        }else{
            IssueNumber = "";
        }

>>>>>>> 6f039d58c335fbb9afe5f2de6252e01731a95f98
        if (ColumnSecond){
            IssueDesc = ColumnSecond->text();
        }else{
            IssueDesc = "";
        }

        TempStr += ("EIP:" + IssueNumber + "    " + IssueDesc);
        this->ui->FormatMessage->append(TempStr);
    }

    if (CreateLabel){
        QRadioButton *Place = qobject_cast<QRadioButton *>(PlaceSelect);
        QRadioButton *Member = qobject_cast<QRadioButton *>(MemberSelect);

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
    }

    File_Str += (this->ui->FileDescEdit->text());

    this->ui->FormatMessage->append(File_Str);

    this->ui->tableWidget->clear();
    this->ui->tableWidget->setRowCount(0);
    this->ui->UserDefineEdit->clear();
    this->ui->FileDescEdit->clear();
    this->ui->LabelMarkerEdit->clear();

    this->ui->FormatMessage->selectAll();
    this->ui->FormatMessage->copy();

    this->ui->FormatMessage->append("**************************************************");
    this->ui->FormatMessage->append("The Commit Message has been copied to clipboard");
    this->ui->FormatMessage->append("Just use Crtl+V to paste the Commit Message to Git");
    this->ui->FormatMessage->append("**************************************************");
}

void MainForm::on_checkBox_stateChanged(int arg1)
<<<<<<< HEAD
{
    if (this->ui->checkBox->checkState() == Qt::Checked){
        this->ui->CreateLabel->setEnabled(true);
    }
    else{
        this->ui->CreateLabel->setEnabled(false);
    }
}



void MainForm::on_DescEdit_returnPressed()
{
    int CurrentRowCount = this->ui->tableWidget->rowCount();

    QTableWidgetItem *IssueNumber = new QTableWidgetItem(this->ui->NumberEdit->text());
    QTableWidgetItem *IssueDesc = new QTableWidgetItem(this->ui->DescEdit->text());

    this->ui->tableWidget->setRowCount(this->ui->tableWidget->rowCount()+1);

    this->ui->tableWidget->setItem(CurrentRowCount, 0, IssueNumber);
    this->ui->tableWidget->setItem(CurrentRowCount, 1, IssueDesc);

    this->ui->NumberEdit->clear();
    this->ui->DescEdit->clear();
    this->ui->NumberEdit->setFocus();
}

void MainForm::on_DeleteButton_clicked()
{
=======
{
    if (this->ui->checkBox->checkState() == Qt::Checked){
        this->ui->CreateLabel->setEnabled(true);
    }
    else{
        this->ui->CreateLabel->setEnabled(false);
    }
}



void MainForm::on_DescEdit_returnPressed()
{
    int CurrentRowCount = this->ui->tableWidget->rowCount();

    QTableWidgetItem *IssueNumber = new QTableWidgetItem(this->ui->NumberEdit->text());
    QTableWidgetItem *IssueDesc = new QTableWidgetItem(this->ui->DescEdit->text());

    this->ui->tableWidget->setRowCount(this->ui->tableWidget->rowCount()+1);

    this->ui->tableWidget->setItem(CurrentRowCount, 0, IssueNumber);
    this->ui->tableWidget->setItem(CurrentRowCount, 1, IssueDesc);

    this->ui->NumberEdit->clear();
    this->ui->DescEdit->clear();
    this->ui->NumberEdit->setFocus();
}

void MainForm::on_DeleteButton_clicked()
{
>>>>>>> 6f039d58c335fbb9afe5f2de6252e01731a95f98
    int RowIndex = this->ui->tableWidget->currentRow();

    if (RowIndex != -1){
        this->ui->tableWidget->removeRow(RowIndex);
    }
}
