#ifndef SERVERWIDGET_H
#define SERVERWIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QLabel>
#include <QTextEdit>
#include <QGridLayout>
#include <QString>
#include <QHostAddress>

class ServerWidget : public QWidget
{
    Q_OBJECT

public:
    ServerWidget(QWidget *parent = 0);
    ~ServerWidget();

private:
    QTcpServer  *Server;
    QTextEdit   *ServerText;

private slots:
    void SendConnectMsg();
};

#endif // SERVERWIDGET_H
