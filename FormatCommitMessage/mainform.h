#ifndef MAINFORM_H
#define MAINFORM_H

#include <QWidget>
#include <QIcon>

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

    void on_ConvertButton_clicked();

    void on_checkBox_stateChanged(int arg1);

    void on_DescEdit_returnPressed();

    void on_DeleteButton_clicked();

private:
    Ui::MainForm *ui;

    QIcon MainIcon;

};

#endif // MAINFORM_H
