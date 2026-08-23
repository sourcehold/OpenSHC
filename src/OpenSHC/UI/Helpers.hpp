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
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
namespace OpenSHC {
namespace UI {
    namespace Helpers {

        using OpenSHC::Map::Buildings::BuildingFailReasonEnum;
        using OpenSHC::Map::Buildings::BuildingType;
        using OpenSHC::Map::Units::EuroRecruitableState;
        using OpenSHC::UI::Enums::DisplayElementID;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        void __cdecl DrawOuterMenuBorder();

        BOOLEnum __cdecl AModalDialogIsActiveButIsNotQuitting();

        void __cdecl CallbackSetMultiplayerSpeedLevel();

        void __cdecl ClearSiegeInformationArray2();

        void __cdecl SomeSiegeUnitsComputation(int param_1);

        void __cdecl SomeSiegeRelatedCopying(int param_1);

        void __cdecl InitializeBasicMap();

        void __cdecl SetTaxesSetting_unknown(int taxesSettingUnk);

        void __cdecl SetTribesPatrolButtonPressed(undefined4 param_1);

        undefined4 __cdecl SomeUnitAndViewportCheck(int unitID);

        void __cdecl PlayPlacementWarning(BuildingFailReasonEnum param_1);

        void __cdecl HandleBuildingSelectionSpeech(int buildingIndexUnk);

        int __cdecl SomePopularityRelatedComputation();

        undefined4 __cdecl SomeFearFactorComputation();

        int __cdecl SomeGoldRelatedComputation();

        void __cdecl DisplayMapDescriptionAndAllocatePlayersToSlots();

        EuroRecruitableState __cdecl IsEuroUnitRecruitableUnk(int barrackUnitIdUnk);

        int __cdecl GetUnitRecruitPermission(int param_1);

        void __cdecl CheckIfEnoughGoldForLadderman();

        void __cdecl CheckIfEnoughGoldForMonk();

        BOOLEnum __cdecl CheckGoldResource(int param_1);

        void __cdecl CheckIfEnoughGoldForTunneler();

        void __cdecl SetEnoughGoldForRequestedUnitToTrueUnk();

        void __cdecl SetupPreviewMinimapDataUnk();

        void __cdecl ClearLobbyHoveredAI();

        void __cdecl CheckDisplayElementByIDAndSetForUnlimitedDisplay(
            DisplayElementID displayElementID, dword elementState);

        BOOLEnum __cdecl GetIfDisplayElementStateNotZero(DisplayElementID displayElementID);

        void __cdecl SumUnitPoints();

        void __cdecl SetTutorialBuildingActionState(int param_1, BuildingType buildingType);

        void __cdecl ResetEventStatusUnk();

        void __cdecl ColorEntireScreen(ushort color);

        void __cdecl DrawLoadedMenuStringHelper(int loadedMenuStringIndex, int xPos, int yPos, int maxWidth, uint color,
            int fontSize, BOOLEnum isSingleLine);

        void __cdecl DrawLoadedMenuStringHelperWithBlending(int loadedMenuStringIndex, int xPos, int yPos, int maxWidth,
            uint color, int fontSize, BOOLEnum isSingleLine, int blendStrength);

        void __cdecl StoreStringInMenuStringArray(char* textToStore);

        void __cdecl LoadScoresFileToMemory(char* filename);

        void __cdecl WriteMissionToScoresFile(char* param_1, int param_2);

        void __cdecl PlayJokeVideoBasedOnCurrentTimeAndPlayTime();

    } // namespace Helpers
} // namespace UI
} // namespace OpenSHC
