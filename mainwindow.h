#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector> //To save all the downloads data
#include <QThread>
#include "downloadprocess.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int downloadsNumberTotal; //This is needed to place new downloads on its places (rows)
    int processID = 0;
    QVector<DownloadProcess *> allDownloadsPtr;

private slots:  //SLOT is a Function, that is called, when the SIGNAL is appeared. Slot includes instructions what to do,
                //when signal appears. Signals and Slots could be connected by connect() function
    void on_startNewButton_clicked();
    void addNewDownload();

    void on_stopAllButton_clicked();

    void on_pauseAllButton_clicked();

    void on_resumeAllButton_clicked();

public slots: //Public, because they are connected to other classes
    void closeProcess(int);
    void pauseProcess(int);
    void resumeProcess(int);


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
