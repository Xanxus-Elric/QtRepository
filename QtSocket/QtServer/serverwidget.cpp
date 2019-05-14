#include "serverwidget.h"

ServerWidget::ServerWidget(QWidget *parent)
    : QWidget(parent)
{
    QLabel *ServerLabel = new QLabel("Server", this);

    this->ServerText = new QTextEdit(this);
    this->ServerText->setReadOnly(true);

    QGridLayout *MainLayout = new QGridLayout(this);
    MainLayout->addWidget(ServerLabel, 0, 0);
    MainLayout->addWidget(this->ServerText, 1, 0);

    //Set up the Listening Socket
    this->Server = new QTcpServer(this);

    //Listen any process wait to connect to Server
    if (!this->Server->listen()){
        this->close();
        return ;
    }

    this->ServerText->append(tr("Server Port %1").arg(this->Server->serverPort()));

    connect(this->Server, SIGNAL(newConnection()), this, SLOT(SendConnectMsg()));
}

ServerWidget::~ServerWidget()
{

}

void ServerWidget::SendConnectMsg(){
    //set up the transfer socket
    QTcpSocket *Connection = this->Server->nextPendingConnection();

    connect(Connection, SIGNAL(disconnected()), Connection, SLOT(deleteLater()));

    QString HostStr = Connection->peerAddress().toString();

    int PortNum = Connection->localPort();

    this->ServerText->append(tr("%1 connect to Server").arg(HostStr));
    this->ServerText->append(tr("Port Number %1").arg(PortNum));

    Connection->write("Connect to Server successfully");

    Connection->waitForReadyRead();

    QString Input(Connection->readAll());
    this->ServerText->append(Input);

}
