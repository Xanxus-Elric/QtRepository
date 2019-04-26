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
#include <QMessageBox>
#include <QMap>
#include <QMapIterator>
#include <QDebug>
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

    QMap<QString, QString> AddressMap;

private slots:    
    void Add();
    void GetAddInfo();
    void Edit();
    void GetEditInfo();
    void Find();

};

#endif // WIDGET_H
