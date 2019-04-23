#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QLCDNumber>
#include <QSize>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QSpacerItem>
#include <QTime>
#include <QTimer>
#include <QDebug>
#include <QString>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QLCDNumber  *TimerShow;
    QPushButton *StartButton;
    QPushButton *StopButton;
    QPushButton *PauseButton;
    QPushButton *CheckButton;
    QTextEdit   *CheckEdit;

    QTime       CurrentTime;
    QTimer      *Timer;

    QString     ShowTimerStr;

public slots:
    void StartButtonHandler();
    void StopButtonHandler();
    void PauseButtonHandler();
    void CheckButtonHandler();
    void FreshLcdShow();
};

#endif // MAINWINDOW_H
