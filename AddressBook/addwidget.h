#ifndef ADDWIDGET_H
#define ADDWIDGET_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <QString>
#include <QMessageBox>

class AddWidget : public QDialog
{
    Q_OBJECT
public:
    explicit AddWidget(QDialog *parent = 0);
    QString GetName();
    QString GetAddress();

    QPushButton *ConfirmButton;
    QPushButton *CancelButton;

private:
    QLineEdit   *Name;
    QTextEdit   *Address;

public slots:
    void ConfirmHandle();

signals:
    void AddConfirmSignal();

};

#endif // ADDWIDGET_H
