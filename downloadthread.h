#ifndef DOWNLOADTHREAD_H
#define DOWNLOADTHREAD_H

#include <QThread>

class DownloadThread : public QThread
{
    Q_OBJECT
public:
    explicit DownloadThread(QObject *parent = nullptr);
    void run();
    bool Stop = false;

signals:
    void AddPercent(int);

public slots:

};

#endif // DOWNLOADTHREAD_H
