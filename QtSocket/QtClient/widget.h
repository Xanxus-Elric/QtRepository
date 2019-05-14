#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtNetwork/QTcpSocket>
#include <QTextEdit>
#include <QLabel>
#include <QString>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QByteArray>
#include <QTextStream>
#include <QDebug>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

private:
    QLineEdit *NameLine;
    QLineEdit *PortLine;

    QPushButton *ConnectBtn;
    QTextEdit   *Text;

    QTcpSocket *ClientSocket;

private slots:
    void Connect();
    void Read();
};

#endif // WIDGET_H
