#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QLabel *ServerName = new QLabel("Server Name", this);
    QLabel *ServerHost = new QLabel("Server Host", this);

    this->NameLine = new QLineEdit(this);
    this->PortLine = new QLineEdit(this);

    this->ConnectBtn = new QPushButton("Connect", this);

    this->Text = new QTextEdit(this);

    QGridLayout *MainLayout = new QGridLayout(this);
    MainLayout->addWidget(ServerName, 0, 0);
    MainLayout->addWidget(this->NameLine, 0, 1);
    MainLayout->addWidget(ServerHost, 1, 0);
    MainLayout->addWidget(this->PortLine, 1, 1);
    MainLayout->addWidget(this->ConnectBtn, 2, 0);
    MainLayout->addWidget(this->Text, 3, 0);

    this->ClientSocket = new QTcpSocket(this);

    connect(this->ConnectBtn, SIGNAL(clicked(bool)), this, SLOT(Connect()));
    connect(this->ClientSocket, SIGNAL(readyRead()), this, SLOT(Read()));

}

Widget::~Widget()
{

}

void Widget::Connect(){
    qDebug() << "Connect";

    this->ClientSocket->abort();
    this->ClientSocket->connectToHost(this->NameLine->text(),
                                      this->PortLine->text().toInt());
}

void Widget::Read(){
    qDebug() << "Read";

    QByteArray Block;

    Block = this->ClientSocket->readAll();

    QTextStream In(Block);

    QString InStr = In.readAll();

    this->Text->setText(InStr);
}


