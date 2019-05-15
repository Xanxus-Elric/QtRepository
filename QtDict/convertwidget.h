#ifndef CONVERTWIDGET_H
#define CONVERTWIDGET_H

#include <QWidget>
#include <QString>
#include "dictwidget.h"

QT_BEGIN_NAMESPACE
class QProgressBar;
class QLabel;
class QPushButton;
class QThread;
class QFile;
QT_END_NAMESPACE

class ReadOpt : public QObject
{
    Q_OBJECT

private:
    QFile   *DictFile;
    int     FileLines;

public:
    bool FileExist;
    ReadOpt(const QString FileName);

private slots:
    void GetFileLines();

signals:
    void ReadFinish(int FileLines);
};

class ConvertOpt : public QObject
{
    Q_OBJECT

private slots:
    void ConvertDb();

signals:
    void SendCurrentLines(int Lines);
    void ConvertFinish();
};

class ConvertWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ConvertWidget(QWidget *parent = 0);

private:
    QLabel          *PromptLabel;
    QProgressBar    *ConvertProgress;
    QPushButton     *CancelButton;
    ReadOpt         *ReadFile;
    QThread         *ReadThread;
    ConvertOpt      *Convert;
    QThread         *ConvertThread;
    int             CurrentLines;
    DictWidget      *Dict;

signals:

public slots:
    void GetReadResult(int FileLines);
};

#endif // CONVERTWIDGET_H
