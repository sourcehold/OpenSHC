/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/DisplayElements.hpp'
*/

#pragma once

#include "OpenSHC/UI/DisplayElement.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "WinDef.h"
namespace OpenSHC {
namespace UI {
    namespace DisplayElements {

        using OpenSHC::UI::DisplayElement;
        using OpenSHC::UI::Enums::DisplayElementID;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        void __cdecl RenderConnectAndPathLinkageInfoTextDisplayElement(int posX, int posY, DWORD tileType);

        void __cdecl RenderBottomLeftDateDisplayElement(int posX, int posY, DWORD elementState);

        void __cdecl RenderStartingGoodDisplayElement(int posX, int posY, DWORD elementState);

        DisplayElement* __cdecl FindDisplayElementWithID(int elementID);

        void __cdecl CheckDisplayElementByIDAndSetForUnlimitedDisplay(
            DisplayElementID displayElementID, dword elementState);

        void __cdecl ActivateGameSpeedAndResourceLackDisplayElementUnk(
            DisplayElementID elementId, dword elementState, int displayDuration);

        void __cdecl TogglePlayerPingDisplayElementUnk(DisplayElementID displayElementID, uint toggleValue);

        BOOLEnum __cdecl GetIfDisplayElementStateNotZero(DisplayElementID displayElementID);

        void __cdecl RenderDisplayElementsUnk();

        void __cdecl RenderInGameChatDisplayElement(int posX, int posY, DWORD elementState);

        void __cdecl RenderResourceMissing1DisplayElement(int posX, int posY, DWORD elementState);

        void __cdecl RenderResourceMissing2DisplayElement(int posX, int posY, DWORD elementState);

        void __cdecl RenderDebugNumbersDisplayElement(int posX, int posY, DWORD elementState);

        void __cdecl RenderUnknownDisplayElement7(int posX, int posY, DWORD elementState);

        void __cdecl RenderSomeMissionNumberUnkDisplayElement9(int posX, int posY, DWORD MissionNumPlus1Unk);

        void __cdecl RenderNoTreeGrowthTextDisplayElement(int posX, int posY, DWORD elementState);

        void __cdecl RenderInGameWinDefeatWindowDisplayElement(int posX, int posY, DWORD elementState);

        void __cdecl RenderMissionWinDefeatBannerDisplayElement(int posX, int posY, DWORD winDefeatState);

        void __cdecl RenderSomeMultiplayerInfoUnkDisplayElement19(int posX, int posY, DWORD elementState);

        void __cdecl RenderPlayerInfoOnHoverDisplayElement(int posX, int posY, DWORD elementState);

        void __cdecl RenderGameSpeedTextDisplayElement(int posX, int posY, DWORD elementState);

        void __cdecl RenderUnknownDisplayElement25(int posX, int posY, DWORD elementState);

        void __cdecl RenderPeopleLeftToPlaceDisplayElement(int posX, int posY, DWORD elementState);

        void __cdecl RenderAndPlayKeepAndGranaryPlacementInfoDisplayElement(
            int posX, int posY, DWORD whichBuildingIsMissing);

        void __cdecl RenderPlayerPingUnkDisplayElement22(int posX, int posY, DWORD elementState);

        void __cdecl RenderGamePausedTextDisplayElement(int posX, int posY, DWORD elementState);

        void __cdecl RenderTimeUntilVictoryDisplayElement(int posX, int posY, DWORD elementState);

        void __cdecl RenderNoRushDisplayElementUnk(int posX, int posY, DWORD elementState);

        void __cdecl RenderTimeUntilDefeatDisplayElement(int posX, int posY, DWORD elementState);

        void __cdecl RenderSomeMultiplayerInfoUnkDisplayElement28(int posX, int posY, DWORD elementState);

    } // namespace DisplayElements
} // namespace UI
} // namespace OpenSHC
