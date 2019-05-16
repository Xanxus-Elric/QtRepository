#ifndef SEARCHWIDGET_H
#define SEARCHWIDGET_H

#include <QWidget>
#include <QSqlQuery>
#include <QtSql>
#include <QSqlDatabase>

QT_BEGIN_NAMESPACE
class QLineEdit;
class QPushButton;
class QTextEdit;
QT_END_NAMESPACE

class SearchWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SearchWidget(QWidget *parent = 0);

private:
    QLineEdit   *SearchInput;
    QPushButton *SearchBtn;
    QTextEdit   *ResultText;
    QSqlDatabase DictDb;

signals:

public slots:
    void Search();

};

#endif // SEARCHWIDGET_H
