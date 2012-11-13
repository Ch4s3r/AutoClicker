#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnStart_clicked()
{
    HWND hWnd;
    PROCESSENTRY32 pe32;
    HANDLE pSnap;

    pe32.dwSize = sizeof( PROCESSENTRY32 );
    pSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (pSnap == INVALID_HANDLE_VALUE)
       return;


    char a[3] = {'a','b','c'};
    char *b = &a[0];
    qDebug() << b[0];


    while(Process32Next(pSnap, &pe32))
    {
        wchar_t  *s = new wchar_t[ui->txtWName->text().length()];
        ui->txtWName->text().toWCharArray(s);

        for(int i = 0; i < ui->txtWName->text().length();i++)
            qDebug() << (char)s[i];

        if(wcscmp(pe32.szExeFile, s)==0){
           GetWindowThreadProcessId(hWnd,&pe32.th32ProcessID);
           qDebug() << "ID: " << pe32.th32ProcessID;
           break;
       }
    }
    CloseHandle(pSnap);

    if (!hWnd){
        QMessageBox::warning(this,"Error", "Window '" + ui->txtWName->text() +"' could not be found!");
        return;
    }

    while (1){
        short a = VkKeyScanW(ui->txtKey->text().at(0).toAscii());
        qDebug() << a;
        PostMessageW(hWnd, WM_KEYDOWN, VkKeyScan(ui->txtKey->text().at(0).toLatin1()), 0);
        Sleep(100);
        PostMessage(hWnd, WM_KEYUP, VkKeyScan(ui->txtKey->text().at(0).toLatin1()), 0); //
        Sleep(ui->txtTime->text().toInt());
    }
}
