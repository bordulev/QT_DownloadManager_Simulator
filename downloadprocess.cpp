#include "downloadprocess.h"
#include "ui_downloadprocess.h"

DownloadProcess::DownloadProcess(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DownloadProcess)
{
    ui->setupUi(this);

    mThread = new DownloadThread(this); //This way, when the form closes, the deletes out of memory automatically
    connect(mThread, SIGNAL(AddPercent(int)), this, SLOT(on_AddPercent(int)));
    connect(mThread, SIGNAL(finished()), this, SLOT(on_ThreadFinished()));
}

DownloadProcess::~DownloadProcess()
{
    delete ui;
}

void DownloadProcess::on_stopButton_clicked()
{
    //Switch Off PAUSE, if it is ON
    if (mThread->Pause == true){
        mThread->Pause = false;
        mThread->pauseCond.wakeAll();
    }
    mThread->Stop = true; //Stop generating percents
    mThread->wait(); //Wait until the thread is finished stopping
    //Here is the finished() SIGNAL is emitted by thread
    //We do not close the process here, since it will be done in on_ThreadFinished()

}

void DownloadProcess::on_pauseButton_clicked()
{
    emit pauseThisProcess(downloadNumber);
}


void DownloadProcess::on_resumeButton_clicked()
{
    emit resumeThisProcess(downloadNumber);
}

void DownloadProcess::writeID(int processID){
    QString new_label;
    new_label = QString::number(processID);
    ui->idLabel->setText("ID: " + new_label);
}

void DownloadProcess::on_AddPercent(int Percent){
    ui->progressBar->setValue(Percent);
    ui->percentLabel->setText(QString::number(Percent) + "%");
}

void DownloadProcess::on_ThreadFinished()
{
    emit closeThisProcess(downloadNumber);
    this->close();
}
