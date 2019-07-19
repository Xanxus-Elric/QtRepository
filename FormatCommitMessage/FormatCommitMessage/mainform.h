#ifndef MAINFORM_H
#define MAINFORM_H

#include <QWidget>
#include "addissueform.h"

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

    void on_AddBtn_clicked();
    void Slot_AddSignal();

    void on_ConvertButton_clicked();


    void on_pushButton_clicked();

private:
    Ui::MainForm *ui;

    AddIssueForm Add;
};

#endif // MAINFORM_H
