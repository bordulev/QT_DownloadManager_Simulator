#include "downloadprocess.h"
#include "ui_downloadprocess.h"

DownloadProcess::DownloadProcess(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DownloadProcess)
{
    ui->setupUi(this);
}

DownloadProcess::~DownloadProcess()
{
    delete ui;
}

void DownloadProcess::on_stopButton_clicked()
{
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

void DownloadProcess::fillDownloadBar()
{
    for (int percentVal = 0; percentVal < 50; percentVal++){
        ui->progressBar->setValue(percentVal);
    }
}

