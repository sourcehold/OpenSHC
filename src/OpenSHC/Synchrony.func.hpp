/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Synchrony.func.hpp'
*/

#pragma once

#include "OpenSHC/Synchrony.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "WinDef.h"
#include "crtdefs.h"
#include "ddraw.h"
#include "dplay.h"
#include "winnt.h"
namespace OpenSHC {
namespace Synchrony_Func {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004274F0, &OpenSHC::Synchrony::InitSkirmishLobbyData)
    InitSkirmishLobbyData;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int playerID), false, Address::SHC_3BB0A8C1_0x00428050,
        &OpenSHC::Synchrony::ResetAiVariationArrayValue)
    ResetAiVariationArrayValue;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00428480,
        &OpenSHC::Synchrony::PutPlayerIntoRandomSlot)
    PutPlayerIntoRandomSlot;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0042A8E0, &OpenSHC::Synchrony::SetAIPlayerNickNames)
    SetAIPlayerNickNames;

    MACRO_FUNCTION_RESOLVER(
        int(__cdecl*)(int playerID), false, Address::SHC_3BB0A8C1_0x0042AC60, &OpenSHC::Synchrony::GetPlayerPosition)
    GetPlayerPosition;

    MACRO_FUNCTION_RESOLVER(HRESULT(__stdcall*)(DDSURFACEDESC* displayDesc, LPVOID userParam), false,
        Address::SHC_3BB0A8C1_0x00467BC0, &OpenSHC::Synchrony::EnumDisplayModesCallback)
    EnumDisplayModesCallback;

    MACRO_FUNCTION_RESOLVER(BOOL(__stdcall*)(LPCGUID lpguidSP, LPVOID lpConnection, DWORD dwConnectionSize,
                                DPNAME* lpName, DWORD dwFlags, LPVOID lpContext),
        false, Address::SHC_3BB0A8C1_0x0047D5B0, &OpenSHC::Synchrony::EnumConnectionsCallback)
    EnumConnectionsCallback;

    MACRO_FUNCTION_RESOLVER(
        bool(__stdcall*)(DPSESSIONDESC2* lpThisSD, LPDWORD lpdwTimeOut, DWORD dwFlags, LPVOID lpContext), false,
        Address::SHC_3BB0A8C1_0x0047DF40, &OpenSHC::Synchrony::EnumSessionsCallback_addSession_async)
    EnumSessionsCallback_addSession_async;

    MACRO_FUNCTION_RESOLVER(BOOLEnum(__stdcall*)(int* param_1, undefined4 param_2, char* param_3), false,
        Address::SHC_3BB0A8C1_0x0047E160, &OpenSHC::Synchrony::DirectPlayModemRelated_MemoryAllocationCallback)
    DirectPlayModemRelated_MemoryAllocationCallback;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(char* dest, size_t size, undefined4 playerID), false,
        Address::SHC_3BB0A8C1_0x00488480, &OpenSHC::Synchrony::MemCopyFromParameter)
    MemCopyFromParameter;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00495840, &OpenSHC::Synchrony::ProgressBarRelated)
    ProgressBarRelated;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004AEA10, &OpenSHC::Synchrony::syncPlayerGroupArrays)
    syncPlayerGroupArrays;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int missionID), false, Address::SHC_3BB0A8C1_0x004C6B20,
        &OpenSHC::Synchrony::LoadSkirmishCampaignData)
    LoadSkirmishCampaignData;

} // namespace Synchrony_Func
} // namespace OpenSHC
