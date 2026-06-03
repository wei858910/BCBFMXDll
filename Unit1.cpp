//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Unit1.h"
#include "Help.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BtnAllocConsoleClick(TObject *Sender)
{
    OpenAndInitConsole();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BtnFreeConsoleClick(TObject *Sender)
{
    FreeConsole();
}
//---------------------------------------------------------------------------
