#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QMessageBox>
#include <QString>

class AddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddDialog(QWidget *parent = 0);
    ~AddDialog();

    QString GetName();
    QString GetAddress();

private:
    QLineEdit   *NameInput;
    QTextEdit   *AddressInput;

    QPushButton *ConfirmBtn;
    QPushButton *CancelBtn;

private slots:
    void AddConfirmHandle();
    void AddCancelHandle();

signals:
    void AddFinishSignal();

};

#endif // ADDDIALOG_H
