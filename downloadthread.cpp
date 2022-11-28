#include "downloadthread.h"
//#include <QtCore> //to use mutex

DownloadThread::DownloadThread(QObject *parent)
    : QThread{parent}
{

}

void DownloadThread::run()
{
    for (int i = 0; i < 100; i++){

        //To avoid any embarassing crashes
        //QMutex mutex;
        //mutex.lock();
        if (this->Stop) break;
        //mutex.unlock();

        emit AddPercent(i);

        //this->msleep(100); //the speed of downloading (percent in how much time)
    }

}
