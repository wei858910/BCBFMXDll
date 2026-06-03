//---------------------------------------------------------------------------

#ifndef wowH
#define wowH

extern const uintptr_t TimerID;
extern const uintptr_t ADDR_ROLE_CALL; // 获取角色对象地址call
extern const uintptr_t ArmorOffset[]; // 护甲偏移 [角色对象地址+0xD0]+0*4+00000174

uintptr_t GetRoleAddress();

uintptr_t GetArmorValue();

/*
    HWND hwnd,          // ① 窗口句柄：与SetTimer的第一个参数相同
    UINT uMsg,          // ② 消息值：固定为 WM_TIMER (即 0x0113)
    UINT_PTR idEvent,   // ③ 定时器ID：与SetTimer的第二个参数相同
    DWORD dwTime        // ④ 系统时间：自Windows启动以来经过的毫秒数
*/
VOID CALLBACK MainThreadFunc(HWND Hwnd, UINT Msg, UINT_PTR ID, DWORD Time);


//---------------------------------------------------------------------------
#endif
