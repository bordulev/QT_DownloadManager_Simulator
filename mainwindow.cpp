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
    DownloadProcess *newProcess = new DownloadProcess(this); //Create new object (our download process)
    //ui->downloadsLayout->addWidget(newProcess, downloadsNumberTotal);
    ui->downloadsLayout->insertWidget(downloadsNumberTotal, newProcess); //insert widget between spacer and the top
    connect(newProcess, SIGNAL(closeThisProcess(int)), this, SLOT(closeProcess(int)));  // connects the signal (trigger) and
    //the slot (function, that is triggered). This string just means, that we trigger closeProcess SLOT, defined in this class,
    //when we receive the SIGNAL, defined in the class of NewProcess. So, basically we just explain to the program, that new process
    //should be closed when we push STOP button at this process
    connect(newProcess, SIGNAL(pauseThisProcess(int)), this, SLOT(pauseProcess(int)));
    connect(newProcess, SIGNAL(resumeThisProcess(int)), this, SLOT(resumeProcess(int)));
    newProcess->setAttribute(Qt::WA_DeleteOnClose, true); // Delete object, if it is closed
    newProcess->downloadNumber = downloadsNumberTotal; //Download ID
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
        allDownloadsPtr[i]->downloadNumber--; //Decrease the process number on 1 in every process after deleted;
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

    for (int i = 0; i < allDownloadsPtr.length(); i++){ //We do not increment the i, since we delete these processes one by one
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
        emit allDownloadsPtr[i]->pauseThisProcess(allDownloadsPtr[i]->downloadNumber); //For every process we call pauseThisProcess SIGNAL
    }
}


void MainWindow::on_resumeAllButton_clicked()
{
    for (int i = 0; i < allDownloadsPtr.length(); i++){
        emit allDownloadsPtr[i]->resumeThisProcess(allDownloadsPtr[i]->downloadNumber); //For every process we call pauseThisProcess SIGNAL
    }
}

