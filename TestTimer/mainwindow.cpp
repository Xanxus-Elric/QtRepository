#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    QSize MainSize(400, 300);

    this->resize(MainSize);
    this->setMaximumSize(MainSize);
    this->setMinimumSize(MainSize);

    QLabel *TimerLabel  = new QLabel("TIMER: ", this);
    QSpacerItem *Space  = new QSpacerItem(0, 0);

    this->TimerShow     = new QLCDNumber(12, this);
    this->StartButton   = new QPushButton("开始", this);
    this->StopButton    = new QPushButton("停止", this);
    this->PauseButton   = new QPushButton("暂停", this);
    this->CheckButton   = new QPushButton("打表", this);
    this->ShowTimerStr  = "00:00:00:000";


    QHBoxLayout *ButtonLayout = new QHBoxLayout;
    ButtonLayout->addWidget(this->StartButton);
    ButtonLayout->addWidget(this->StopButton);
    ButtonLayout->addWidget(this->PauseButton);
    ButtonLayout->addWidget(this->CheckButton);

    QHBoxLayout *TimerLayout = new QHBoxLayout;
    TimerLayout->addWidget(TimerLabel);
    TimerLayout->addItem(Space);
    TimerLayout->addWidget(this->TimerShow);

    this->CheckEdit = new QTextEdit(this);
    this->CheckEdit->setReadOnly(true);

    QGridLayout *MainLayout = new QGridLayout(this);
    MainLayout->addLayout(TimerLayout, 0, 0);
    MainLayout->addLayout(ButtonLayout, 1, 0);
    MainLayout->addWidget(this->CheckEdit, 2, 0);

    this->TimerShow->display("00.00.000");

    connect(this->StartButton, SIGNAL(clicked(bool)), this, SLOT(StartButtonHandler()));
    connect(this->StopButton, SIGNAL(clicked(bool)), this, SLOT(StopButtonHandler()));
    connect(this->PauseButton, SIGNAL(clicked(bool)), this, SLOT(PauseButtonHandler()));
    connect(this->CheckButton, SIGNAL(clicked(bool)), this, SLOT(CheckButtonHandler()));

    this->Timer = new QTimer(this);
    connect(this->Timer, SIGNAL(timeout()), this, SLOT(FreshLcdShow()));

    this->StopButton->setEnabled(false);
    this->PauseButton->setEnabled(false);
    this->CheckButton->setEnabled(false);
    this->TimerShow->setSegmentStyle(QLCDNumber::Flat);
}

void MainWindow::StartButtonHandler(){
    //Get the Current System's time;
    this->CurrentTime = QTime::currentTime();

    //Begin the Timer;
    this->Timer->start(1);
}

void MainWindow::FreshLcdShow(){
    int mSeconds = this->CurrentTime.msecsTo(QTime::currentTime());

    //Get how many mSecondes from User click the Start button to now
    QTime ShowTime;

    ShowTime = ShowTime.fromString(this->ShowTimerStr, "hh:mm:ss:zzz");

    //for if the timer start, this function will be called each 1 mseconds;
    ShowTime = ShowTime.addMSecs(1);

    this->ShowTimerStr = ShowTime.toString("hh:mm:ss:zzz");

    //convert the Time to the string, and show it on the LCDNumber
    this->TimerShow->display(this->ShowTimerStr);

    //Let Disable the StartButton
    //and Enable the other button
    this->StartButton->setEnabled(false);
    this->StopButton->setEnabled(true);
    this->PauseButton->setEnabled(true);
    this->CheckButton->setEnabled(true);
}

void MainWindow::StopButtonHandler(){
    if (this->StopButton->text() == "停止"){
        this->Timer->stop();
        this->StopButton->setText("清空");
        this->StartButton->setEnabled(false);
        this->StopButton->setEnabled(true);
        this->PauseButton->setEnabled(false);
        this->CheckButton->setEnabled(false);
    }
    else{
        this->ShowTimerStr = "00:00:00:000";
        this->TimerShow->display(this->ShowTimerStr);
        this->CheckEdit->setText("");
        this->StopButton->setText("停止");
        this->StartButton->setEnabled(true);
        this->StopButton->setEnabled(false);
        this->PauseButton->setEnabled(false);
        this->CheckButton->setEnabled(false);
    }
}

void MainWindow::PauseButtonHandler(){
    if(this->PauseButton->text() == "暂停"){
        this->Timer->stop();

        this->PauseButton->setText("继续");

        this->StartButton->setEnabled(false);
        this->StopButton->setEnabled(false);
        this->PauseButton->setEnabled(true);
        this->CheckButton->setEnabled(false);

        qDebug() << this->ShowTimerStr;
    }
    else{
        this->Timer->start(1);

        this->PauseButton->setText("暂停");

        this->StartButton->setEnabled(false);
        this->StopButton->setEnabled(true);
        this->PauseButton->setEnabled(true);
        this->CheckButton->setEnabled(true);
    }
}

void MainWindow::CheckButtonHandler(){
    //when user press the Check Button
    //show the ShowTimerStr on the textedit

    this->CheckEdit->append(this->ShowTimerStr);
}

MainWindow::~MainWindow()
{

}
