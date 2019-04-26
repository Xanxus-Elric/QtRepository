#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include "addwidget.h"
#include "editwidget.h"
#include "findwidget.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

private:
    QLineEdit       *NameLine;
    QTextEdit       *AddressText;
    QPushButton     *AddButton;
    QPushButton     *EditButton;
    QPushButton     *RemoveButton;
    QPushButton     *FindButton;
    QPushButton     *LoadFileButton;
    QPushButton     *SaveFileButton;
    QPushButton     *PreButton;
    QPushButton     *NextButton;

    AddWidget       *AddOptForm;
    EditWidget      *EditOptForm;
    FindWidget      *FindOptForm;

private slots:

};

#endif // WIDGET_H
