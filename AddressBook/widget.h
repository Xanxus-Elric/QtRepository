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

    QWidget         *AddWidget;
    QWidget         *EditWidget;
    QWidget         *FindWidget;

private slots:
    void AddHandler();
    void EditHandler();
    void RemoveHandler();
    void FindHandler();
    void LoadFileHandler();
    void SaveFileHandler();
    void PreviousHandler();
    void NextHandler();

    void AddConfirmHandler();
    void EditConfirmHandler();
    void FindComfirmHandler();

};

#endif // WIDGET_H
