#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <windows.h>
#include <TlHelp32.h>
#include <stdio.h>
#include <stdlib.h>
#include "sendthread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
    void GetDebugPrivilege();
    SendThread *mSendThread;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_btnStart_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
