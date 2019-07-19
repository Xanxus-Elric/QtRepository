#ifndef ADDISSUEFORM_H
#define ADDISSUEFORM_H

#include <QWidget>
#include <QString>

namespace Ui {
class AddIssueForm;
}

class AddIssueForm : public QWidget
{
    Q_OBJECT

public:
    explicit AddIssueForm(QWidget *parent = 0);
    ~AddIssueForm();

    QString IssueNumber;
    QString IssueDesc;

private slots:
    void on_OkBtn_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::AddIssueForm *ui;

signals:
    void IssueAdd();
};

#endif // ADDISSUEFORM_H
