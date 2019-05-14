#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QTcpSocket>
#include <QGridLayout>
#include <QDebug>
#include <QString>
#include <QTextEdit>
#include <QHBoxLayout>

class ClientWidget : public QWidget
{
    Q_OBJECT

public:
    ClientWidget(QWidget *parent = 0);
    ~ClientWidget();

private:
    QLineEdit   *AddressLine;
    QLineEdit   *PortLine;

    QPushButton *ConnectBtn;
    QPushButton *DisconnectBtn;
    QTcpSocket  *ClientSocket;

    QTextEdit   *InputText;
    QTextEdit   *OutputText;

private slots:
    void ConnectServer();
    void ReadData();
};

#endif // CLIENTWIDGET_H
