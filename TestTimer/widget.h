#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLCDNumber>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTime>
#include <QTimer>
#include <QDebug>
#include <QGridLayout>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;

    QLCDNumber  *TimerLcd;
    QTextEdit   *TimeEdit;
    QPushButton *StartButton;
    QPushButton *StopButton;
    QPushButton *PauseButton;
    QPushButton *GetButton;

    QTime       CurrentTime;
    QTimer      *Timer;

public slots:
    void StartButtonHandler();
    void StopButtonHandler();
    void PauseButtonHandler();
    void GetButtonHandler();

};

#endif // WIDGET_H
