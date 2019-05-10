#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class PaintClock : public QWidget
{
    Q_OBJECT

public:
    PaintClock(QWidget *parent = 0);
    ~PaintClock();

private:
    void paintEvent(QPaintEvent *event);
};

#endif // WIDGET_H
