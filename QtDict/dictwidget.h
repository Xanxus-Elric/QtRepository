#ifndef DICTWIDGET_H
#define DICTWIDGET_H

#include <QWidget>
#include <QtSql>

QT_BEGIN_NAMESPACE
class QLineEdit;
class QPushButton;
class QTextEdit;
QT_END_NAMESPACE

class DictWidget : public QWidget
{
    Q_OBJECT

public:
    DictWidget(QWidget *parent = 0);
    ~DictWidget();

private:
    QLineEdit       *SearchWord;
    QPushButton     *SearchBtn;
    QTextEdit       *SearchResult;
    QSqlDatabase    DictDb;

private slots:
    void Search();
};

#endif // DICTWIDGET_H
