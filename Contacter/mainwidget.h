#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QString>
#include <QStringList>
#include <QFile>
#include <QMap>
#include <QMapIterator>
#include <QDebug>
#include <QTextStream>
#include <QCloseEvent>
#include "adddialog.h"
#include "modifydialog.h"
#include "searchdialog.h"

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();

    QLineEdit   *NameEdit;
    QTextEdit   *AddressEdit;

private:
    QPushButton     *AddBtn;
    QPushButton     *DelBtn;
    QPushButton     *ModifyBtn;
    QPushButton     *SearchBtn;
    QPushButton     *PrevBtn;
    QPushButton     *NextBtn;

    AddDialog       *AddForm;
    ModifyDialog    *ModifyForm;
    SearchDialog    *SearchForm;

    QMap<QString, QString> InfoMap;

    QFile           *MapFile;

private slots:
    void LoadFile();
    void SaveFile();
    void AddHandle();
    void GetAddInfo();
    void DelHandle();
    void ModifyHandle();
    void GetModifyInfo();
    void SearchHandle();
    void GetSearchInfo();
    void PrevHandle();
    void NextHandle();

public slots:
};

#endif // MAINWIDGET_H
