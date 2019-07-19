#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QString>
#include <QDebug>
#include <QStringList>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->ThisIcon.addFile("./yuzu.ico");

    this->setWindowIcon(this->ThisIcon);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_ConvertButton_clicked()
{
    if (this->ui->IssueListEdit->toPlainText().isEmpty()){
        QMessageBox::warning(this, "Convert Fail", "There is no text on the Text Edit");
        return ;
    }

    QString CurrentIssueList = this->ui->IssueListEdit->toPlainText();
    QString ConvertIssueList = "";
    QString TempStr = "";

    this->OldList.push_back(CurrentIssueList);

    QStringList TempIssueList = CurrentIssueList.split("\n");
    int IssueNumber = 1;

    for (int i = 0; i < TempIssueList.length(); i++){
        TempStr = TempIssueList.value(i);

        if (TempStr.contains("Message") || \
                TempStr.contains("Revision") || \
                TempStr.contains("Author") || \
                TempStr.contains("Date") || \
                TempStr.contains("----"))
        {
            continue ;
        }

        else if (TempStr.contains("Added") || \
                 TempStr.contains("Deleted") || \
                 TempStr.contains("Modified"))
        {
            TempStr = "               " + TempStr;
        }
        else if (TempStr.contains("M00x"))
        {
            TempStr.replace("M00x", "M" + QString("%1").arg(IssueNumber,3,10,QLatin1Char('0')));
            IssueNumber++;
        }

        TempStr += "\n";
        ConvertIssueList += TempStr;
    }

    this->ui->IssueListEdit->setText(ConvertIssueList);
    this->ui->IssueListEdit->selectAll();
    this->ui->IssueListEdit->copy();
}

void Widget::on_pushButton_clicked()
{
    if (this->OldList.isEmpty()){
        QMessageBox::warning(this, "Fail", "There isn't any older Text!\n");
        return ;
    }

    QString OldIssueList = this->OldList.constLast();
    this->OldList.pop_back();

    this->ui->IssueListEdit->setText(OldIssueList);
}
