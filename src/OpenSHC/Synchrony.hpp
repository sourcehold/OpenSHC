/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Synchrony.hpp'
*/

#pragma once

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "WinDef.h"
#include "crtdefs.h"
#include "ddraw.h"
#include "dplay.h"
#include "winnt.h"
namespace OpenSHC {
namespace Synchrony {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    void __stdcall InitSkirmishLobbyData();

    void __cdecl ResetAiVariationArrayValue(int playerID);

    void __cdecl PutPlayerIntoRandomSlot(int param_1);

    void __stdcall SetAIPlayerNickNames();

    int __cdecl GetPlayerPosition(int playerID);

    HRESULT __stdcall EnumDisplayModesCallback(DDSURFACEDESC* displayDesc, LPVOID userParam);

    BOOL __stdcall EnumConnectionsCallback(
        LPCGUID lpguidSP, LPVOID lpConnection, DWORD dwConnectionSize, DPNAME* lpName, DWORD dwFlags, LPVOID lpContext);

    bool __stdcall EnumSessionsCallback_addSession_async(
        DPSESSIONDESC2* lpThisSD, LPDWORD lpdwTimeOut, DWORD dwFlags, LPVOID lpContext);

    BOOLEnum __stdcall DirectPlayModemRelated_MemoryAllocationCallback(int* param_1, undefined4 param_2, char* param_3);

    void __cdecl MemCopyFromParameter(char* dest, size_t size, undefined4 playerID);

    void __stdcall ProgressBarRelated();

    void __stdcall syncPlayerGroupArrays();

    void __cdecl LoadSkirmishCampaignData(int missionID);

} // namespace Synchrony
} // namespace OpenSHC
