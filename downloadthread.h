#ifndef DOWNLOADTHREAD_H
#define DOWNLOADTHREAD_H

#include <QThread>
#include <QtCore> //to use mutex

class DownloadThread : public QThread
{
    Q_OBJECT
public:
    explicit DownloadThread(QObject *parent = nullptr);
    void run();
    bool Stop = false;
    bool Pause = false;
    QWaitCondition pauseCond;

signals:
    void AddPercent(int);

public slots:

};

#endif // DOWNLOADTHREAD_H
