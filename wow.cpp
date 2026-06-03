//---------------------------------------------------------------------------

#pragma hdrstop

#include "wow.h"
#include "Help.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

const uintptr_t TimerID{ 10086 };
const uintptr_t ADDR_ROLE_CALL{ 0x0060C1F0 };    // 获取角色对象地址call
const uintptr_t ArmorOffset[] = { 0xD0, 0x174 }; // 护甲偏移 [角色对象地址+0xD0]+0*4+00000174

// 获取角色对象地址
uintptr_t GetRoleAddress()
{
    static uintptr_t RoleAddress{};
    if (0 == RoleAddress)
    {
        // 声明获取角色对象地址函数指针类型
        using TFunc = uintptr_t(*)(const char*);

        TFunc GetRoleAddressCall = reinterpret_cast<TFunc>(ADDR_ROLE_CALL);
        const char* arg1 = "player";
        RoleAddress = GetRoleAddressCall(arg1);
    }

    return RoleAddress;
}

// 获取护甲值
uintptr_t GetArmorValue()
{
    int ArmorValue = GetTargetValue<int>(ArmorOffset, ARRAY_SIZE(ArmorOffset), GetRoleAddress());

    OutputDebugMsg("护甲 = %d 行号 = %d \r\n", ArmorValue, __LINE__);

    return ArmorValue;
}

// 主线程函数  VOID (CALLBACK* TIMERPROC)(HWND, UINT, UINT_PTR, DWORD);
VOID CALLBACK MainThreadFunc(HWND Hwnd, UINT Msg, UINT_PTR ID, DWORD Time)
{
    KillTimer(Hwnd, ID);

    DWORD ThreadID = GetCurrentThreadId();
    OutputDebugMsg("主线程代码 窗口句柄 = %p 线程ID = %lu 行号 = %d \r\n", Hwnd, ThreadID, __LINE__);

    GetArmorValue();
}
