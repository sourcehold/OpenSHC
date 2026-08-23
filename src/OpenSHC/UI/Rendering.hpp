/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/Rendering.hpp'
*/

#pragma once

#include "OpenSHC/UI/Enums/DisplayElementID.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "WinDef.h"
namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::UI::Enums::DisplayElementID;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        void __cdecl RenderConnectAndPathLinkageInfoTextDisplayElement(int posX, int posY, DWORD tileType);

        void __cdecl TransformAndRenderPercentage(int xPos, int yPos, int valueUnk, BOOLEnum otherImageFlagUnk);

        void __cdecl RenderBottomLeftDateDisplayElement(int posX, int posY, DWORD elementState);

        void __cdecl RenderStartingGoodDisplayElement(int posX, int posY, DWORD elementState);

        void __cdecl RenderBuildingMenu_WorkshopWeaponProduction();

        void __cdecl RenderBuildingMenu_RecruitingBuilding();

        void __cdecl RenderBuildingMenu_Keep();

        void __cdecl RenderBuildingMenu_Inn();

        void __cdecl RenderBuildingMenu_Granary();

        void __cdecl RenderBuildingMenu_Fletcher();

        void __cdecl RenderBuildingMenu_Blacksmith();

        void __cdecl RenderBuildingMenu_Poleturner();

        void __cdecl RenderBuildingMenu_Armourer();

        void __cdecl RenderBuildingMenu_Tanner();

        void __cdecl RenderBuildingMenu_Bakery();

        void __cdecl RenderBuildingMenu_Brewery();

        void __cdecl RenderBuildingMenu_Outpost();

        void __cdecl RenderBuildingMenu_House();

        void __cdecl RenderBuildingMenu_WoodcutterShut();

        void __cdecl RenderBuildingMenu_OxThether();

        void __cdecl RenderBuildingMenu_Quarry();

        void __cdecl RenderBuildingMenu_Ironmine();

        void __cdecl RenderBuildingMenu_PitchRig();

        void __cdecl RenderBuildingMenu_HuntersHut();

        void __cdecl RenderBuildingMenu_Apothecary();

        void __cdecl RenderBuildingMenu_Wheatfarm();

        void __cdecl RenderBuildingMenu_Hopfarm();

        void __cdecl RenderBuildingMenu_Applefarm();

        void __cdecl RenderBuildingMenu_Diaryfarm();

        void __cdecl RenderBuildingMenu_Mill();

        void __cdecl RenderBuildingMenu_ChapelAndChurch();

        void __cdecl RenderBuildingMenu_Stockpile();

        void __cdecl RenderBuildingMenu_Armory();

        void __cdecl RenderBuildingMenu_Quarry_Stonepile();

        void __cdecl RenderBuildingMenu_Engineersguild();

        void __cdecl RenderBuildingMenu_Tunnelersguild();

        void __cdecl RenderBuildingMenu_Cathedral();

        void __cdecl RenderPeasantMenu_CurrentActionUnk(int unitID, int xPos, int yPos);

        void __cdecl RenderBuildingMenu_Marketplace();

        void __cdecl RenderBuildingMenu_Marketplace_Stonks();

        void __cdecl RenderBuildingMenu_Marketplace_Food();

        void __cdecl RenderBuildingMenu_Marketplace_Resource();

        void __cdecl RenderBuildingMenu_Marketplace_Weapons();

        void __cdecl RenderBuildingMenu_Marketplace_Trade();

        void __cdecl RenderBuildingMenu_Well();

        void __cdecl RenderBuildingMenu_WaterPot();

        void __cdecl RenderBuildingMenu_Oilsmelter();

        void __cdecl RenderBuildingMenu_Stables();

        void __cdecl RenderBuildingMenu_Drawbridge();

        void __cdecl RenderBuildingMenu_Unused_PosternGate();

        void __cdecl RenderBuildingMenu_TunnelEntrance();

        void __cdecl RenderBuildingMenu_Signpost();

        void __cdecl RenderBuildingMenu_KillingPit();

        void __cdecl RenderBuildingMenu_Campfire();

        void __cdecl RenderBuildingMenu_Gallows();

        void __cdecl RenderBuildingMenu_Stocks();

        void __cdecl RenderBuildingMenu_Unused_Witchhoist();

        void __cdecl RenderBuildingMenu_Maypole();

        void __cdecl RenderBuildingMenu_Gardens();

        void __cdecl RenderBuildingMenu_TrainingGrounds();

        void __cdecl RenderBuildingMenu_CessPit();

        void __cdecl RenderBuildingMenu_BurningStake();

        void __cdecl RenderBuildingMenu_Gibbet();

        void __cdecl RenderBuildingMenu_Dungeon();

        void __cdecl RenderBuildingMenu_StretchingRack();

        void __cdecl RenderBuildingMenu_Unused_FloggingRack();

        void __cdecl RenderBuildingMenu_ChoppingBlock();

        void __cdecl RenderBuildingMenu_DunkingStool();

        void __cdecl RenderBuildingMenu_DogCage();

        void __cdecl RenderBuildingMenu_Statue();

        void __cdecl RenderBuildingMenu_Shrine();

        void __cdecl RenderBuildingMenu_Unused_BeeHive();

        void __cdecl RenderBuildingMenu_DancingBear();

        void __cdecl RenderBuildingMenu_Unused_Pond();

        void __cdecl RenderBuildingMenu_Unused_BearCave();

        void __cdecl RenderBuildingMenu_Siegetent_Catapult();

        void __cdecl RenderBuildingMenu_Siegetent_Fireballista();

        void __cdecl RenderBuildingMenu_Siegetent_Trebuchet();

        void __cdecl RenderBuildingMenu_Siegetent_Siegetower();

        void __cdecl RenderBuildingMenu_Siegetent_BatteringRam();

        void __cdecl RenderBuildingMenu_Siegetent_Shield();

        void __cdecl RenderBuildingMenu_RenderTowerAndGateHealth();

        void __cdecl RenderStatusMenu_Popularity();

        void __cdecl RenderStatusMenu_FearFactor();

        void __cdecl RenderStatusMenu_Population();

        void __cdecl RenderStatusMenu_Food();

        void __cdecl RenderStatusMenu_Resources();

        void __cdecl RenderStatusMenu_Religion();

        void __cdecl RenderStatusMenu_Weapons();

        void __cdecl RenderStatusMenu_Chimp();

        void __cdecl RenderBuildingMenu_Gatehouse();

        void __cdecl RenderBuildingMenu_Tower();

        void __cdecl RenderStatusMenu_Overview();

        void __cdecl RenderStatusMenu_Army();

        void __cdecl InitBlendFilterArraysUnk();

        void __cdecl RenderTerrainTilesCenterPiece();

        void __cdecl RenderCurrentNotActiveButtonWithPossibleAlphaTexOnCurrentSurfaceUnk();

        void __cdecl RenderCurrentButtonOnScreenMenu();

        void __cdecl RenderCurrentButtonToScreenMenuWithBlendingUnk(int blendStrengthUnk);

        uint __cdecl TransformToCurrentModeColor(int red, int green, int blue);

        void __cdecl RenderLoadAndSaveBar(int progressValueUnk);

        void __cdecl TogglePlayerPingDisplayElementUnk(DisplayElementID displayElementID, uint toggleValue);

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

        void __cdecl RenderScenarioButtonWithText(int textNumInGroup);

        void __cdecl RenderGreatestLordScreen();

        int __cdecl RenderMissionObjectivesUnk();

        void __cdecl RenderGfxHelperUnk(int loadedGfxIndex, int xPosInMenuRect, int yPosInMenuRect);

        void __cdecl RenderMenuGfxHelper(int gfxIndex, int x, int y, int blendStrength);

        void __cdecl RenderHistoryBookEdgeUnk();

        void __cdecl RenderNoViewsFoundWarning();

        void __cdecl RenderCurrentMenuView();

    } // namespace Rendering
} // namespace UI
} // namespace OpenSHC
