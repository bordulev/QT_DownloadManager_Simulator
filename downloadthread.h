#ifndef DOWNLOADTHREAD_H
#define DOWNLOADTHREAD_H

#include <QThread>
#include <QObject>

class DownloadThread : public QThread
{
public:
    explicit DownloadThread(QObject *parent = nullptr);
    void run();
    bool Stop;

signals:
    void AddPercent(int);

public slots:

};

#endif // DOWNLOADTHREAD_H
