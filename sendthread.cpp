#include "sendthread.h"

SendThread::SendThread(QString pname, QString key, QString time, QObject *parent) :
    QThread(parent)
{
    myPostMessage = (DWORD)GetProcAddress(LoadLibrary(L"user32.dll"),"PostMessageA") + 5;

    this->time = time.toInt();
    PROCESSENTRY32 pe32;
    HANDLE pSnap;

    pe32.dwSize = sizeof( PROCESSENTRY32 );
    pSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (pSnap == INVALID_HANDLE_VALUE)
       return;

    wchar_t  *s = new wchar_t[pname.length()];
    pname.toWCharArray(s);
    for(int i = 0; i < pname.length();i++)
        qDebug() << (char)s[i];

    while(Process32Next(pSnap, &pe32))
    {
        if(wcscmp(pe32.szExeFile, s)==0){
           GetWindowThreadProcessId(hWnd,&pe32.th32ProcessID);
           qDebug() << "ID: " << pe32.th32ProcessID;
           break;
       }
    }
    CloseHandle(pSnap);
    this->key = VkKeyScan(key.at(0).toAscii());
}

__declspec(naked) BOOL WINAPI _PostMessageA(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
//    "addl %1, %0"
//          : "=r"(x)
//          : "m"(y), "0"(x)

    __asm(
    ".intel_syntax noprefix\n\t"
    "push   ebp\n\t"
    "mov    ebp, esp\n\t"
    "jmp    dword ptr ds:[myPostMessage]\n\t"
    ".att_syntax\n"
    );
}

void SendThread::run(){
    if (!hWnd)
        return;
    while (1){
//        qDebug() << "Key: '" << (char)key << "'";
        qApp->processEvents();
//        PostMessageW(hWnd, WM_KEYDOWN, key, 0);
//        Sleep(100);
//        PostMessage(hWnd, WM_KEYUP, key, 0);
//        Sleep(time);
        for(int i = 0; i < 1000; i+=10)
            for(int j = 0; j < 1000; j+=10){
                PostMessage(hWnd, WM_MOUSEMOVE, NULL, MAKELONG(i, j));
                qDebug() << "i: " << i << " | j: " << j;
                PostMessage(hWnd, WM_RBUTTONDOWN, MK_RBUTTON, MAKELONG(i, j));
                Sleep(5);
                PostMessage(hWnd, WM_RBUTTONUP, MK_RBUTTON, MAKELONG(i, j));
            }

        PostMessage(hWnd, WM_RBUTTONDOWN, MK_RBUTTON, MAKELONG(100, 100));
        Sleep(5);
        PostMessage(hWnd, WM_RBUTTONUP, MK_RBUTTON, MAKELONG(100, 100));
        Sleep(time);
    }
}
