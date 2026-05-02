/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/Rendering.hpp'
*/

#pragma once

#include "OpenSHC/UI/Enums/DisplayElementIDInt.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "WinDef.h"
namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::UI::Enums::DisplayElementIDInt;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        void __cdecl RenderConnectAndPathLinkageInfoTextDisplayElement(int posX, int posY, DWORD tileType);

        void __cdecl TransformAndRenderPercentage(int xPos, int yPos, int valueUnk, BOOLEnum otherImageFlagUnk);

        void __cdecl RenderBottomLeftDateDisplayElement(int posX, int posY, DWORD elementState);

        void __cdecl RenderStartingGoodDisplayElement(int posX, int posY, DWORD elementState);

        void __cdecl RenderBuildingMenu_WorkshopWeaponProduction();

        void __cdecl RenderBuildingMenu_RecruitingBuilding();

        void __stdcall RenderBuildingMenu_Keep();

        void __stdcall RenderBuildingMenu_Inn();

        void __cdecl RenderBuildingMenu_Granary();

        void __stdcall RenderBuildingMenu_Fletcher();

        void __stdcall RenderBuildingMenu_Blacksmith();

        void __stdcall RenderBuildingMenu_Poleturner();

        void __stdcall RenderBuildingMenu_Armourer();

        void __stdcall RenderBuildingMenu_Tanner();

        void __stdcall RenderBuildingMenu_Bakery();

        void __stdcall RenderBuildingMenu_Brewery();

        void __stdcall RenderBuildingMenu_Outpost();

        void __cdecl RenderBuildingMenu_House();

        void __stdcall RenderBuildingMenu_WoodcutterShut();

        void __stdcall RenderBuildingMenu_OxThether();

        void __stdcall RenderBuildingMenu_Quarry();

        void __stdcall RenderBuildingMenu_Ironmine();

        void __stdcall RenderBuildingMenu_PitchRig();

        void __stdcall RenderBuildingMenu_HuntersHut();

        void __stdcall RenderBuildingMenu_Apothecary();

        void __stdcall RenderBuildingMenu_Wheatfarm();

        void __stdcall RenderBuildingMenu_Hopfarm();

        void __stdcall RenderBuildingMenu_Applefarm();

        void __stdcall RenderBuildingMenu_Diaryfarm();

        void __stdcall RenderBuildingMenu_Mill();

        void __stdcall RenderBuildingMenu_ChapelAndChurch();

        void __stdcall RenderBuildingMenu_Stockpile();

        void __stdcall RenderBuildingMenu_Armory();

        void __stdcall RenderBuildingMenu_Quarry_Stonepile();

        void __stdcall RenderBuildingMenu_Engineersguild();

        void __stdcall RenderBuildingMenu_Tunnelersguild();

        void __stdcall RenderBuildingMenu_Cathedral();

        void __cdecl RenderPeasantMenu_CurrentActionUnk(int unitID, int xPos, int yPos);

        void __stdcall RenderBuildingMenu_Marketplace();

        void __stdcall RenderBuildingMenu_Marketplace_Stonks();

        void __stdcall RenderBuildingMenu_Marketplace_Food();

        void __stdcall RenderBuildingMenu_Marketplace_Resource();

        void __stdcall RenderBuildingMenu_Marketplace_Weapons();

        void __stdcall RenderBuildingMenu_Marketplace_Trade();

        void __stdcall RenderBuildingMenu_Well();

        void __stdcall RenderBuildingMenu_WaterPot();

        void __stdcall RenderBuildingMenu_Oilsmelter();

        void __stdcall RenderBuildingMenu_Stables();

        void __stdcall RenderBuildingMenu_Drawbridge();

        void __stdcall RenderBuildingMenu_Unused_PosternGate();

        void __stdcall RenderBuildingMenu_TunnelEntrance();

        void __stdcall RenderBuildingMenu_Signpost();

        void __stdcall RenderBuildingMenu_KillingPit();

        void __stdcall RenderBuildingMenu_Campfire();

        void __stdcall RenderBuildingMenu_Gallows();

        void __stdcall RenderBuildingMenu_Stocks();

        void __stdcall RenderBuildingMenu_Unused_Witchhoist();

        void __stdcall RenderBuildingMenu_Maypole();

        void __stdcall RenderBuildingMenu_Gardens();

        void __stdcall RenderBuildingMenu_TrainingGrounds();

        void __stdcall RenderBuildingMenu_CessPit();

        void __stdcall RenderBuildingMenu_BurningStake();

        void __stdcall RenderBuildingMenu_Gibbet();

        void __stdcall RenderBuildingMenu_Dungeon();

        void __stdcall RenderBuildingMenu_StretchingRack();

        void __stdcall RenderBuildingMenu_Unused_FloggingRack();

        void __stdcall RenderBuildingMenu_ChoppingBlock();

        void __stdcall RenderBuildingMenu_DunkingStool();

        void __stdcall RenderBuildingMenu_DogCage();

        void __stdcall RenderBuildingMenu_Statue();

        void __stdcall RenderBuildingMenu_Shrine();

        void __stdcall RenderBuildingMenu_Unused_BeeHive();

        void __stdcall RenderBuildingMenu_DancingBear();

        void __stdcall RenderBuildingMenu_Unused_Pond();

        void __stdcall RenderBuildingMenu_Unused_BearCave();

        void __stdcall RenderBuildingMenu_Siegetent_Catapult();

        void __stdcall RenderBuildingMenu_Siegetent_Fireballista();

        void __stdcall RenderBuildingMenu_Siegetent_Trebuchet();

        void __stdcall RenderBuildingMenu_Siegetent_Siegetower();

        void __stdcall RenderBuildingMenu_Siegetent_BatteringRam();

        void __stdcall RenderBuildingMenu_Siegetent_Shield();

        void __stdcall RenderBuildingMenu_RenderTowerAndGateHealth();

        void __stdcall RenderStatusMenu_Popularity();

        void __stdcall RenderStatusMenu_FearFactor();

        void __stdcall RenderStatusMenu_Population();

        void __stdcall RenderStatusMenu_Food();

        void __stdcall RenderStatusMenu_Resources();

        void __stdcall RenderStatusMenu_Religion();

        void __stdcall RenderStatusMenu_Weapons();

        void __stdcall RenderStatusMenu_Chimp();

        void __stdcall RenderBuildingMenu_Gatehouse();

        void __stdcall RenderBuildingMenu_Tower();

        void __stdcall RenderStatusMenu_Overview();

        void __stdcall RenderStatusMenu_Army();

        void __stdcall RenderTerrainTilesCenterPiece();

        void __stdcall RenderCurrentNotActiveButtonWithPossibleAlphaTexOnCurrentSurfaceUnk();

        void __stdcall RenderCurrentButtonOnScreenMenu();

        void __cdecl RenderCurrentButtonToScreenMenuWithBlendingUnk(int blendStrengthUnk);

        uint __cdecl TransformToCurrentModeColor(int red, int green, int blue);

        void __cdecl RenderLoadAndSaveBar(int progressValueUnk);

        void __cdecl TogglePlayerPingDisplayElementUnk(DisplayElementIDInt displayElementID, uint toggleValue);

        void __stdcall RenderDisplayElementsUnk();

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

        void __cdecl RenderScenarioButtonWithText(int textNumInGroup);

        void __stdcall RenderGreatestLordScreen();

        int __stdcall RenderMissionObjectivesUnk();

        void __cdecl RenderGfxHelperUnk(int loadedGfxIndex, int xPosInMenuRect, int yPosInMenuRect);

        void __cdecl RenderMenuGfxHelper(int gfxIndex, int x, int y, int blendStrength);

        void __stdcall RenderHistoryBookEdgeUnk();

        void __stdcall RenderNoViewsFoundWarning();

        void __stdcall RenderCurrentMenuView();

    } // namespace Rendering
} // namespace UI
} // namespace OpenSHC
