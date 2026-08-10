/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Global.hpp'
*/

#pragma once

#include "OpenSHC/Game/Resources/ResourceType.hpp"
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
namespace Global {

    using OpenSHC::Game::Resources::ResourceType;
    using OpenSHC::Map::Buildings::BuildingFailReasonEnum;
    using OpenSHC::Map::Buildings::BuildingType;
    using OpenSHC::Map::Units::EuroRecruitableState;
    using OpenSHC::Map::Units::States::UnitState;
    using OpenSHC::Rendering::Enums::DirectDrawStatus;
    using OpenSHC::UI::DisplayElement;
    using OpenSHC::UI::Enums::DisplayElementID;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    void __stdcall SetCurrentEntityID3000();

    uint __cdecl SomeFireSpreadFunction(int param_1, int x, int y, int param_4, int param_5);

    uint __cdecl IgniteFireAtMiniTile(
        int playerID, int miniTileX, int miniTileY, int tileHeightMin8, int two, int fireIntensity);

    void __cdecl AFireSpreadFunction(int playerID, int x, int y, int height, int param_5, int param_6);

    void __cdecl SetPlaceOnFire(int playerID, int x, int y, int height, int param_5);

    void __stdcall DestroyDrawbridgesInFirst10Buildings();

    void __stdcall ClearBuildings1000AndHigher();

    void __stdcall LoadTGX_shc_back();

    void __stdcall DrawOuterMenuBorder();

    void __stdcall MainMenu_Unknown21_Prepare();

    BOOLEnum __stdcall AModalDialogIsActiveButIsNotQuitting();

    void __stdcall InitSkirmishLobbyData();

    void __cdecl ResetAiVariationArrayValue(int playerID);

    void __cdecl PutPlayerIntoRandomSlot(int param_1);

    void __cdecl RemovePositionOfPlayer(int playerID);

    void __stdcall CallbackSetMultiplayerSpeedLevel();

    void __stdcall SetupSkirmishBalanceAndOrIntensity();

    void __stdcall SetAIPlayerNickNames();

    int __cdecl GetPlayerPosition(int playerID);

    void __stdcall ClearSiegeInformationArray2();

    void __cdecl LaunchSinglePlayerGameUnk(int param_1);

    void __stdcall InitializeBasicMap();

    void __stdcall ResetSomeValuesFunctionUnk();

    void __cdecl PlayPlacementWarning(BuildingFailReasonEnum param_1);

    void __stdcall PlaceUnit();

    void __cdecl HandleBuildingSelectionSpeech(int buildingIndexUnk);

    HCURSOR __stdcall SetCursorDependingOnProgramState();

    void __stdcall DisplayMapDescriptionAndAllocatePlayersToSlots();

    void __cdecl LaunchSkirmishGame(int whichCastle);

    int __cdecl ComputePlayerPoints1(int playerID);

    int __cdecl ComputePlayerRanking(int playerID);

    int __cdecl GetPlayerAtRank(int rankingPosition);

    int __stdcall IfAiGreatestLordGetAiType();

    int __stdcall GetLowestRankedAlivePlayer();

    void __stdcall ComputeCurrentPlayerRanking();

    void __stdcall PlaySFXVoices();

    void __stdcall InitBlendFilterArraysUnk();

    void __cdecl PrintToDestination(wchar_t* destination, wchar_t* format, ...);

    EuroRecruitableState __cdecl IsEuroUnitRecruitableUnk(int barrackUnitIdUnk);

    int __cdecl GetUnitRecruitPermission(int param_1);

    void __cdecl ProcessRecruitUnit(int playerID, int unitType, undefined4 recruitmentBuildingID);

    void __stdcall CheckIfEnoughGoldForLadderman();

    void __stdcall CheckIfEnoughGoldForMonk();

    BOOLEnum __cdecl CheckGoldResource(int param_1);

    void __stdcall CheckIfEnoughGoldForTunneler();

    void __cdecl SetBuildingProductionType(
        undefined4 playerID, int buildingID, ushort producedItemType, int buildingUID);

    void __cdecl ChangeTaxes(int playerID, int taxesSetting);

    void __cdecl ChangeRations(int playerID, int rationsSetting);

    void __cdecl SetStorageMarketFailState(int state, ResourceType resource);

    void __cdecl ProcessBuyOrSell(int playerID, int buyOrSell, ResourceType resourceType);

    void __cdecl TryAcquireAmmunitionOrPlanToBuyStone(int param_1, int param_2);

    short* __cdecl SelectionReplenishAmmo(int playerID, int param_2);

    void __cdecl ProcessBuildingSleepUpdate(int playerID, int buildingType);

    void __cdecl ProcessTowerRepair(
        int playerID, int buildingID, int requiredWood, int requiredStone, int gameObjectID);

    void __cdecl ReleaseDogs2(int param_1, int buildingID, int buildingUID);

    void __stdcall SetEnoughGoldForRequestedUnitToTrueUnk();

    void __stdcall SetSomeColorsUnk();

    HRESULT __stdcall EnumDisplayModesCallback(DDSURFACEDESC* displayDesc, LPVOID userParam);

    void __stdcall DoNothing();

    char* __cdecl GetStringBasedOnHardcodedMaps(char* mapName, int* hardcodedMapDescriptionGroupNum);

    DirectDrawStatus __stdcall DetectDXVersionByLoadingDDRAW();

    byte __stdcall TestOSVersion();

    BOOL __stdcall EnumConnectionsCallback(
        LPCGUID lpguidSP, LPVOID lpConnection, DWORD dwConnectionSize, DPNAME* lpName, DWORD dwFlags, LPVOID lpContext);

    bool __stdcall EnumSessionsCallback_addSession_async(
        DPSESSIONDESC2* lpThisSD, LPDWORD lpdwTimeOut, DWORD dwFlags, LPVOID lpContext);

    BOOLEnum __stdcall DirectPlayModemRelated_MemoryAllocationFunction(int* param_1, undefined4 param_2, char* param_3);

    int __stdcall ComputeSomeHashOnUnitArray();

    void __cdecl MemCopyFromParameter(char* dest, size_t size, undefined4 playerID);

    void __stdcall SetupPreviewMinimapDataUnk();

    void __stdcall ProgressBarRelated();

    void __stdcall ClearPathFindingTileMaps();

    void __cdecl ProcessAllyAcceptsRequest(int param_1, int param_2);

    void __cdecl ProcessAllyDeniesRequest2(int param_1, int param_2);

    void __cdecl ProcessAllyRequestAttackDefense(
        int targetPlayerID, int playerID, int requestedByPlayerID, int param_4);

    void __cdecl ProcessAllyRequestingGoods(int askedPlayerID, int param_2, int amount, int askee);

    void __cdecl ProcessAllyGoodsRequest(int param_1, ResourceType param_2, int param_3, int param_4);

    void __cdecl ProcessAllyDeniesRequest(int param_1, int param_2);

    DisplayElement* __cdecl FindDisplayElementWithID(int elementID);

    void __cdecl CheckDisplayElementByIDAndSetForUnlimitedDisplay(
        DisplayElementID displayElementID, dword elementState);

    void __cdecl ActivateGameSpeedAndResourceLackDisplayElementUnk(
        DisplayElementID elementId, dword elementState, int displayDuration);

    BOOLEnum __cdecl GetIfDisplayElementStateNotZero(DisplayElementID displayElementID);

    LRESULT __stdcall WindowMsgProcessingFunc(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam);

    void __cdecl SumUnitPoints();

    void __cdecl SetTutorialBuildingActionState(int param_1, BuildingType buildingType);

    void __stdcall SetTutorialHintActiveWithTimestamp();

    void __cdecl SetupSkirmishMode(int skirmishTrailMission);

    void __cdecl LoadSkirmishCampaignData(int missionID);

    int __stdcall StoreTime();

    BOOLEnum __cdecl StoreCurrentGameIntoTemporarySKMasterEntry(int score);

    void __cdecl StoreGameIntoSKMasters(int score);

    int __cdecl ComputeSkMasterScore(int playerID);

    void __cdecl ResetEventStatusUnk();

    void __cdecl TacticalPowersFill();

    void __cdecl ColorEntireScreen(ushort color);

    void __cdecl DrawLoadedMenuStringHelper(
        int loadedMenuStringIndex, int xPos, int yPos, int maxWidth, uint color, int fontSize, BOOLEnum isSingleLine);

    void __cdecl DrawLoadedMenuStringHelperWithBlending(int loadedMenuStringIndex, int xPos, int yPos, int maxWidth,
        uint color, int fontSize, BOOLEnum isSingleLine, int blendStrength);

    void __cdecl StoreStringInMenuStringArray(char* textToStore);

    void __cdecl InsertElementIntoAnArrayAt_ec0348(int state, undefined4 xSpace, undefined4 param_3, undefined4 ySpace,
        undefined4 someX, undefined4 someY, undefined4 param_7, int param_8, undefined4 param_9);

    void __cdecl InsertElementIntoArrayAt_ec0348_3(int param_1, undefined4 param_2, undefined4 param_3,
        undefined4 param_4, undefined4 param_5, undefined4 param_6, undefined4 param_7, undefined4 param_8);

    void __cdecl InsertElementIntoArrayAt_ec0348_2(int param_1, undefined4 xSpace, undefined4 param_3,
        undefined4 param_4, undefined4 ySpace, undefined4 someX, int param_7, undefined4 someY, undefined4 param_9);

    void __cdecl LoadScoresFileToMemory(char* filename);

    int __cdecl PrepareHistoryBook();

    void __cdecl WriteMissionToScoresFile(char* param_1, int param_2);

    int __stdcall ComputeLargestSeparateArea();

    void __cdecl DecrementTileMap1104();

    void __cdecl DetachLadderman(int unitID);

    void __cdecl IncrementAndOptionalUpdateAVValueRelated(int unitID, BOOLEnum updateAV);

    BOOLEnum __cdecl ConsiderHavingABreakNowUnk(int unitID, UnitState nextUnitState);

    undefined4 __cdecl SetStateToFreetimeWalking(int unitID, int shouldFindNewGoodThing, int param_3);

    bool __cdecl CheckUnitProductionPaused(int param_1);

    int __cdecl ComputeGoodsProduced(int unitID, int goodsCount, BOOLEnum boost);

    void __stdcall WarnIfPlayersGranaryIsFull();

    uint __stdcall PlayStockpileIsFullWarning();

    void __stdcall PlayArmoryIsFullWarning();

    BOOLEnum __cdecl CurrentUnitHasHealer();

    undefined4 __cdecl SetRestingForUnit(int unitID);

    void __stdcall PlayJokeVideoBasedOnCurrentTimeAndPlayTime();

    int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);

    void __cdecl SetRNGSeed(ulong param_1);

    int __cdecl GetFilePtrPos(HANDLE hFile);

} // namespace Global
} // namespace OpenSHC
