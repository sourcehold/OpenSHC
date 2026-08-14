/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Global.hpp'
*/

#pragma once

#include "OpenSHC/Rendering/Enums/DirectDrawStatus.hpp"

#include "WinDef.h"
#include "winnt.h"
namespace OpenSHC {
namespace Global {

    using OpenSHC::Rendering::Enums::DirectDrawStatus;

    void __cdecl PrintToDestination(wchar_t* destination, wchar_t* format, ...);

    void __stdcall DoNothing();

    char* __cdecl GetStringBasedOnHardcodedMaps(char* mapName, int* hardcodedMapDescriptionGroupNum);

    DirectDrawStatus __stdcall DetectDXVersionByLoadingDDRAW();

    byte __stdcall TestOSVersion();

    LRESULT __stdcall WindowMsgProcessingFunc(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam);

    int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);

} // namespace Global
} // namespace OpenSHC
