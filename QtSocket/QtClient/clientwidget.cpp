#include "clientwidget.h"

ClientWidget::ClientWidget(QWidget *parent)
    : QWidget(parent)
{
    QLabel *HostLabel = new QLabel("Host", this);
    QLabel *PortLabel = new QLabel("Port", this);

    this->AddressLine = new QLineEdit("Localhost", this);
    this->PortLine = new QLineEdit();

    this->ConnectBtn = new QPushButton("Connect", this);
    this->DisconnectBtn = new QPushButton("Disconnect", this);

    this->InputText = new QTextEdit(this);
    this->OutputText = new QTextEdit(this);
    this->OutputText->setReadOnly(true);

    QHBoxLayout *ButtonLayout = new QHBoxLayout();
    ButtonLayout->addWidget(this->ConnectBtn);
    ButtonLayout->addWidget(this->DisconnectBtn);

    QGridLayout *MainLayout = new QGridLayout(this);
    MainLayout->addWidget(HostLabel, 0, 0);
    MainLayout->addWidget(this->AddressLine, 0, 1);
    MainLayout->addWidget(PortLabel, 1, 0);
    MainLayout->addWidget(this->PortLine, 1, 1);
    MainLayout->addLayout(ButtonLayout, 2, 0, 1, 2);
    MainLayout->addWidget(this->OutputText, 3, 0, 1, 2);
    MainLayout->addWidget(this->InputText, 4, 0, 1, 2);

    this->ClientSocket = new QTcpSocket(this);

    connect(this->ConnectBtn, SIGNAL(clicked(bool)), this, SLOT(ConnectServer()));
    connect(this->ClientSocket, SIGNAL(readyRead()), this, SLOT(ReadData()));
}

ClientWidget::~ClientWidget()
{

}

void ClientWidget::ConnectServer(){
    //this->ClientSocket->abort();
    this->OutputText->append("Start to Connect to Server");
    this->ClientSocket->connectToHost(this->AddressLine->text(),
                                      this->PortLine->text().toInt());
}

void ClientWidget::ReadData(){
    QString In(this->ClientSocket->readAll());

    this->OutputText->append(In);

    this->ClientSocket->write("Hello World");
}
