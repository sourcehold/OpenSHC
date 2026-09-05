/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/DisplayElements.func.hpp'
*/

#pragma once

#include "OpenSHC/UI/DisplayElement.hpp"
#include "OpenSHC/UI/DisplayElements.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "WinDef.h"
namespace OpenSHC {
namespace UI {
    namespace DisplayElements_Func {

        using OpenSHC::UI::DisplayElement;
        using OpenSHC::UI::Enums::DisplayElementID;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int posX, int posY, DWORD tileType), false,
            Address::SHC_3BB0A8C1_0x00433BC0,
            &OpenSHC::UI::DisplayElements::RenderConnectAndPathLinkageInfoTextDisplayElement)
        RenderConnectAndPathLinkageInfoTextDisplayElement;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int posX, int posY, DWORD elementState), false,
            Address::SHC_3BB0A8C1_0x00433D00, &OpenSHC::UI::DisplayElements::RenderBottomLeftDateDisplayElement)
        RenderBottomLeftDateDisplayElement;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int posX, int posY, DWORD elementState), false,
            Address::SHC_3BB0A8C1_0x00433DA0, &OpenSHC::UI::DisplayElements::RenderStartingGoodDisplayElement)
        RenderStartingGoodDisplayElement;

        MACRO_FUNCTION_RESOLVER(DisplayElement*(__cdecl*)(int elementID), false, Address::SHC_3BB0A8C1_0x004AF630,
            &OpenSHC::UI::DisplayElements::FindDisplayElementWithID)
        FindDisplayElementWithID;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(DisplayElementID displayElementID, dword elementState), false,
            Address::SHC_3BB0A8C1_0x004AF650,
            &OpenSHC::UI::DisplayElements::CheckDisplayElementByIDAndSetForUnlimitedDisplay)
        CheckDisplayElementByIDAndSetForUnlimitedDisplay;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(DisplayElementID elementId, dword elementState, int displayDuration),
            false, Address::SHC_3BB0A8C1_0x004AF680,
            &OpenSHC::UI::DisplayElements::ActivateGameSpeedAndResourceLackDisplayElementUnk)
        ActivateGameSpeedAndResourceLackDisplayElementUnk;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(DisplayElementID displayElementID, uint toggleValue), false,
            Address::SHC_3BB0A8C1_0x004AF6B0, &OpenSHC::UI::DisplayElements::TogglePlayerPingDisplayElementUnk)
        TogglePlayerPingDisplayElementUnk;

        MACRO_FUNCTION_RESOLVER(BOOLEnum(__cdecl*)(DisplayElementID displayElementID), false,
            Address::SHC_3BB0A8C1_0x004AF6E0, &OpenSHC::UI::DisplayElements::GetIfDisplayElementStateNotZero)
        GetIfDisplayElementStateNotZero;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004AF700,
            &OpenSHC::UI::DisplayElements::RenderDisplayElementsUnk)
        RenderDisplayElementsUnk;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int posX, int posY, DWORD elementState), false,
            Address::SHC_3BB0A8C1_0x004AF800, &OpenSHC::UI::DisplayElements::RenderInGameChatDisplayElement)
        RenderInGameChatDisplayElement;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int posX, int posY, DWORD elementState), false,
            Address::SHC_3BB0A8C1_0x004AF820, &OpenSHC::UI::DisplayElements::RenderResourceMissing1DisplayElement)
        RenderResourceMissing1DisplayElement;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int posX, int posY, DWORD elementState), false,
            Address::SHC_3BB0A8C1_0x004AF840, &OpenSHC::UI::DisplayElements::RenderResourceMissing2DisplayElement)
        RenderResourceMissing2DisplayElement;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int posX, int posY, DWORD elementState), false,
            Address::SHC_3BB0A8C1_0x004AF860, &OpenSHC::UI::DisplayElements::RenderDebugNumbersDisplayElement)
        RenderDebugNumbersDisplayElement;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int posX, int posY, DWORD elementState), false,
            Address::SHC_3BB0A8C1_0x004AFA50, &OpenSHC::UI::DisplayElements::RenderUnknownDisplayElement7)
        RenderUnknownDisplayElement7;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int posX, int posY, DWORD MissionNumPlus1Unk), false,
            Address::SHC_3BB0A8C1_0x004AFA80, &OpenSHC::UI::DisplayElements::RenderSomeMissionNumberUnkDisplayElement9)
        RenderSomeMissionNumberUnkDisplayElement9;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int posX, int posY, DWORD elementState), false,
            Address::SHC_3BB0A8C1_0x004AFB00, &OpenSHC::UI::DisplayElements::RenderNoTreeGrowthTextDisplayElement)
        RenderNoTreeGrowthTextDisplayElement;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int posX, int posY, DWORD elementState), false,
            Address::SHC_3BB0A8C1_0x004AFB30, &OpenSHC::UI::DisplayElements::RenderInGameWinDefeatWindowDisplayElement)
        RenderInGameWinDefeatWindowDisplayElement;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int posX, int posY, DWORD winDefeatState), false,
            Address::SHC_3BB0A8C1_0x004AFDA0, &OpenSHC::UI::DisplayElements::RenderMissionWinDefeatBannerDisplayElement)
        RenderMissionWinDefeatBannerDisplayElement;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int posX, int posY, DWORD elementState), false,
            Address::SHC_3BB0A8C1_0x004AFE10,
            &OpenSHC::UI::DisplayElements::RenderSomeMultiplayerInfoUnkDisplayElement19)
        RenderSomeMultiplayerInfoUnkDisplayElement19;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int posX, int posY, DWORD elementState), false,
            Address::SHC_3BB0A8C1_0x004B0390, &OpenSHC::UI::DisplayElements::RenderPlayerInfoOnHoverDisplayElement)
        RenderPlayerInfoOnHoverDisplayElement;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int posX, int posY, DWORD elementState), false,
            Address::SHC_3BB0A8C1_0x004B07C0, &OpenSHC::UI::DisplayElements::RenderGameSpeedTextDisplayElement)
        RenderGameSpeedTextDisplayElement;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int posX, int posY, DWORD elementState), false,
            Address::SHC_3BB0A8C1_0x004B0820, &OpenSHC::UI::DisplayElements::RenderUnknownDisplayElement25)
        RenderUnknownDisplayElement25;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int posX, int posY, DWORD elementState), false,
            Address::SHC_3BB0A8C1_0x004B0AC0, &OpenSHC::UI::DisplayElements::RenderPeopleLeftToPlaceDisplayElement)
        RenderPeopleLeftToPlaceDisplayElement;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int posX, int posY, DWORD whichBuildingIsMissing), false,
            Address::SHC_3BB0A8C1_0x004B1C30,
            &OpenSHC::UI::DisplayElements::RenderAndPlayKeepAndGranaryPlacementInfoDisplayElement)
        RenderAndPlayKeepAndGranaryPlacementInfoDisplayElement;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int posX, int posY, DWORD elementState), false,
            Address::SHC_3BB0A8C1_0x004B1D30, &OpenSHC::UI::DisplayElements::RenderPlayerPingUnkDisplayElement22)
        RenderPlayerPingUnkDisplayElement22;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int posX, int posY, DWORD elementState), false,
            Address::SHC_3BB0A8C1_0x004B1E60, &OpenSHC::UI::DisplayElements::RenderGamePausedTextDisplayElement)
        RenderGamePausedTextDisplayElement;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int posX, int posY, DWORD elementState), false,
            Address::SHC_3BB0A8C1_0x004B1EB0, &OpenSHC::UI::DisplayElements::RenderTimeUntilVictoryDisplayElement)
        RenderTimeUntilVictoryDisplayElement;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int posX, int posY, DWORD elementState), false,
            Address::SHC_3BB0A8C1_0x004B20B0, &OpenSHC::UI::DisplayElements::RenderNoRushDisplayElementUnk)
        RenderNoRushDisplayElementUnk;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int posX, int posY, DWORD elementState), false,
            Address::SHC_3BB0A8C1_0x004B2280, &OpenSHC::UI::DisplayElements::RenderTimeUntilDefeatDisplayElement)
        RenderTimeUntilDefeatDisplayElement;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int posX, int posY, DWORD elementState), false,
            Address::SHC_3BB0A8C1_0x004B2530,
            &OpenSHC::UI::DisplayElements::RenderSomeMultiplayerInfoUnkDisplayElement28)
        RenderSomeMultiplayerInfoUnkDisplayElement28;

    } // namespace DisplayElements_Func
} // namespace UI
} // namespace OpenSHC
