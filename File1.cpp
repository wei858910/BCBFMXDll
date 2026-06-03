#include <fmx.h>
#include <windows.h>
#include "Unit1.h"

#pragma hdrstop
#pragma argsused

void WINAPI Run()
{
    Application->Initialize();
    Application->CreateForm(__classid(TForm1), &Form1);
    Application->Run();

    FreeLibraryAndExitThread(HInstance, 0);
}

DWORD WINAPI DllCallback(UIntPtr dwReason)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(HInstance);
        DWORD tid{};
        CreateThread(nullptr, 0, LPTHREAD_START_ROUTINE(Run), nullptr, 0, nullptr);
    }

    return 0;
}

extern "C" int _libmain(unsigned long reason)
{
    DllCallback(reason);
    return 1;
}
