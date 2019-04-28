#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMessageBox>

class SearchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SearchDialog(QWidget *parent = 0);
    ~SearchDialog();

    QString GetSearchName();

private:
    QLineEdit   *SearchName;
    QPushButton *ConfirmBtn;

private slots:
    void SearchConfirmHandle();

signals:
    void SearchFinishSignal();

};

#endif // SEARCHDIALOG_H
