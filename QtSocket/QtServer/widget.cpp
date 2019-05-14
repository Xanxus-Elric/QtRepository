#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QLabel *PromptLabel = new QLabel("Server", this);

    this->Text = new QTextEdit(this);

    QGridLayout *MainLayout = new QGridLayout(this);
    MainLayout->addWidget(PromptLabel, 0, 0);
    MainLayout->addWidget(this->Text, 1, 0);

    this->Server = new QTcpServer(this);

    if (!this->Server->listen()){
        this->close();
        return ;
    }

    qDebug() << this->Server->serverAddress().toString();
    this->Text->setText(tr("Server Port %1\n").arg(this->Server->serverPort()));

    connect(this->Server, SIGNAL(newConnection()), this, SLOT(SendMsg()));
}

Widget::~Widget()
{

}

void Widget::SendMsg(){
    QByteArray Block;
    QTextStream out(&Block);

    qDebug() << "hello world";

    out << "Hello World";

    QTcpSocket *ServerSocket = this->Server->nextPendingConnection();
    connect(ServerSocket, SIGNAL(disconnected()), ServerSocket, SLOT(deleteLater()));

    ServerSocket->write(Block);

    ServerSocket->disconnectFromHost();
}
