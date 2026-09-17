/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/Helpers.hpp'
*/

#pragma once

#include "OpenSHC/Map/Buildings/BuildingFailReasonEnum.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Units/EuroRecruitableState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "WinDef.h"
namespace OpenSHC {
namespace UI {
    namespace Helpers {

        using OpenSHC::Map::Buildings::BuildingFailReasonEnum;
        using OpenSHC::Map::Buildings::BuildingType;
        using OpenSHC::Map::Units::EuroRecruitableState;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        void __cdecl LoadTGX_shc_back();

        void __cdecl MainMenu_Unknown21_Prepare();

        BOOLEnum __cdecl AModalDialogIsActiveButIsNotQuitting();

        void __cdecl CallbackSetMultiplayerSpeedLevel();

        void __cdecl ClearSiegeInformationArray2();

        void __cdecl SomeSiegeUnitsComputation(int param_1);

        void __cdecl SomeSiegeRelatedCopying(int param_1);

        void __cdecl InitializeBasicMap();

        void __cdecl SetTaxesSetting_unknown(int taxesSettingUnk);

        void __cdecl SetTribesPatrolButtonPressed(undefined4 param_1);

        undefined4 __cdecl SomeUnitAndViewportCheck(int unitID);

        void __cdecl HandleWallTerrainMouseDrag();

        void __cdecl PlayPlacementWarning(BuildingFailReasonEnum param_1);

        void __cdecl HandleBuildingSelectionSpeech(int buildingIndexUnk);

        int __cdecl SomePopularityRelatedComputation();

        undefined4 __cdecl SomeFearFactorComputation();

        int __cdecl SomeGoldRelatedComputation();

        void __cdecl CountPlayerUnitsByType();

        HCURSOR __cdecl SetCursorDependingOnProgramState();

        EuroRecruitableState __cdecl IsEuroUnitRecruitableUnk(int barrackUnitIdUnk);

        int __cdecl GetUnitRecruitPermission(int param_1);

        BOOLEnum __cdecl HasEnoughGold(int param_1);

        void __cdecl CheckIfEnoughGoldForLadderman();

        void __cdecl CheckIfEnoughGoldForMonk();

        BOOLEnum __cdecl CheckGoldResource(int param_1);

        void __cdecl CheckIfEnoughGoldForTunneler();

        void __cdecl SetEnoughGoldForRequestedUnitToTrueUnk();

        void __cdecl DisableMercPostPortraits();

        undefined4 __cdecl TicksSinceCounterStart();

        void __cdecl SetupPreviewMinimapDataUnk();

        void __cdecl ShowProgressBarSaveLoadDialog(int param_1);

        void __cdecl BuildEnemyPlayerList();

        void __cdecl ClearLobbyHoveredAI();

        void __cdecl PlayAMessageFromAI(uint aiType, int param_2);

        void __cdecl SumUnitPoints();

        void __cdecl RestoreScenarioGold();

        void __cdecl CaptureCurrentTimeToUnknownTime01();

        void __cdecl InitTutorialStepTransition(int param_1);

        undefined4 __cdecl GetCurrentTutorialStep();

        void __cdecl RecordTutorialPlayerAction(int param_1);

        void __cdecl SetTutorialBuildingActionState(int param_1, BuildingType buildingType);

        void __cdecl ResetTutorialActionTrackers();

        void __cdecl SetTutorialHintActiveWithTimestamp();

        void __cdecl UpdateTutorialStepAndProgress();

        void __cdecl ParseCampaignMapHotspotBitmap();

        void __cdecl ResetEventStatusUnk();

        void __cdecl ReadMapHeaderFromFile(char* param_1);

        void __cdecl TacticalPowersFill();

        void __cdecl ColorEntireScreen(ushort color);

        void __cdecl StoreStringInMenuStringArray(char* textToStore);

        void __cdecl LoadScoresFileToMemory(char* filename);

        void __cdecl BuildIntroLogoSequence(undefined4 param_1, undefined4 param_2);

        int __cdecl PrepareHistoryBook();

        void __cdecl TrimStoredMenuString(int storedMenuStringIndex, undefined4 param_2, undefined4 param_3,
            int allowedWidth, undefined4 param_5, int fontSize);

        undefined4 __cdecl FindCampaignMapHotspotAtMouse();

        void __cdecl BuildExtremeDemoIntroScript();

        void __cdecl WriteMissionToScoresFile(char* param_1, int param_2);

        void __cdecl PlayJokeVideoBasedOnCurrentTimeAndPlayTime();

    } // namespace Helpers
} // namespace UI
} // namespace OpenSHC
