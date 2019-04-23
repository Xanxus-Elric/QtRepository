#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->TimerLcd      = new QLCDNumber(this);
    this->TimeEdit      = new QTextEdit(this);
    this->StartButton   = new QPushButton("开始", this);
    this->StopButton    = new QPushButton("停止", this);
    this->PauseButton   = new QPushButton("暂停", this);
    this->GetButton     = new QPushButton("打表", this);

    QHBoxLayout *ButtonLayout = new QHBoxLayout(this);
    ButtonLayout->addWidget(this->StartButton);
    ButtonLayout->addWidget(this->StopButton);
    ButtonLayout->addWidget(this->PauseButton);
    ButtonLayout->addWidget(this->GetButton);

    QGridLayout *TotalLayout = new QGridLayout(this);
    TotalLayout->addWidget(this->TimerLcd, 0, 0);
    TotalLayout->addLayout(ButtonLayout, 1, 0);
    //TotalLayout->addWidget(this->TimeEdit, 2, 0);

    connect(this->StartButton, SIGNAL(clicked(bool)), this, SLOT(StartButtonHandler()));
    connect(this->StopButton, SIGNAL(clicked(bool)), this, SLOT(StopButtonHandler()));
    connect(this->PauseButton, SIGNAL(clicked(bool)), this, SLOT(PauseButtonHandler()));
    connect(this->GetButton, SIGNAL(clicked(bool)), this, SLOT(GetButtonHandler()));
}

void Widget::StartButtonHandler(){
    this->CurrentTime = QTime::currentTime();
    qDebug() << "the Current Time is " << this->CurrentTime.toString("hh:mm:ss:zzz");
}

void Widget::StopButtonHandler(){

}

void Widget::PauseButtonHandler(){

}

void Widget::GetButtonHandler(){

}

Widget::~Widget()
{
    delete ui;
}
