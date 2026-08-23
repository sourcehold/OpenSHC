/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Global.func.hpp'
*/

#pragma once

#include "OpenSHC/Global.hpp"
#include "OpenSHC/Rendering/Enums/DirectDrawStatus.hpp"

#include "WinDef.h"
#include "winnt.h"
namespace OpenSHC {
namespace Global_Func {

    using OpenSHC::Rendering::Enums::DirectDrawStatus;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(wchar_t* destination, wchar_t* format, va_list args), false,
        Address::SHC_3BB0A8C1_0x0045D060, &OpenSHC::Global::PrintToDestination)
    PrintToDestination;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00469F10, &OpenSHC::Global::DoNothing)
    DoNothing;

    MACRO_FUNCTION_RESOLVER(char*(__cdecl*)(char* mapName, int* hardcodedMapDescriptionGroupNum), false,
        Address::SHC_3BB0A8C1_0x0046D390, &OpenSHC::Global::GetStringBasedOnHardcodedMaps)
    GetStringBasedOnHardcodedMaps;

    MACRO_FUNCTION_RESOLVER(DirectDrawStatus(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x0046F4F0,
        &OpenSHC::Global::DetectDXVersionByLoadingDDRAW)
    DetectDXVersionByLoadingDDRAW;

    MACRO_FUNCTION_RESOLVER(byte(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x0046F570, &OpenSHC::Global::TestOSVersion)
    TestOSVersion;

    MACRO_FUNCTION_RESOLVER(LRESULT(__stdcall*)(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam), false,
        Address::SHC_3BB0A8C1_0x004B2AE0, &OpenSHC::Global::WindowMsgProcessingFunc)
    WindowMsgProcessingFunc;

    MACRO_FUNCTION_RESOLVER(
        int(__stdcall*)(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd), false,
        Address::SHC_3BB0A8C1_0x0057BE10, &OpenSHC::Global::WinMain)
    WinMain;

} // namespace Global_Func
} // namespace OpenSHC
