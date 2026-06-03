//---------------------------------------------------------------------------

#pragma hdrstop

#include "Help.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

void OpenAndInitConsole()
{
    if (AllocConsole())
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

bool IsAddressValid(uintptr_t address)
{
    // 快速过滤空指针和低地址
    if (address == 0 || address < 0x10000)
        return false;

    // 平台地址范围检查
#ifdef _WIN64
    // 64位：用户态有效范围为 0x0000 到 0x7FFF FFFF FFFF
    if (address > 0x00007FFFFFFFFFFFULL)
        return false;
#else
    // 32位：用户态有效范围为 0x0000 到 0x7FFF FFFF
    if (address > 0x7FFFFFFF)
        return false;
#endif

    // 内存属性验证
    MEMORY_BASIC_INFORMATION mbi;
    if (VirtualQuery((LPCVOID)address, &mbi, sizeof(mbi)) == 0)
        return false;

    // 必须是已提交且可读的内存
    return (mbi.State == MEM_COMMIT) && ((mbi.Protect & (PAGE_READONLY | PAGE_READWRITE | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE)) != 0);
}
