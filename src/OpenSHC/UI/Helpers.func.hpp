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
#include "OpenSHC/UI/Helpers.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "WinDef.h"
namespace OpenSHC {
namespace UI {
    namespace Helpers_Func {

        using OpenSHC::Map::Buildings::BuildingFailReasonEnum;
        using OpenSHC::Map::Buildings::BuildingType;
        using OpenSHC::Map::Units::EuroRecruitableState;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00424BD0, &OpenSHC::UI::Helpers::LoadTGX_shc_back)
        LoadTGX_shc_back;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00427180,
            &OpenSHC::UI::Helpers::MainMenu_Unknown21_Prepare)
        MainMenu_Unknown21_Prepare;

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

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00437CC0,
            &OpenSHC::UI::Helpers::HandleWallTerrainMouseDrag)
        HandleWallTerrainMouseDrag;

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

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00440360, &OpenSHC::UI::Helpers::CountPlayerUnitsByType)
        CountPlayerUnitsByType;

        MACRO_FUNCTION_RESOLVER(HCURSOR(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00440430,
            &OpenSHC::UI::Helpers::SetCursorDependingOnProgramState)
        SetCursorDependingOnProgramState;

        MACRO_FUNCTION_RESOLVER(EuroRecruitableState(__cdecl*)(int barrackUnitIdUnk), false,
            Address::SHC_3BB0A8C1_0x00464DA0, &OpenSHC::UI::Helpers::IsEuroUnitRecruitableUnk)
        IsEuroUnitRecruitableUnk;

        MACRO_FUNCTION_RESOLVER(int(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00464E80,
            &OpenSHC::UI::Helpers::GetUnitRecruitPermission)
        GetUnitRecruitPermission;

        MACRO_FUNCTION_RESOLVER(BOOLEnum(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00465040,
            &OpenSHC::UI::Helpers::HasEnoughGold)
        HasEnoughGold;

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

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00466E10, &OpenSHC::UI::Helpers::DisableMercPostPortraits)
        DisableMercPostPortraits;

        MACRO_FUNCTION_RESOLVER(undefined4(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x0046CF90,
            &OpenSHC::UI::Helpers::TicksSinceCounterStart)
        TicksSinceCounterStart;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00493050,
            &OpenSHC::UI::Helpers::SetupPreviewMinimapDataUnk)
        SetupPreviewMinimapDataUnk;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00495800,
            &OpenSHC::UI::Helpers::ShowProgressBarSaveLoadDialog)
        ShowProgressBarSaveLoadDialog;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004AC650, &OpenSHC::UI::Helpers::BuildEnemyPlayerList)
        BuildEnemyPlayerList;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004AE7C0, &OpenSHC::UI::Helpers::ClearLobbyHoveredAI)
        ClearLobbyHoveredAI;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(uint aiType, int param_2), false, Address::SHC_3BB0A8C1_0x004B7F60,
            &OpenSHC::UI::Helpers::PlayAMessageFromAI)
        PlayAMessageFromAI;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004B8200, &OpenSHC::UI::Helpers::SumUnitPoints)
        SumUnitPoints;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004B8210, &OpenSHC::UI::Helpers::RestoreScenarioGold)
        RestoreScenarioGold;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004B9610,
            &OpenSHC::UI::Helpers::CaptureCurrentTimeToUnknownTime01)
        CaptureCurrentTimeToUnknownTime01;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004BC5F0,
            &OpenSHC::UI::Helpers::InitTutorialStepTransition)
        InitTutorialStepTransition;

        MACRO_FUNCTION_RESOLVER(undefined4(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004BC620,
            &OpenSHC::UI::Helpers::GetCurrentTutorialStep)
        GetCurrentTutorialStep;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004BC630,
            &OpenSHC::UI::Helpers::RecordTutorialPlayerAction)
        RecordTutorialPlayerAction;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, BuildingType buildingType), false,
            Address::SHC_3BB0A8C1_0x004BC690, &OpenSHC::UI::Helpers::SetTutorialBuildingActionState)
        SetTutorialBuildingActionState;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004BC6C0,
            &OpenSHC::UI::Helpers::ResetTutorialActionTrackers)
        ResetTutorialActionTrackers;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004BC770,
            &OpenSHC::UI::Helpers::SetTutorialHintActiveWithTimestamp)
        SetTutorialHintActiveWithTimestamp;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004BD1B0,
            &OpenSHC::UI::Helpers::UpdateTutorialStepAndProgress)
        UpdateTutorialStepAndProgress;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004D6F60,
            &OpenSHC::UI::Helpers::ParseCampaignMapHotspotBitmap)
        ParseCampaignMapHotspotBitmap;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004D7200, &OpenSHC::UI::Helpers::ResetEventStatusUnk)
        ResetEventStatusUnk;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(char* param_1), false, Address::SHC_3BB0A8C1_0x004D8A20,
            &OpenSHC::UI::Helpers::ReadMapHeaderFromFile)
        ReadMapHeaderFromFile;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004D9D90, &OpenSHC::UI::Helpers::TacticalPowersFill)
        TacticalPowersFill;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(ushort color), false, Address::SHC_3BB0A8C1_0x004DA360,
            &OpenSHC::UI::Helpers::ColorEntireScreen)
        ColorEntireScreen;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(char* textToStore), false, Address::SHC_3BB0A8C1_0x004DA750,
            &OpenSHC::UI::Helpers::StoreStringInMenuStringArray)
        StoreStringInMenuStringArray;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(char* filename), false, Address::SHC_3BB0A8C1_0x004DAF50,
            &OpenSHC::UI::Helpers::LoadScoresFileToMemory)
        LoadScoresFileToMemory;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(undefined4 param_1, undefined4 param_2), false,
            Address::SHC_3BB0A8C1_0x004DB180, &OpenSHC::UI::Helpers::BuildIntroLogoSequence)
        BuildIntroLogoSequence;

        MACRO_FUNCTION_RESOLVER(
            int(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004DB210, &OpenSHC::UI::Helpers::PrepareHistoryBook)
        PrepareHistoryBook;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int storedMenuStringIndex, undefined4 param_2, undefined4 param_3,
                                    int allowedWidth, undefined4 param_5, int fontSize),
            false, Address::SHC_3BB0A8C1_0x004DB300, &OpenSHC::UI::Helpers::TrimStoredMenuString)
        TrimStoredMenuString;

        MACRO_FUNCTION_RESOLVER(undefined4(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004DC140,
            &OpenSHC::UI::Helpers::FindCampaignMapHotspotAtMouse)
        FindCampaignMapHotspotAtMouse;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004DC1C0,
            &OpenSHC::UI::Helpers::BuildExtremeDemoIntroScript)
        BuildExtremeDemoIntroScript;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(char* param_1, int param_2), false, Address::SHC_3BB0A8C1_0x004E1810,
            &OpenSHC::UI::Helpers::WriteMissionToScoresFile)
        WriteMissionToScoresFile;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x0057B9C0,
            &OpenSHC::UI::Helpers::PlayJokeVideoBasedOnCurrentTimeAndPlayTime)
        PlayJokeVideoBasedOnCurrentTimeAndPlayTime;

    } // namespace Helpers_Func
} // namespace UI
} // namespace OpenSHC
