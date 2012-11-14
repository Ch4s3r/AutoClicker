#ifndef SENDTHREAD_H
#define SENDTHREAD_H

#include <QThread>
#include <windows.h>
#include <tlhelp32.h>
#include <QtGui>
#include <stdlib.h>

class SendThread : public QThread
{
    Q_OBJECT

    int time;
    short key;
    HWND hWnd;
    DWORD myPostMessage;
public:
    explicit SendThread(QString pname, QString key, QString time, QObject *parent = 0);
    
protected:
    void run();

signals:
    
public slots:
    
};
#endif
