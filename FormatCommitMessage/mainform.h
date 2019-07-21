#ifndef MAINFORM_H
#define MAINFORM_H

#include <QWidget>
#include <QIcon>
#include <QStringList>

namespace Ui {
class MainForm;
}

class MainForm : public QWidget
{
    Q_OBJECT

public:
    explicit MainForm(QWidget *parent = 0);
    ~MainForm();

private slots:

    void on_IssueNumberEdit_returnPressed();

    void on_IssueDescEdit_returnPressed();

    void on_ModuleGroupEdit_returnPressed();

    void on_MemberNameEdit_returnPressed();

    void on_LabelMarkerEdit_returnPressed();

    void on_IssueDescEdit_editingFinished();

private:
    Ui::MainForm *ui;

    QIcon MainIcon;

    QStringList IssueList;

    bool NoLabel;

};

#endif // MAINFORM_H
