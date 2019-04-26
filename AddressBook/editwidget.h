#ifndef EDITWIDGET_H
#define EDITWIDGET_H

#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QString>
#include <QMessageBox>

class EditWidget : public QDialog
{
    Q_OBJECT
public:
    explicit EditWidget(QDialog *parent = 0);
    void SetName(QString Name);
    void SetAddress(QString Address);
    QString GetName();
    QString GetAddress();

private:
    QPushButton *ConfirmButton;
    QPushButton *CancelButton;

    QLineEdit   *NameLine;
    QTextEdit   *AddressText;

public slots:
    void ConfirmHandle();

signals:
    void EditConfirmSignal();
};

#endif // EDITWIDGET_H
