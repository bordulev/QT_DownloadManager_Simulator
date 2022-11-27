#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    downloadsNumberTotal = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_startNewButton_clicked()
{
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
    newProcess->setAttribute(Qt::WA_DeleteOnClose, true); // Delete object, if it is closed
    newProcess->downloadNumber = downloadsNumberTotal; //Download ID
    newProcess->writeID();
    newProcess->fillDownloadBar();
    allDownloadsPtr.append(newProcess);
    downloadsNumberTotal++;
    }

void MainWindow::closeProcess(int processNumber){
    allDownloadsPtr[processNumber]->close( );
    //Now we should decrease the process numbers that stands after deleted one
    for (int i = processNumber+1; i < allDownloadsPtr.length(); i++){
        allDownloadsPtr[i]->downloadNumber--; //Decrease the process number on 1 in every process after deleted;
    }
    downloadsNumberTotal--;
    allDownloadsPtr.remove(processNumber);

}

void MainWindow::on_stopAllButton_clicked()
{
    for (int i = 0; i < allDownloadsPtr.length(); ){ //We do not increment the i, since we delete these processes one by one
        emit allDownloadsPtr[i]->closeThisProcess(allDownloadsPtr[i]->downloadNumber); //For every process we call closeThisProcess SIGNAL
    }
}

