//---------------------------------------------------------------------------

#pragma hdrstop

#include "Help.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

void OpenAndInitConsole()
{
    if(AllocConsole())
    {
        FILE* fConsole{};
        freopen_s(&fConsole, "CONOUT$", "w+t", stdout);

        // 设置控制台标题
        SetConsoleTitle(TEXT("调试输出"));

        // 设置控制台颜色
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    }
}
