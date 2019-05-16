#ifndef MAINDICTWIDGET_H
#define MAINDICTWIDGET_H

#include <QWidget>
#include "searchwidget.h"

QT_BEGIN_NAMESPACE
class QProgressBar;
class QPushButton;
class QLabel;
class QThread;
QT_END_NAMESPACE

class ConvertOpt : public QObject
{
    Q_OBJECT

signals:
    void ReportLines(int Lines);
    void CloseThread();

public slots:
    void ConvertDb();
};

class PrepareOpt : public QObject
{
    Q_OBJECT
private:
    int TotalLines;

signals:
    void SendTotalLines(int TotalLines);

public slots:
    void PrepareRead();
};

class MainDictWidget : public QWidget
{
    Q_OBJECT

public:
    MainDictWidget(QWidget *parent = 0);
    ~MainDictWidget();

private:
    QProgressBar    *ConvertBar;
    QPushButton     *CancelBtn;
    QLabel          *PromptLabel;
    SearchWidget    *SearchMain;

    ConvertOpt      *convert;
    QThread         *convertThread;

    PrepareOpt      *prepare;
    QThread         *prepareThread;

public slots:
    void StartConvertThread(int TotalLines);
    void ShowSearchMainAfterConvert();

signals:
};

#endif // MAINDICTWIDGET_H
