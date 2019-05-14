#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QString>
#include <QLabel>
#include <QTextEdit>
#include <QGridLayout>
#include <QDebug>
#include <QByteArray>
#include <QTextStream>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

private:
    QTcpServer *Server;

    QTextEdit  *Text;

private slots:
    void SendMsg();
};

#endif // WIDGET_H
