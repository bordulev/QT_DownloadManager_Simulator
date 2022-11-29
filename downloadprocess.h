#ifndef DOWNLOADPROCESS_H
#define DOWNLOADPROCESS_H

#include "downloadthread.h"
#include <QWidget>

namespace Ui {
class DownloadProcess;
}

class DownloadProcess : public QWidget
{
    Q_OBJECT

public:
    explicit DownloadProcess(QWidget *parent = nullptr);
    ~DownloadProcess();
    int downloadNumber;
    DownloadThread *mThread;

    void writeID(int processID);


private:
    Ui::DownloadProcess *ui;

signals:
    void closeThisProcess(int);
    void pauseThisProcess(int);
    void resumeThisProcess(int);

private slots:
    void on_stopButton_clicked();
    void on_pauseButton_clicked();
    void on_resumeButton_clicked();
    void on_AddPercent(int);
    void on_ThreadFinished();
};

#endif // DOWNLOADPROCESS_H
