#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    downloadsNumberTotal = 0;
    this->setFixedSize(this->size());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_startNewButton_clicked()
{
    processID ++;
    addNewDownload();
}

void MainWindow::addNewDownload()
{
    DownloadProcess *newProcess = new DownloadProcess(this);
    ui->downloadsLayout->insertWidget(downloadsNumberTotal, newProcess);
    connect(newProcess, SIGNAL(closeThisProcess(int)), this, SLOT(closeProcess(int)));
    connect(newProcess, SIGNAL(pauseThisProcess(int)), this, SLOT(pauseProcess(int)));
    connect(newProcess, SIGNAL(resumeThisProcess(int)), this, SLOT(resumeProcess(int)));
    newProcess->setAttribute(Qt::WA_DeleteOnClose, true); // Delete object, if it is closed
    newProcess->downloadNumber = downloadsNumberTotal;
    newProcess->writeID(processID);
    //Start gaining the pecents
    newProcess->mThread->start();
    allDownloadsPtr.append(newProcess);
    downloadsNumberTotal++;
    }

void MainWindow::closeProcess(int processNumber)
{
    allDownloadsPtr[processNumber]->close( );
    //Now we should decrease the process numbers that stands after deleted one
    for (int i = processNumber+1; i < allDownloadsPtr.length(); i++){
        allDownloadsPtr[i]->downloadNumber--;
    }
    downloadsNumberTotal--;
    allDownloadsPtr.remove(processNumber);

}

void MainWindow::pauseProcess(int processNumber)
{
    allDownloadsPtr[processNumber]->mThread->Pause = true;
}

void MainWindow::resumeProcess(int processNumber)
{
    allDownloadsPtr[processNumber]->mThread->Pause = false;
    allDownloadsPtr[processNumber]->mThread->pauseCond.wakeAll(); //
}

void MainWindow::on_stopAllButton_clicked()
{
    processID = 0;

    for (int i = 0; i < allDownloadsPtr.length(); i++){
        //Switch Off PAUSE, if it is ON
        if (allDownloadsPtr[i]->mThread->Pause == true){
            allDownloadsPtr[i]->mThread->Pause = false;
            allDownloadsPtr[i]->mThread->pauseCond.wakeAll();
        }
        allDownloadsPtr[i]->mThread->Stop = true; //Stop generating percents
        allDownloadsPtr[i]->mThread->wait(); //Wait until the thread is finished stopping
    }
}


void MainWindow::on_pauseAllButton_clicked()
{
    for (int i = 0; i < allDownloadsPtr.length(); i++){
        emit allDownloadsPtr[i]->pauseThisProcess(allDownloadsPtr[i]->downloadNumber);
    }
}


void MainWindow::on_resumeAllButton_clicked()
{
    for (int i = 0; i < allDownloadsPtr.length(); i++){
        emit allDownloadsPtr[i]->resumeThisProcess(allDownloadsPtr[i]->downloadNumber);
    }
}

