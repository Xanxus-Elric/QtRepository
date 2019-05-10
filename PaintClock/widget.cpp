#include "Clock.h"
#include <QTime>
#include <QTimer>
#include <QPoint>
#include <QColor>
#include <QPainter>

//set the coordinate of the Hour hand, and Minute hand
//set the color of the both hands
static const QPoint hourPoints[3] = {
    QPoint(5, 0),
    QPoint(-5, 0),
    QPoint(0, -40)
};

static const QPoint minPoints[3] = {
    QPoint(5, 0),
    QPoint(-5, 0),
    QPoint(0, -70)
};

static const QPoint secPoints[3] = {
    QPoint(3, 0),
    QPoint(-3, 0),
    QPoint(0, 100)
};

static const QPoint HourSign[4] = {
    QPoint(-2, 0 + 110),
    QPoint(0, 3 + 110),
    QPoint(2, 0 + 110),
    QPoint(0, -3 + 110)
};

static const QPoint SecSign[4] = {
    QPoint(-1, 2 + 110),
    QPoint(1, 2 + 110),
    QPoint(1, -2 + 110),
    QPoint(-1, -2 + 110)
};

static const QColor hourColor(127, 0, 127);
static const QColor minColor(0, 127, 127);
static const QColor secColor(127, 127, 0);
static const QColor signColor(127, 127, 127);

PaintClock::PaintClock(QWidget *parent)
    : QWidget(parent)
{
    this->setWindowTitle("Paint Clock");
    this->resize(500, 500);

    //Add the Timer to Refresh the Main Widget every second
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000);
}

PaintClock::~PaintClock()
{

}

//overload the Function "PaintEvent"
void PaintClock::paintEvent(QPaintEvent *event){

    QTime time = QTime::currentTime();

    //initialize the Painter on this Widget
    QPainter painter(this);
    //show the graphic more smoothly
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(this->width()/2, this->height()/2);

    int MinSide = qMin(this->width(), this->height());

    painter.scale(MinSide/250, MinSide/250);
    painter.setPen(Qt::NoPen);

    painter.setBrush(hourColor);
    painter.save();
    //calculate the angle of current hour hand
    painter.rotate((time.hour() % 12) * 30 + (time.minute() / 60) * 30);
    painter.drawConvexPolygon(hourPoints, 3);
    painter.restore();

    painter.setBrush(minColor);
    painter.save();
    painter.rotate(time.minute() * 6);
    painter.drawConvexPolygon(minPoints, 3);
    painter.restore();

    painter.setBrush(secColor);
    painter.save();
    painter.rotate(time.second() * 6);
    painter.drawConvexPolygon(secPoints, 3);
    painter.restore();

    for (int i = 0; i < 60; i++){
        painter.setBrush(signColor);
        painter.save();
        painter.rotate(i * 6);

        if (i % 5 == 0){
            //paint the hour sign
            painter.drawConvexPolygon(HourSign, 4);

        }
        else{
            painter.drawConvexPolygon(SecSign, 4);
        }

        painter.restore();
    }
}
