#include "downloadprocess.h"
#include "ui_downloadprocess.h"

DownloadProcess::DownloadProcess(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DownloadProcess)
{
    ui->setupUi(this);

    mThread = new DownloadThread(this); //This way, when the forms closes, the deletes out of memory automatically
    connect(mThread, SIGNAL(AddPercent(int)), this, SLOT(on_AddPercent(int)));
}

DownloadProcess::~DownloadProcess()
{
    delete ui;
}

void DownloadProcess::on_stopButton_clicked()
{
    mThread->Stop = true; //Stop generating percents
    emit closeThisProcess(downloadNumber); //emit EMITS the SIGNAL that we want
    this->close();
}

void DownloadProcess::on_pauseButton_clicked()
{

}


void DownloadProcess::on_resumeButton_clicked()
{

}

void DownloadProcess::writeID(){
    QString new_label;
    new_label = QString::number(this->downloadNumber);
    ui->idLabel->setText("ID: " + new_label);
}

void DownloadProcess::on_AddPercent(int Percent){
    ui->progressBar->setValue(Percent);

}
