#ifndef ADDWIDGET_H
#define ADDWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QSpacerItem>

class AddWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AddWidget(QWidget *parent = 0);

private:
    QLineEdit   *Name;
    QTextEdit   *Address;

    QPushButton *ConfirmButton;
    QPushButton *CancelButton;


public slots:
};

#endif // ADDWIDGET_H
