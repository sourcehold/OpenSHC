/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Global.func.hpp'
*/

#pragma once

#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Global.hpp"
#include "OpenSHC/Map/Buildings/BuildingFailReasonEnum.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Units/EuroRecruitableState.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Rendering/Enums/DirectDrawStatus.hpp"
#include "OpenSHC/UI/DisplayElement.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "WinDef.h"
#include "crtdefs.h"
#include "ddraw.h"
#include "dplay.h"
#include "winnt.h"
namespace OpenSHC {
namespace Global_Func {

    using OpenSHC::Game::Resources::ResourceType;
    using OpenSHC::Map::Buildings::BuildingFailReasonEnum;
    using OpenSHC::Map::Buildings::BuildingType;
    using OpenSHC::Map::Units::EuroRecruitableState;
    using OpenSHC::Map::Units::States::UnitState;
    using OpenSHC::Rendering::Enums::DirectDrawStatus;
    using OpenSHC::UI::DisplayElement;
    using OpenSHC::UI::Enums::DisplayElementID;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004038A0, &OpenSHC::Global::SetCurrentEntityID3000)
    SetCurrentEntityID3000;

    MACRO_FUNCTION_RESOLVER(uint(__cdecl*)(int param_1, int x, int y, int param_4, int param_5), false,
        Address::SHC_3BB0A8C1_0x00405130, &OpenSHC::Global::SomeFireSpreadFunction)
    SomeFireSpreadFunction;

    MACRO_FUNCTION_RESOLVER(
        uint(__cdecl*)(int playerID, int miniTileX, int miniTileY, int tileHeightMin8, int two, int fireIntensity),
        false, Address::SHC_3BB0A8C1_0x004052E0, &OpenSHC::Global::IgniteFireAtMiniTile)
    IgniteFireAtMiniTile;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int playerID, int x, int y, int height, int param_5, int param_6), false,
        Address::SHC_3BB0A8C1_0x004054E0, &OpenSHC::Global::AFireSpreadFunction)
    AFireSpreadFunction;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int playerID, int x, int y, int height, int param_5), false,
        Address::SHC_3BB0A8C1_0x00407160, &OpenSHC::Global::SetPlaceOnFire)
    SetPlaceOnFire;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0041A460,
        &OpenSHC::Global::DestroyDrawbridgesInFirst10Buildings)
    DestroyDrawbridgesInFirst10Buildings;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0041A620, &OpenSHC::Global::ClearBuildings1000AndHigher)
    ClearBuildings1000AndHigher;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00424BD0, &OpenSHC::Global::LoadTGX_shc_back)
    LoadTGX_shc_back;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00424BE0, &OpenSHC::Global::DrawOuterMenuBorder)
    DrawOuterMenuBorder;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00427180, &OpenSHC::Global::MainMenu_Unknown21_Prepare)
    MainMenu_Unknown21_Prepare;

    MACRO_FUNCTION_RESOLVER(BOOLEnum(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00427210,
        &OpenSHC::Global::AModalDialogIsActiveButIsNotQuitting)
    AModalDialogIsActiveButIsNotQuitting;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004274F0, &OpenSHC::Global::InitSkirmishLobbyData)
    InitSkirmishLobbyData;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int playerID), false, Address::SHC_3BB0A8C1_0x00428050,
        &OpenSHC::Global::ResetAiVariationArrayValue)
    ResetAiVariationArrayValue;

    MACRO_FUNCTION_RESOLVER(
        void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00428480, &OpenSHC::Global::PutPlayerIntoRandomSlot)
    PutPlayerIntoRandomSlot;

    MACRO_FUNCTION_RESOLVER(
        void(__cdecl*)(int playerID), false, Address::SHC_3BB0A8C1_0x004285C0, &OpenSHC::Global::RemovePositionOfPlayer)
    RemovePositionOfPlayer;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00429650, &OpenSHC::Global::CallbackSetMultiplayerSpeedLevel)
    CallbackSetMultiplayerSpeedLevel;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00429710,
        &OpenSHC::Global::SetupSkirmishBalanceAndOrIntensity)
    SetupSkirmishBalanceAndOrIntensity;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0042A8E0, &OpenSHC::Global::SetAIPlayerNickNames)
    SetAIPlayerNickNames;

    MACRO_FUNCTION_RESOLVER(
        int(__cdecl*)(int playerID), false, Address::SHC_3BB0A8C1_0x0042AC60, &OpenSHC::Global::GetPlayerPosition)
    GetPlayerPosition;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0042C190, &OpenSHC::Global::ClearSiegeInformationArray2)
    ClearSiegeInformationArray2;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x0042C620,
        &OpenSHC::Global::LaunchSinglePlayerGameUnk)
    LaunchSinglePlayerGameUnk;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0042F010, &OpenSHC::Global::InitializeBasicMap)
    InitializeBasicMap;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00431990, &OpenSHC::Global::ResetSomeValuesFunctionUnk)
    ResetSomeValuesFunctionUnk;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(BuildingFailReasonEnum param_1), false, Address::SHC_3BB0A8C1_0x004380E0,
        &OpenSHC::Global::PlayPlacementWarning)
    PlayPlacementWarning;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004381D0, &OpenSHC::Global::PlaceUnit)
    PlaceUnit;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int buildingIndexUnk), false, Address::SHC_3BB0A8C1_0x00439730,
        &OpenSHC::Global::HandleBuildingSelectionSpeech)
    HandleBuildingSelectionSpeech;

    MACRO_FUNCTION_RESOLVER(HCURSOR(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00440430,
        &OpenSHC::Global::SetCursorDependingOnProgramState)
    SetCursorDependingOnProgramState;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004410D0,
        &OpenSHC::Global::DisplayMapDescriptionAndAllocatePlayersToSlots)
    DisplayMapDescriptionAndAllocatePlayersToSlots;

    MACRO_FUNCTION_RESOLVER(
        void(__cdecl*)(int whichCastle), false, Address::SHC_3BB0A8C1_0x00441270, &OpenSHC::Global::LaunchSkirmishGame)
    LaunchSkirmishGame;

    MACRO_FUNCTION_RESOLVER(
        int(__cdecl*)(int playerID), false, Address::SHC_3BB0A8C1_0x0044A830, &OpenSHC::Global::ComputePlayerPoints1)
    ComputePlayerPoints1;

    MACRO_FUNCTION_RESOLVER(
        int(__cdecl*)(int playerID), false, Address::SHC_3BB0A8C1_0x0044B680, &OpenSHC::Global::ComputePlayerRanking)
    ComputePlayerRanking;

    MACRO_FUNCTION_RESOLVER(
        int(__cdecl*)(int rankingPosition), false, Address::SHC_3BB0A8C1_0x0044B760, &OpenSHC::Global::GetPlayerAtRank)
    GetPlayerAtRank;

    MACRO_FUNCTION_RESOLVER(
        int(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0044B7D0, &OpenSHC::Global::IfAiGreatestLordGetAiType)
    IfAiGreatestLordGetAiType;

    MACRO_FUNCTION_RESOLVER(
        int(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0044B800, &OpenSHC::Global::GetLowestRankedAlivePlayer)
    GetLowestRankedAlivePlayer;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0044C400, &OpenSHC::Global::ComputeCurrentPlayerRanking)
    ComputeCurrentPlayerRanking;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0044C410, &OpenSHC::Global::PlaySFXVoices)
    PlaySFXVoices;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0044E510, &OpenSHC::Global::InitBlendFilterArraysUnk)
    InitBlendFilterArraysUnk;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(wchar_t* destination, wchar_t* format, ...), false,
        Address::SHC_3BB0A8C1_0x0045D060, &OpenSHC::Global::PrintToDestination)
    PrintToDestination;

    MACRO_FUNCTION_RESOLVER(EuroRecruitableState(__cdecl*)(int barrackUnitIdUnk), false,
        Address::SHC_3BB0A8C1_0x00464DA0, &OpenSHC::Global::IsEuroUnitRecruitableUnk)
    IsEuroUnitRecruitableUnk;

    MACRO_FUNCTION_RESOLVER(
        int(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00464E80, &OpenSHC::Global::GetUnitRecruitPermission)
    GetUnitRecruitPermission;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int playerID, int unitType, undefined4 recruitmentBuildingID), false,
        Address::SHC_3BB0A8C1_0x00464EF0, &OpenSHC::Global::ProcessRecruitUnit)
    ProcessRecruitUnit;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00465080, &OpenSHC::Global::CheckIfEnoughGoldForLadderman)
    CheckIfEnoughGoldForLadderman;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004650A0, &OpenSHC::Global::CheckIfEnoughGoldForMonk)
    CheckIfEnoughGoldForMonk;

    MACRO_FUNCTION_RESOLVER(
        BOOLEnum(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004650C0, &OpenSHC::Global::CheckGoldResource)
    CheckGoldResource;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004650F0, &OpenSHC::Global::CheckIfEnoughGoldForTunneler)
    CheckIfEnoughGoldForTunneler;

    MACRO_FUNCTION_RESOLVER(
        void(__cdecl*)(undefined4 playerID, int buildingID, ushort producedItemType, int buildingUID), false,
        Address::SHC_3BB0A8C1_0x004652A0, &OpenSHC::Global::SetBuildingProductionType)
    SetBuildingProductionType;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int playerID, int taxesSetting), false, Address::SHC_3BB0A8C1_0x00465800,
        &OpenSHC::Global::ChangeTaxes)
    ChangeTaxes;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int playerID, int rationsSetting), false, Address::SHC_3BB0A8C1_0x00465890,
        &OpenSHC::Global::ChangeRations)
    ChangeRations;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int state, ResourceType resource), false, Address::SHC_3BB0A8C1_0x00465DB0,
        &OpenSHC::Global::SetStorageMarketFailState)
    SetStorageMarketFailState;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int playerID, int buyOrSell, ResourceType resourceType), false,
        Address::SHC_3BB0A8C1_0x00465E60, &OpenSHC::Global::ProcessBuyOrSell)
    ProcessBuyOrSell;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, int param_2), false, Address::SHC_3BB0A8C1_0x00465F20,
        &OpenSHC::Global::TryAcquireAmmunitionOrPlanToBuyStone)
    TryAcquireAmmunitionOrPlanToBuyStone;

    MACRO_FUNCTION_RESOLVER(short*(__cdecl*)(int playerID, int param_2), false, Address::SHC_3BB0A8C1_0x00465F90,
        &OpenSHC::Global::SelectionReplenishAmmo)
    SelectionReplenishAmmo;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int playerID, int buildingType), false, Address::SHC_3BB0A8C1_0x004660F0,
        &OpenSHC::Global::ProcessBuildingSleepUpdate)
    ProcessBuildingSleepUpdate;

    MACRO_FUNCTION_RESOLVER(
        void(__cdecl*)(int playerID, int buildingID, int requiredWood, int requiredStone, int gameObjectID), false,
        Address::SHC_3BB0A8C1_0x00466260, &OpenSHC::Global::ProcessTowerRepair)
    ProcessTowerRepair;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, int buildingID, int buildingUID), false,
        Address::SHC_3BB0A8C1_0x00466430, &OpenSHC::Global::ReleaseDogs2)
    ReleaseDogs2;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00466E00,
        &OpenSHC::Global::SetEnoughGoldForRequestedUnitToTrueUnk)
    SetEnoughGoldForRequestedUnitToTrueUnk;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00467890, &OpenSHC::Global::SetSomeColorsUnk)
    SetSomeColorsUnk;

    MACRO_FUNCTION_RESOLVER(HRESULT(__stdcall*)(DDSURFACEDESC* displayDesc, LPVOID userParam), false,
        Address::SHC_3BB0A8C1_0x00467BC0, &OpenSHC::Global::EnumDisplayModesCallback)
    EnumDisplayModesCallback;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00469F10, &OpenSHC::Global::DoNothing)
    DoNothing;

    MACRO_FUNCTION_RESOLVER(char*(__cdecl*)(char* mapName, int* hardcodedMapDescriptionGroupNum), false,
        Address::SHC_3BB0A8C1_0x0046D390, &OpenSHC::Global::GetStringBasedOnHardcodedMaps)
    GetStringBasedOnHardcodedMaps;

    MACRO_FUNCTION_RESOLVER(DirectDrawStatus(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0046F4F0,
        &OpenSHC::Global::DetectDXVersionByLoadingDDRAW)
    DetectDXVersionByLoadingDDRAW;

    MACRO_FUNCTION_RESOLVER(
        byte(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0046F570, &OpenSHC::Global::TestOSVersion)
    TestOSVersion;

    MACRO_FUNCTION_RESOLVER(BOOL(__stdcall*)(LPCGUID lpguidSP, LPVOID lpConnection, DWORD dwConnectionSize,
                                DPNAME* lpName, DWORD dwFlags, LPVOID lpContext),
        false, Address::SHC_3BB0A8C1_0x0047D5B0, &OpenSHC::Global::EnumConnectionsCallback)
    EnumConnectionsCallback;

    MACRO_FUNCTION_RESOLVER(
        bool(__stdcall*)(DPSESSIONDESC2* lpThisSD, LPDWORD lpdwTimeOut, DWORD dwFlags, LPVOID lpContext), false,
        Address::SHC_3BB0A8C1_0x0047DF40, &OpenSHC::Global::EnumSessionsCallback_addSession_async)
    EnumSessionsCallback_addSession_async;

    MACRO_FUNCTION_RESOLVER(BOOLEnum(__stdcall*)(int* param_1, undefined4 param_2, char* param_3), false,
        Address::SHC_3BB0A8C1_0x0047E160, &OpenSHC::Global::DirectPlayModemRelated_MemoryAllocationFunction)
    DirectPlayModemRelated_MemoryAllocationFunction;

    MACRO_FUNCTION_RESOLVER(
        int(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0047EEB0, &OpenSHC::Global::ComputeSomeHashOnUnitArray)
    ComputeSomeHashOnUnitArray;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(char* dest, size_t size, undefined4 playerID), false,
        Address::SHC_3BB0A8C1_0x00488480, &OpenSHC::Global::MemCopyFromParameter)
    MemCopyFromParameter;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00493050, &OpenSHC::Global::SetupPreviewMinimapDataUnk)
    SetupPreviewMinimapDataUnk;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00495840, &OpenSHC::Global::ProgressBarRelated)
    ProgressBarRelated;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00496E40, &OpenSHC::Global::ClearPathFindingTileMaps)
    ClearPathFindingTileMaps;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, int param_2), false, Address::SHC_3BB0A8C1_0x004AD110,
        &OpenSHC::Global::ProcessAllyAcceptsRequest)
    ProcessAllyAcceptsRequest;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, int param_2), false, Address::SHC_3BB0A8C1_0x004AD1E0,
        &OpenSHC::Global::ProcessAllyDeniesRequest2)
    ProcessAllyDeniesRequest2;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int targetPlayerID, int playerID, int requestedByPlayerID, int param_4),
        false, Address::SHC_3BB0A8C1_0x004AD2F0, &OpenSHC::Global::ProcessAllyRequestAttackDefense)
    ProcessAllyRequestAttackDefense;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int askedPlayerID, int param_2, int amount, int askee), false,
        Address::SHC_3BB0A8C1_0x004AD7C0, &OpenSHC::Global::ProcessAllyRequestingGoods)
    ProcessAllyRequestingGoods;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ResourceType param_2, int param_3, int param_4), false,
        Address::SHC_3BB0A8C1_0x004ADDD0, &OpenSHC::Global::ProcessAllyGoodsRequest)
    ProcessAllyGoodsRequest;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, int param_2), false, Address::SHC_3BB0A8C1_0x004AE010,
        &OpenSHC::Global::ProcessAllyDeniesRequest)
    ProcessAllyDeniesRequest;

    MACRO_FUNCTION_RESOLVER(DisplayElement*(__cdecl*)(int elementID), false, Address::SHC_3BB0A8C1_0x004AF630,
        &OpenSHC::Global::FindDisplayElementWithID)
    FindDisplayElementWithID;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(DisplayElementID displayElementID, dword elementState), false,
        Address::SHC_3BB0A8C1_0x004AF650, &OpenSHC::Global::CheckDisplayElementByIDAndSetForUnlimitedDisplay)
    CheckDisplayElementByIDAndSetForUnlimitedDisplay;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(DisplayElementID elementId, dword elementState, int displayDuration), false,
        Address::SHC_3BB0A8C1_0x004AF680, &OpenSHC::Global::ActivateGameSpeedAndResourceLackDisplayElementUnk)
    ActivateGameSpeedAndResourceLackDisplayElementUnk;

    MACRO_FUNCTION_RESOLVER(BOOLEnum(__cdecl*)(DisplayElementID displayElementID), false,
        Address::SHC_3BB0A8C1_0x004AF6E0, &OpenSHC::Global::GetIfDisplayElementStateNotZero)
    GetIfDisplayElementStateNotZero;

    MACRO_FUNCTION_RESOLVER(LRESULT(__stdcall*)(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam), false,
        Address::SHC_3BB0A8C1_0x004B2AE0, &OpenSHC::Global::WindowMsgProcessingFunc)
    WindowMsgProcessingFunc;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004B8200, &OpenSHC::Global::SumUnitPoints)
    SumUnitPoints;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, BuildingType buildingType), false,
        Address::SHC_3BB0A8C1_0x004BC690, &OpenSHC::Global::SetTutorialBuildingActionState)
    SetTutorialBuildingActionState;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004BC770,
        &OpenSHC::Global::SetTutorialHintActiveWithTimestamp)
    SetTutorialHintActiveWithTimestamp;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int skirmishTrailMission), false, Address::SHC_3BB0A8C1_0x004C68D0,
        &OpenSHC::Global::SetupSkirmishMode)
    SetupSkirmishMode;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int missionID), false, Address::SHC_3BB0A8C1_0x004C6B20,
        &OpenSHC::Global::LoadSkirmishCampaignData)
    LoadSkirmishCampaignData;

    MACRO_FUNCTION_RESOLVER(int(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004C6CD0, &OpenSHC::Global::StoreTime)
    StoreTime;

    MACRO_FUNCTION_RESOLVER(BOOLEnum(__cdecl*)(int score), false, Address::SHC_3BB0A8C1_0x004D1700,
        &OpenSHC::Global::StoreCurrentGameIntoTemporarySKMasterEntry)
    StoreCurrentGameIntoTemporarySKMasterEntry;

    MACRO_FUNCTION_RESOLVER(
        void(__cdecl*)(int score), false, Address::SHC_3BB0A8C1_0x004D52A0, &OpenSHC::Global::StoreGameIntoSKMasters)
    StoreGameIntoSKMasters;

    MACRO_FUNCTION_RESOLVER(
        int(__cdecl*)(int playerID), false, Address::SHC_3BB0A8C1_0x004D5780, &OpenSHC::Global::ComputeSkMasterScore)
    ComputeSkMasterScore;

    MACRO_FUNCTION_RESOLVER(
        void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004D7200, &OpenSHC::Global::ResetEventStatusUnk)
    ResetEventStatusUnk;

    MACRO_FUNCTION_RESOLVER(
        void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004D9D90, &OpenSHC::Global::TacticalPowersFill)
    TacticalPowersFill;

    MACRO_FUNCTION_RESOLVER(
        void(__cdecl*)(ushort color), false, Address::SHC_3BB0A8C1_0x004DA360, &OpenSHC::Global::ColorEntireScreen)
    ColorEntireScreen;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int loadedMenuStringIndex, int xPos, int yPos, int maxWidth, uint color,
                                int fontSize, BOOLEnum isSingleLine),
        false, Address::SHC_3BB0A8C1_0x004DA670, &OpenSHC::Global::DrawLoadedMenuStringHelper)
    DrawLoadedMenuStringHelper;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int loadedMenuStringIndex, int xPos, int yPos, int maxWidth, uint color,
                                int fontSize, BOOLEnum isSingleLine, int blendStrength),
        false, Address::SHC_3BB0A8C1_0x004DA6E0, &OpenSHC::Global::DrawLoadedMenuStringHelperWithBlending)
    DrawLoadedMenuStringHelperWithBlending;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(char* textToStore), false, Address::SHC_3BB0A8C1_0x004DA750,
        &OpenSHC::Global::StoreStringInMenuStringArray)
    StoreStringInMenuStringArray;

    MACRO_FUNCTION_RESOLVER(
        void(__cdecl*)(int state, undefined4 xSpace, undefined4 param_3, undefined4 ySpace, undefined4 someX,
            undefined4 someY, undefined4 param_7, int param_8, undefined4 param_9),
        false, Address::SHC_3BB0A8C1_0x004DAD40, &OpenSHC::Global::InsertElementIntoAnArrayAt_ec0348)
    InsertElementIntoAnArrayAt_ec0348;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4,
                                undefined4 param_5, undefined4 param_6, undefined4 param_7, undefined4 param_8),
        false, Address::SHC_3BB0A8C1_0x004DAE00, &OpenSHC::Global::InsertElementIntoArrayAt_ec0348_3)
    InsertElementIntoArrayAt_ec0348_3;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, undefined4 xSpace, undefined4 param_3, undefined4 param_4,
                                undefined4 ySpace, undefined4 someX, int param_7, undefined4 someY, undefined4 param_9),
        false, Address::SHC_3BB0A8C1_0x004DAE90, &OpenSHC::Global::InsertElementIntoArrayAt_ec0348_2)
    InsertElementIntoArrayAt_ec0348_2;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(char* filename), false, Address::SHC_3BB0A8C1_0x004DAF50,
        &OpenSHC::Global::LoadScoresFileToMemory)
    LoadScoresFileToMemory;

    MACRO_FUNCTION_RESOLVER(
        int(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004DB210, &OpenSHC::Global::PrepareHistoryBook)
    PrepareHistoryBook;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(char* param_1, int param_2), false, Address::SHC_3BB0A8C1_0x004E1810,
        &OpenSHC::Global::WriteMissionToScoresFile)
    WriteMissionToScoresFile;

    MACRO_FUNCTION_RESOLVER(
        int(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004EDD00, &OpenSHC::Global::ComputeLargestSeparateArea)
    ComputeLargestSeparateArea;

    MACRO_FUNCTION_RESOLVER(
        void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x0051D5D0, &OpenSHC::Global::DecrementTileMap1104)
    DecrementTileMap1104;

    MACRO_FUNCTION_RESOLVER(
        void(__cdecl*)(int unitID), false, Address::SHC_3BB0A8C1_0x00530760, &OpenSHC::Global::DetachLadderman)
    DetachLadderman;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int unitID, BOOLEnum updateAV), false, Address::SHC_3BB0A8C1_0x00530B40,
        &OpenSHC::Global::IncrementAndOptionalUpdateAVValueRelated)
    IncrementAndOptionalUpdateAVValueRelated;

    MACRO_FUNCTION_RESOLVER(BOOLEnum(__cdecl*)(int unitID, UnitState nextUnitState), false,
        Address::SHC_3BB0A8C1_0x00530C40, &OpenSHC::Global::ConsiderHavingABreakNowUnk)
    ConsiderHavingABreakNowUnk;

    MACRO_FUNCTION_RESOLVER(undefined4(__cdecl*)(int unitID, int shouldFindNewGoodThing, int param_3), false,
        Address::SHC_3BB0A8C1_0x00530CF0, &OpenSHC::Global::SetStateToFreetimeWalking)
    SetStateToFreetimeWalking;

    MACRO_FUNCTION_RESOLVER(bool(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00530D50,
        &OpenSHC::Global::CheckUnitProductionPaused)
    CheckUnitProductionPaused;

    MACRO_FUNCTION_RESOLVER(int(__cdecl*)(int unitID, int goodsCount, BOOLEnum boost), false,
        Address::SHC_3BB0A8C1_0x00530D70, &OpenSHC::Global::ComputeGoodsProduced)
    ComputeGoodsProduced;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00530E00, &OpenSHC::Global::WarnIfPlayersGranaryIsFull)
    WarnIfPlayersGranaryIsFull;

    MACRO_FUNCTION_RESOLVER(
        uint(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00530EB0, &OpenSHC::Global::PlayStockpileIsFullWarning)
    PlayStockpileIsFullWarning;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00530F20, &OpenSHC::Global::PlayArmoryIsFullWarning)
    PlayArmoryIsFullWarning;

    MACRO_FUNCTION_RESOLVER(
        BOOLEnum(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x0053A020, &OpenSHC::Global::CurrentUnitHasHealer)
    CurrentUnitHasHealer;

    MACRO_FUNCTION_RESOLVER(
        undefined4(__cdecl*)(int unitID), false, Address::SHC_3BB0A8C1_0x00549B30, &OpenSHC::Global::SetRestingForUnit)
    SetRestingForUnit;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0057B9C0,
        &OpenSHC::Global::PlayJokeVideoBasedOnCurrentTimeAndPlayTime)
    PlayJokeVideoBasedOnCurrentTimeAndPlayTime;

    MACRO_FUNCTION_RESOLVER(
        int(__stdcall*)(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd), false,
        Address::SHC_3BB0A8C1_0x0057BE10, &OpenSHC::Global::WinMain)
    WinMain;

    MACRO_FUNCTION_RESOLVER(
        void(__cdecl*)(ulong param_1), false, Address::SHC_3BB0A8C1_0x005816EE, &OpenSHC::Global::SetRNGSeed)
    SetRNGSeed;

    MACRO_FUNCTION_RESOLVER(
        int(__cdecl*)(HANDLE hFile), false, Address::SHC_3BB0A8C1_0x005826FB, &OpenSHC::Global::GetFilePtrPos)
    GetFilePtrPos;

} // namespace Global_Func
} // namespace OpenSHC
