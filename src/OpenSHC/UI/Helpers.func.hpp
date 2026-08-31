/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/Helpers.func.hpp'
*/

#pragma once

#include "OpenSHC/Map/Buildings/BuildingFailReasonEnum.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Units/EuroRecruitableState.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"
#include "OpenSHC/UI/Helpers.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
namespace OpenSHC {
namespace UI {
    namespace Helpers_Func {

        using OpenSHC::Map::Buildings::BuildingFailReasonEnum;
        using OpenSHC::Map::Buildings::BuildingType;
        using OpenSHC::Map::Units::EuroRecruitableState;
        using OpenSHC::UI::Enums::DisplayElementID;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00424BE0, &OpenSHC::UI::Helpers::DrawOuterMenuBorder)
        DrawOuterMenuBorder;

        MACRO_FUNCTION_RESOLVER(BOOLEnum(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00427210,
            &OpenSHC::UI::Helpers::AModalDialogIsActiveButIsNotQuitting)
        AModalDialogIsActiveButIsNotQuitting;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00429650,
            &OpenSHC::UI::Helpers::CallbackSetMultiplayerSpeedLevel)
        CallbackSetMultiplayerSpeedLevel;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x0042C190,
            &OpenSHC::UI::Helpers::ClearSiegeInformationArray2)
        ClearSiegeInformationArray2;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x0042C1E0,
            &OpenSHC::UI::Helpers::SomeSiegeUnitsComputation)
        SomeSiegeUnitsComputation;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x0042C540,
            &OpenSHC::UI::Helpers::SomeSiegeRelatedCopying)
        SomeSiegeRelatedCopying;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x0042F010, &OpenSHC::UI::Helpers::InitializeBasicMap)
        InitializeBasicMap;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int taxesSettingUnk), false, Address::SHC_3BB0A8C1_0x00433560,
            &OpenSHC::UI::Helpers::SetTaxesSetting_unknown)
        SetTaxesSetting_unknown;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(undefined4 param_1), false, Address::SHC_3BB0A8C1_0x00434340,
            &OpenSHC::UI::Helpers::SetTribesPatrolButtonPressed)
        SetTribesPatrolButtonPressed;

        MACRO_FUNCTION_RESOLVER(undefined4(__cdecl*)(int unitID), false, Address::SHC_3BB0A8C1_0x004347F0,
            &OpenSHC::UI::Helpers::SomeUnitAndViewportCheck)
        SomeUnitAndViewportCheck;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(BuildingFailReasonEnum param_1), false, Address::SHC_3BB0A8C1_0x004380E0,
            &OpenSHC::UI::Helpers::PlayPlacementWarning)
        PlayPlacementWarning;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int buildingIndexUnk), false, Address::SHC_3BB0A8C1_0x00439730,
            &OpenSHC::UI::Helpers::HandleBuildingSelectionSpeech)
        HandleBuildingSelectionSpeech;

        MACRO_FUNCTION_RESOLVER(int(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x0043E540,
            &OpenSHC::UI::Helpers::SomePopularityRelatedComputation)
        SomePopularityRelatedComputation;

        MACRO_FUNCTION_RESOLVER(undefined4(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x0043E5A0,
            &OpenSHC::UI::Helpers::SomeFearFactorComputation)
        SomeFearFactorComputation;

        MACRO_FUNCTION_RESOLVER(
            int(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x0043E5F0, &OpenSHC::UI::Helpers::SomeGoldRelatedComputation)
        SomeGoldRelatedComputation;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004410D0,
            &OpenSHC::UI::Helpers::DisplayMapDescriptionAndAllocatePlayersToSlots)
        DisplayMapDescriptionAndAllocatePlayersToSlots;

        MACRO_FUNCTION_RESOLVER(EuroRecruitableState(__cdecl*)(int barrackUnitIdUnk), false,
            Address::SHC_3BB0A8C1_0x00464DA0, &OpenSHC::UI::Helpers::IsEuroUnitRecruitableUnk)
        IsEuroUnitRecruitableUnk;

        MACRO_FUNCTION_RESOLVER(int(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00464E80,
            &OpenSHC::UI::Helpers::GetUnitRecruitPermission)
        GetUnitRecruitPermission;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00465080,
            &OpenSHC::UI::Helpers::CheckIfEnoughGoldForLadderman)
        CheckIfEnoughGoldForLadderman;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004650A0, &OpenSHC::UI::Helpers::CheckIfEnoughGoldForMonk)
        CheckIfEnoughGoldForMonk;

        MACRO_FUNCTION_RESOLVER(BOOLEnum(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004650C0,
            &OpenSHC::UI::Helpers::CheckGoldResource)
        CheckGoldResource;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004650F0,
            &OpenSHC::UI::Helpers::CheckIfEnoughGoldForTunneler)
        CheckIfEnoughGoldForTunneler;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00466E00,
            &OpenSHC::UI::Helpers::SetEnoughGoldForRequestedUnitToTrueUnk)
        SetEnoughGoldForRequestedUnitToTrueUnk;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00493050,
            &OpenSHC::UI::Helpers::SetupPreviewMinimapDataUnk)
        SetupPreviewMinimapDataUnk;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004AE7C0, &OpenSHC::UI::Helpers::ClearLobbyHoveredAI)
        ClearLobbyHoveredAI;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(DisplayElementID displayElementID, dword elementState), false,
            Address::SHC_3BB0A8C1_0x004AF650, &OpenSHC::UI::Helpers::CheckDisplayElementByIDAndSetForUnlimitedDisplay)
        CheckDisplayElementByIDAndSetForUnlimitedDisplay;

        MACRO_FUNCTION_RESOLVER(BOOLEnum(__cdecl*)(DisplayElementID displayElementID), false,
            Address::SHC_3BB0A8C1_0x004AF6E0, &OpenSHC::UI::Helpers::GetIfDisplayElementStateNotZero)
        GetIfDisplayElementStateNotZero;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004B8200, &OpenSHC::UI::Helpers::SumUnitPoints)
        SumUnitPoints;

        MACRO_FUNCTION_RESOLVER(undefined4(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004BC620,
            &OpenSHC::UI::Helpers::GetCurrentTutorialStep)
        GetCurrentTutorialStep;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, BuildingType buildingType), false,
            Address::SHC_3BB0A8C1_0x004BC690, &OpenSHC::UI::Helpers::SetTutorialBuildingActionState)
        SetTutorialBuildingActionState;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004D7200, &OpenSHC::UI::Helpers::ResetEventStatusUnk)
        ResetEventStatusUnk;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(ushort color), false, Address::SHC_3BB0A8C1_0x004DA360,
            &OpenSHC::UI::Helpers::ColorEntireScreen)
        ColorEntireScreen;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int loadedMenuStringIndex, int xPos, int yPos, int maxWidth, uint color,
                                    int fontSize, BOOLEnum isSingleLine),
            false, Address::SHC_3BB0A8C1_0x004DA670, &OpenSHC::UI::Helpers::DrawLoadedMenuStringHelper)
        DrawLoadedMenuStringHelper;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int loadedMenuStringIndex, int xPos, int yPos, int maxWidth, uint color,
                                    int fontSize, BOOLEnum isSingleLine, int blendStrength),
            false, Address::SHC_3BB0A8C1_0x004DA6E0, &OpenSHC::UI::Helpers::DrawLoadedMenuStringHelperWithBlending)
        DrawLoadedMenuStringHelperWithBlending;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(char* textToStore), false, Address::SHC_3BB0A8C1_0x004DA750,
            &OpenSHC::UI::Helpers::StoreStringInMenuStringArray)
        StoreStringInMenuStringArray;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(char* filename), false, Address::SHC_3BB0A8C1_0x004DAF50,
            &OpenSHC::UI::Helpers::LoadScoresFileToMemory)
        LoadScoresFileToMemory;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(char* param_1, int param_2), false, Address::SHC_3BB0A8C1_0x004E1810,
            &OpenSHC::UI::Helpers::WriteMissionToScoresFile)
        WriteMissionToScoresFile;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x0057B9C0,
            &OpenSHC::UI::Helpers::PlayJokeVideoBasedOnCurrentTimeAndPlayTime)
        PlayJokeVideoBasedOnCurrentTimeAndPlayTime;

    } // namespace Helpers_Func
} // namespace UI
} // namespace OpenSHC
