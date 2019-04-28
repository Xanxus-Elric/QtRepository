#ifndef MODIFYDIALOG_H
#define MODIFYDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QMessageBox>
#include <QString>

class ModifyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ModifyDialog(QWidget *parent = 0);
    ~ModifyDialog();

    void SetName(QString Name);
    void SetAddress(QString Address);
    QString GetName();
    QString GetAddress();

private:  
    QLineEdit *NameInput;
    QTextEdit *AddressInput;

    QPushButton *ConfirmBtn;
    QPushButton *CancelBtn;

private slots:
    void ModifyConfirmHandle();
    void ModifyCancelHandle();

signals:
    void ModifyFinishSignal();
};

#endif // MODIFYDIALOG_H
