#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QIcon>
#include <QStringList>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:

    void on_ConvertButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
    QIcon ThisIcon;
    QStringList OldList;
};

#endif // WIDGET_H
