/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Game/GameCore.hpp'
*/

#pragma once

#include "OpenSHC/Game/GameMode2Int.hpp"
#include "OpenSHC/Game/TrailTypeInt.hpp"
#include "OpenSHC/Map/MapLockStateInt.hpp"
#include "OpenSHC/Map/Navigation/Algorithms/XYPair.hpp"
#include "OpenSHC/Rendering/Enums/DirectDrawStatusInt.hpp"
#include "OpenSHC/UI/ActiveMenuTab.hpp"
#include "OpenSHC/UI/Enums/BuildMenuTabTypeShort.hpp"
#include "OpenSHC/UI/Enums/MenuViewTypeInt.hpp"
#include "OpenSHC/UI/MenuItemActionHandler.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "WinDef.h"

namespace OpenSHC {
namespace Game {

    using OpenSHC::Game::GameMode2Int;
    using OpenSHC::Game::TrailTypeInt;
    using OpenSHC::Map::MapLockStateInt;
    using OpenSHC::Map::Navigation::Algorithms::XYPair;
    using OpenSHC::Rendering::Enums::DirectDrawStatusInt;
    using OpenSHC::UI::ActiveMenuTab;
    using OpenSHC::UI::MenuItemActionHandler;
    using OpenSHC::UI::Enums::BuildMenuTabTypeShort;
    using OpenSHC::UI::Enums::MenuViewTypeInt;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

    // SIZE: 0x00002380
    class GameCore {
    public:
        DirectDrawStatusInt directDrawStatus; // 0x00000000 length: 4
        int menuSwitchDelay; // 0x00000004 length: 4
        dword menuRenderMoment; // 0x00000008 length: 4
        MenuViewTypeInt currentMenuViewType; // 0x0000000C length: 4
        ActiveMenuTab activeMenuTab; // 0x00000010 length: 4
        dword unknownAlwaysZero01; // 0x00000014 length: 4
        MenuViewTypeInt menuViewToSwitchTo; // 0x00000018 length: 4
        ActiveMenuTab menuTabToSwitchTo; // 0x0000001C length: 4
        dword field8_0x20; // 0x00000020 length: 4
        ActiveMenuTab buildmenuMenuTabToSwitchTo; // 0x00000024 length: 4
        dword buildingandstatusmenuMenuTabToSwitchTo; // 0x00000028 length: 4
        dword landscapingmenuMenuTabToSwitchTo; // 0x0000002C length: 4
        dword field12_0x30; // 0x00000030 length: 4
        ActiveMenuTab unknownActiveMenuTabToSwitchTo; // 0x00000034 length: 4
        BuildMenuTabTypeShort tabTypeSiegeSubset; // 0x00000038 length: 4
        dword historicCampaignNumber; // 0x0000003C length: 4
        int missionNumber1to20; // 0x00000040 length: 4
        int progressCallToArms; // 0x00000044 length: 4
        int progressSaladinsConquest; // 0x00000048 length: 4
        int progressTheKingsCrusade; // 0x0000004C length: 4
        int progressCrusaderStates; // 0x00000050 length: 4
        dword furthestMission; // 0x00000054 length: 4
        dword unlockAllHistoricalCampaigns; // 0x00000058 length: 4
        dword unused1; // 0x0000005C length: 4
        dword section1066; // 0x00000060 length: 4
        dword field25_0x64; // 0x00000064 length: 4
        GameMode2Int gameMode_2; // 0x00000068 length: 4
        int field27_0x6c; // 0x0000006C length: 4
        dword specialMultiplayerState; // 0x00000070 length: 4
        dword field29_0x74; // 0x00000074 length: 4
        int mapU4Int1; // 0x00000078 length: 4
        int mapU4Int1_2; // 0x0000007C length: 4
        dword field32_0x80; // 0x00000080 length: 4
        int battleLevel; // 0x00000084 length: 4
        dword cowPoisonTrackerUnk; // 0x00000088 length: 4
        int someSoundMatchTime_1; // 0x0000008C length: 4
        dword field36_0x90; // 0x00000090 length: 4
        int battleLevel2; // 0x00000094 length: 4
        dword mapTimeInTicks; // 0x00000098 length: 4
        dword section1127; // 0x0000009C length: 4
        dword field40_0xa0; // 0x000000A0 length: 4
        BOOLEnum currentlyInGameUnk_0xa4; // 0x000000A4 length: 4
        dword gameSpeedMultiplicator; // 0x000000A8 length: 4
        dword performedGameTicksThisLoop; // 0x000000AC length: 4
        dword gameTicksThisLoop; // 0x000000B0 length: 4
        dword gameTicksLastLoop; // 0x000000B4 length: 4
        dword averageTimePerGameTick; // 0x000000B8 length: 4
        dword timeBeforeRunningGameTicksThisLoop; // 0x000000BC length: 4
        int countdown; // 0x000000C0 length: 4
        int uniqueGameObjectTracker; // 0x000000C4 length: 4
        dword gameSpeedLevel; // 0x000000C8 length: 4
        dword settingBubbleHelp; // 0x000000CC length: 4
        BOOLEnum isTimeHalted; // 0x000000D0 length: 4
        dword section1076; // 0x000000D4 length: 4
        dword isTimeHalted2; // 0x000000D8 length: 4
        dword field55_0xdc; // 0x000000DC length: 4
        int missionDifficulty; // 0x000000E0 length: 4
        int missionDifficulty2; // 0x000000E4 length: 4
        int missionDifficulty_2; // 0x000000E8 length: 4
        int missionDifficulty_3; // 0x000000EC length: 4
        int missionDifficulty_1; // 0x000000F0 length: 4
        int missionDifficulty_0; // 0x000000F4 length: 4
        dword field62_0xf8; // 0x000000F8 length: 4
        BOOLEnum solitaryAllBuildingsAreFree; // 0x000000FC length: 4
        int field64_0x100; // 0x00000100 length: 4
        dword field65_0x104; // 0x00000104 length: 4
        dword field66_0x108; // 0x00000108 length: 4
        dword unknownAlwaysZero; // 0x0000010C length: 4
        dword unknownAlwaysZero02; // 0x00000110 length: 4
        int unknownAlwaysZero03; // 0x00000114 length: 4
        BOOLEnum unknownFlag_0x118; // 0x00000118 length: 4
        DWORD unknownTime_0x11c; // 0x0000011C length: 4
        byte unused_0x120[8]; // 0x00000120 length: 8
        int scribeAnimationFrameCopy; // 0x00000128 length: 4
        int taxesSettingUnk; // 0x0000012C length: 4
        BOOLEnum unknownScribeRelatedFlag_0x130; // 0x00000130 length: 4
        int scribeAnimationFrame; // 0x00000134 length: 4
        int scribeAnimationFrame2; // 0x00000138 length: 4
        int taxestimeUnk; // 0x0000013C length: 4
        byte unused_0x140[4]; // 0x00000140 length: 4
        int field80_0x144; // 0x00000144 length: 4
        int field81_0x148; // 0x00000148 length: 4
        dword isBinkVideoPlaying; // 0x0000014C length: 4
        dword section1095; // 0x00000150 length: 4
        dword newPlayerID; // 0x00000154 length: 4
        dword hasMenuRenderedUnk; // 0x00000158 length: 4
        dword field86_0x15c; // 0x0000015C length: 4
        int xbowProducible_logic; // 0x00000160 length: 4
        int pikeProducible_logic; // 0x00000164 length: 4
        int swordProducible_logic; // 0x00000168 length: 4
        int bowProducible_logic; // 0x0000016C length: 4
        int spearProducible_logic; // 0x00000170 length: 4
        int maceProducible_logic; // 0x00000174 length: 4
        byte unused_0x178[2024]; // 0x00000178 length: 2024
        BOOLEnum cheatModeFlag; // 0x00000960 length: 4
        BOOLEnum solitaryAltUDungeon; // 0x00000964 length: 4
        dword descriptionUseStringTable; // 0x00000968 length: 4
        dword descriptionStringTableIndex; // 0x0000096C length: 4
        char temporaryTextBufferOfSize1000[1000]; // 0x00000970 length: 1000
        char standaloneFilename[1001]; // 0x00000D58 length: 1001
        byte unused_0x1141[1003]; // 0x00001141 length: 1003
        int mapU4Int0; // 0x0000152C length: 4
        int mapU4Int0_2; // 0x00001530 length: 4
        dword U2_mapType_singleOrMulti; // 0x00001534 length: 4
        dword mapU2MiddleBytes; // 0x00001538 length: 4
        dword field105_0x153c; // 0x0000153C length: 4
        dword field106_0x1540; // 0x00001540 length: 4
        dword field107_0x1544; // 0x00001544 length: 4
        dword field108_0x1548; // 0x00001548 length: 4
        int mapU2PlayersCount; // 0x0000154C length: 4
        int mapU4Int3_balanced; // 0x00001550 length: 4
        int mapDescUseStringTable; // 0x00001554 length: 4
        int mapDescUseStringTableIndex; // 0x00001558 length: 4
        char mapDescription[1000]; // 0x0000155C length: 1000
        byte unused_0x1944[1004]; // 0x00001944 length: 1004
        int mapType; // 0x00001D30 length: 4
        int sh1MapKeeps[5]; // 0x00001D34 length: 20
        int mapPlayerCount; // 0x00001D48 length: 4
        XYPair keepPositions[8]; // 0x00001D4C length: 64
        int savedMapBalance; // 0x00001D8C length: 4
        MapLockStateInt U3_mapLockedState; // 0x00001D90 length: 4
        MapLockStateInt savedMapLocked; // 0x00001D94 length: 4
        dword field122_0x1d98; // 0x00001D98 length: 4
        int mapU3EndInt; // 0x00001D9C length: 4
        int savedMapEndInt2; // 0x00001DA0 length: 4
        int canBeginMainLoop; // 0x00001DA4 length: 4
        int twohundred; // 0x00001DA8 length: 4
        byte unused_0x1dac[4]; // 0x00001DAC length: 4
        MenuItemActionHandler* menuType7_MenuItemClickHandlerUnk; // 0x00001DB0 length: 4
        int numOfAIsWithCastleUnk; // 0x00001DB4 length: 4
        int arrayOfLordIdsWithAIVsUnk[16]; // 0x00001DB8 length: 64
        int furthestSkirmishTrailMission; // 0x00001DF8 length: 4
        int skirmishTrailMonthsTakenOrChicken[50]; // 0x00001DFC length: 200
        int skirmishTrailStartDateInMonths[50]; // 0x00001EC4 length: 200
        dword skirmishTrailYearReached; // 0x00001F8C length: 4
        dword skirmishTrailStartDateMonths; // 0x00001F90 length: 4
        BOOLEnum isSkirmishTrail; // 0x00001F94 length: 4
        dword skirmishTrailProgress; // 0x00001F98 length: 4
        TrailTypeInt currentTrailType; // 0x00001F9C length: 4
        int furthestWarchestTrailMission; // 0x00001FA0 length: 4
        int warchestTrailMonthsTakenOrChicken[50]; // 0x00001FA4 length: 200
        int warchestTrailStartDatesInMonths[50]; // 0x0000206C length: 200
        dword warchestTrailYearReached; // 0x00002134 length: 4
        dword warchestTrailStartDateMonths; // 0x00002138 length: 4
        dword field144_0x213c; // 0x0000213C length: 4
        dword warchestTrailProgress; // 0x00002140 length: 4
        int furthestExtremeTrailMission; // 0x00002144 length: 4
        int extremeTrailMonthsTakenOrChicken[50]; // 0x00002148 length: 200
        int extremeTrailStartDatesInMonths[50]; // 0x00002210 length: 200
        dword extremeTrailYearReached; // 0x000022D8 length: 4
        dword extremeTrailStartDateMonths; // 0x000022DC length: 4
        dword field151_0x22e0; // 0x000022E0 length: 4
        int extremeTrailProgress; // 0x000022E4 length: 4
        int lordIconUnk; // 0x000022E8 length: 4
        int lordIcons[9]; // 0x000022EC length: 36
        byte unused_0x2310[4]; // 0x00002310 length: 4
        int selectedLordTypeUnk; // 0x00002314 length: 4
        int selectedLordType_2Unk; // 0x00002318 length: 4
        int selectedLordTypes[9]; // 0x0000231C length: 36
        dword field159_0x2340; // 0x00002340 length: 4
        dword gamePausedLogical; // 0x00002344 length: 4
        int viewportFocusBeforeBarracksHotkey; // 0x00002348 length: 4
        int viewportFocusBeforeMercenaryHotkey; // 0x0000234C length: 4
        int viewportFocusBeforeGranaryHotkey; // 0x00002350 length: 4
        int viewportFocusBeforeMarketHotkey; // 0x00002354 length: 4
        int viewportFocusBeforeKeepHotkey; // 0x00002358 length: 4
        int viewportFocusBeforeArmoryHotkey; // 0x0000235C length: 4
        int viewportFocusBeforeEngineersGuildHotkey; // 0x00002360 length: 4
        int field168_0x2364; // 0x00002364 length: 4
        BOOLEnum genieVoiceActive; // 0x00002368 length: 4
        uint timeSum_2; // 0x0000236C length: 4
        dword gameDuration; // 0x00002370 length: 4
        byte tacticalPowersDisplayFlag; // 0x00002374 length: 1
        byte unusedOption1; // 0x00002375 length: 1
        byte isVictoryOrDefeatUnk; // 0x00002376 length: 1
        byte skipStoreSKMasters; // 0x00002377 length: 1
        byte altRToggleMinimapHideWildlife; // 0x00002378 length: 1
        byte unused_0x2379[3]; // 0x00002379 length: 3
        dword forty; // 0x0000237C length: 4

    private:
        GameCore(GameCore const&);
        void operator=(GameCore const&);

        GameCore();
        ~GameCore();

    public:
        // Constructor
        GameCore* Constructor_GameCore();

        void setViewOnExitUnk();

        void setTabToSwitchTo();

        void meth_0x46b320();

        void switchToMenuView(MenuViewTypeInt menuID, int delay);

        void processMenuViewSwitch();

        void viewportAndScrollingRelated();

        BOOLEnum getAreWeInAInGameMenu();

        BOOLEnum isInBuildingTab();

        void removeJesterAndLadyUnitsInCertainMissions();

        void FUN_0046bc90();

        BOOLEnum isGameHaltingMenuOpen();

        void setStartDateUnk(int param_1);

        void incrementMissionProgress();

        void switchToScenarioDescriptionMenuView();

        void meth_0x471a00();

        void hideOrUnhideUI();
    };

    static_assert_cpp98_obj(sizeof(GameCore) == 9088, GameCore);

#pragma pack(pop)

    MACRO_STRUCT_RESOLVER(GameCore, false, Address::SHC_3BB0A8C1_0x01FE7D10) pDAT_GameCore;

} // namespace Game
} // namespace OpenSHC
