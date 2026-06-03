//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Unit1.h"
#include "Help.h"
#include "wow.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TForm1* Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BtnGetArmorClick(TObject* Sender)
{
    HWND GameHwnd = FindWindow(TEXT("GxWindowClassD3d"), TEXT("魔兽世界")); // 获取游戏窗口句柄

    SetTimer(GameHwnd, TimerID, 1, MainThreadFunc);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BtnGetGameBaseAddressClick(TObject *Sender)
{
    GetGameBase();
}
//---------------------------------------------------------------------------

