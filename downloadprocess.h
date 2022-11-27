#ifndef DOWNLOADPROCESS_H
#define DOWNLOADPROCESS_H

#include <QWidget>
#include <QThread>

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

    void writeID();
    void fillDownloadBar();

private:
    Ui::DownloadProcess *ui;

signals:
    void closeThisProcess(int);

private slots:
    void on_stopButton_clicked();
    void on_pauseButton_clicked();
    void on_resumeButton_clicked();
};

#endif // DOWNLOADPROCESS_H
