#ifndef EDITWIDGET_H
#define EDITWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QGridLayout>

class EditWidget : public QWidget
{
    Q_OBJECT
public:
    explicit EditWidget(QWidget *parent = 0);

private:
    QPushButton *ConfirmButton;
    QPushButton *CancelButton;

    QLineEdit   *NameLine;
    QTextEdit   *AddressText;

public slots:
};

#endif // EDITWIDGET_H
