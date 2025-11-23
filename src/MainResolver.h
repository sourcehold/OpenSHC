#pragma once

#include "FunctionResolver.h"

#include "MainDeclaration.h"

namespace Main_Func {

MACRO_FUNCTION_RESOLVER(int(__stdcall*)(HINSTANCE, HINSTANCE, PSTR, int), false, 0x0057be10, &Main::WinMain)
WinMain;

}
