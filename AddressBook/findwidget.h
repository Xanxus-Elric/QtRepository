#ifndef FINDEDIT_H
#define FINDEDIT_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>

class FindWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FindWidget(QWidget *parent = 0);

private:
    QLineEdit   *InputName;
    QPushButton *SearchButton;

public slots:

};

#endif // FINDEDIT_H
