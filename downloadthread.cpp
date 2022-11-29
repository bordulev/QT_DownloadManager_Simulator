#include "downloadthread.h"

DownloadThread::DownloadThread(QObject *parent)
    : QThread{parent}
{

}

void DownloadThread::run()
{
    for (int i = 0; i <= 100; i++){

        QMutex mutex; //To avoid any embarassing crashes
        mutex.lock();
        if (this->Stop) break;
        if (this->Pause) pauseCond.wait(&mutex);
        mutex.unlock();

        emit AddPercent(i);

        this->msleep(100); //the speed of downloading (percent in how much time)
    }
}
