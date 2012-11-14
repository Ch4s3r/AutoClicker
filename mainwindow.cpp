#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    GetDebugPrivilege();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::GetDebugPrivilege()
{
    TOKEN_PRIVILEGES privilege;
    LUID Luid;
    HANDLE handle1;
    HANDLE handle2;

    handle1 = OpenProcess(PROCESS_ALL_ACCESS, FALSE, GetCurrentProcessId());
    OpenProcessToken(handle1, TOKEN_ALL_ACCESS, &handle2);
    LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &Luid);
    privilege.PrivilegeCount = 1;
    privilege.Privileges[0].Luid = Luid;
    privilege.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    AdjustTokenPrivileges(handle2, FALSE, &privilege, sizeof(privilege), NULL, NULL);
    CloseHandle(handle2);
    CloseHandle(handle1);
}


void MainWindow::on_btnStart_clicked()
{
    if(ui->btnStart->text().contains("Start")){
        ui->btnStart->setText("Stop");
        mSendThread = new SendThread(ui->txtWName->text(),ui->txtKey->text(),ui->txtTime->text());
        mSendThread->start();
    } else{
        ui->btnStart->setText("Start");
        mSendThread->terminate();
        delete mSendThread;
    }
}
