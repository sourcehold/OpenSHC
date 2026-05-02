/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Global.hpp'
*/

#pragma once

#include "OpenSHC/AI/AIVUnitTypeInt.hpp"
#include "OpenSHC/DirectPlay/DPNAME.hpp"
#include "OpenSHC/DirectPlay/DPSESSIONDESC2.hpp"
#include "OpenSHC/Game/Resources/ResourceTypeInt.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeInt.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeShort.hpp"
#include "OpenSHC/Map/Units/EuroRecruitableStateInt.hpp"
#include "OpenSHC/Map/Units/States/UnitStateShort.hpp"
#include "OpenSHC/Map/Units/UnitTypeInt.hpp"
#include "OpenSHC/Rendering/Enums/DirectDrawStatusInt.hpp"
#include "OpenSHC/UI/DisplayElement.hpp"
#include "OpenSHC/UI/Enums/DisplayElementIDInt.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "WinDef.h"
#include "crtdefs.h"
#include "ddraw.h"
#include "winnt.h"
namespace OpenSHC {
namespace Global {

    using OpenSHC::AI::AIVUnitTypeInt;
    using OpenSHC::DirectPlay::DPNAME;
    using OpenSHC::DirectPlay::DPSESSIONDESC2;
    using OpenSHC::Game::Resources::ResourceTypeInt;
    using OpenSHC::Map::Buildings::BuildingTypeInt;
    using OpenSHC::Map::Buildings::BuildingTypeShort;
    using OpenSHC::Map::Units::EuroRecruitableStateInt;
    using OpenSHC::Map::Units::UnitTypeInt;
    using OpenSHC::Map::Units::States::UnitStateShort;
    using OpenSHC::Rendering::Enums::DirectDrawStatusInt;
    using OpenSHC::UI::DisplayElement;
    using OpenSHC::UI::Enums::DisplayElementIDInt;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    void __stdcall SetCurrentEntityID3000();

    uint __cdecl SomeFireSpreadFunction(int param_1, int x, int y, int param_4, int param_5);

    uint __cdecl IgniteFireAtMiniTile(
        int playerID, int miniTileX, int miniTileY, int tileHeightMin8, int two, int fireIntensity);

    void __cdecl AFireSpreadFunction(int playerID, int x, int y, int height, int param_5, int param_6);

    void __cdecl SetPlaceOnFire(int playerID, int x, int y, int height, int param_5);

    void __stdcall UpdateHovel();

    void __stdcall UpdateWoodcuttersHut();

    void __stdcall UpdatePitchRig();

    void __stdcall UpdateMercenaryPost();

    void __stdcall UpdateBarracks();

    void __stdcall UpdateOutpostBuilding();

    void __stdcall UpdateStockpile();

    void __stdcall UpdateArmory();

    void __stdcall UpdateFletchersWorkshop();

    void __stdcall UpdateBlacksmithsWorkshop();

    void __stdcall UpdatePoleturnersWorkshop();

    void __stdcall UpdateArmorersWorkshop();

    void __stdcall UpdateTannersWorkshop();

    void __stdcall UpdateBakery();

    void __stdcall UpdateBrewery();

    void __stdcall UpdateGranary();

    void __stdcall UpdateInn();

    void __stdcall UpdateApothecary();

    void __stdcall UpdateTunnelersGuild();

    void __stdcall UpdateMarketplace();

    void __stdcall UpdateOilSmelter();

    void __stdcall UpdateWheatFarm();

    void __stdcall UpdateHopsFarm();

    void __stdcall UpdateAppleFarm();

    void __stdcall UpdateDairyFarm();

    void __stdcall UpdateMill();

    void __stdcall UpdateStables();

    void __stdcall UpdateBuildingShared2();

    void __stdcall UpdateCathedral();

    void __stdcall UpdateKeepManorHouse();

    void __stdcall UpdateKeepStoneKeep();

    void __stdcall UpdateKeepStronghold();

    void __stdcall UpdateDrawBridge();

    void __stdcall UpdateTunnel();

    void __stdcall UpdateBuildingShared1();

    void __stdcall UpdateCampGround();

    void __stdcall UpdateParadeGround2();

    void __stdcall UpdateParadeGround3();

    void __stdcall UpdateParadeGround4();

    void __stdcall UpdateBadBuildingGallows();

    void __stdcall UpdateBadBuildingStocks();

    void __stdcall UpdateGoodBuildingMaypole();

    void __stdcall UpdateGoodBuildingGarden();

    void __stdcall UpdatePlacedSiegeTower();

    void __stdcall UpdateWellOrWaterpot();

    void __stdcall UpdateKeepDoorLeft();

    void __stdcall UpdateKeepDoorRight();

    void __stdcall UpdateKeepDoor();

    void __stdcall UpdateTower1();

    void __stdcall UpdateBadBuildingCessPitOrDancingBearUnk();

    void __stdcall UpdateBadBuildingBurningStake();

    void __stdcall UpdateBadBuildingGibbet();

    void __stdcall UpdateBadBuildingDungeon();

    void __stdcall UpdateBadBuildingStretchingRack();

    void __stdcall UpdateBadBuildingRackFlogging();

    void __stdcall UpdateBadBuildingChoppingBlock();

    void __stdcall UpdateBadBuildingDunkingStool();

    void __stdcall UpdateGoodBuildingStatue();

    void __stdcall UpdateGoodBuildingShrine();

    void __stdcall UpdateDancingBear();

    void __stdcall DestroyDrawbridgesInFirst10Buildings();

    void __stdcall ClearBuildings1000AndHigher();

    void __stdcall UpdateOxTether();

    void __stdcall UpdateIronMine();

    void __stdcall UpdateQuarry();

    void __stdcall UpdateFireBallistaBuilding();

    void __stdcall UpdateKillingPit();

    void __stdcall UpdateTower2();

    void __stdcall UpdateTower3();

    void __stdcall UpdateTower4();

    void __stdcall UpdateTower5();

    void __stdcall UpdateCatapultBuilding();

    void __stdcall UpdateTrebutchetBuilding();

    void __stdcall UpdateSiegeTowerBuilding();

    void __stdcall UpdateBatteringRamBuilding();

    void __stdcall UpdateShieldBuilding();

    void __stdcall UpdateDogCage();

    void __stdcall UpdateHuntersPost();

    void __stdcall UpdateGateHouseLarge();

    void __stdcall UpdateGateHouseSmall();

    void __stdcall UpdateWoodGate1();

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

    void __cdecl PlayPlacementWarning(undefined4 param_1);

    void __stdcall PlaceUnit();

    void __cdecl HandleBuildingSelectionSpeech(int buildingIndexUnk);

    HCURSOR __stdcall SetCursorDependingOnProgramState();

    void __stdcall DisplayMapDescriptionAndAllocatePlayersToSlots();

    void __cdecl LaunchSkirmishGame(int whichCastle);

    int __cdecl ComputePlayerPoints1(int playerID);

    void __stdcall PlayUnitSpeech(UnitTypeInt unitType, int actionID);

    int __cdecl ComputePlayerRanking(int playerID);

    int __cdecl GetPlayerAtRank(int rankingPosition);

    int __stdcall IfAiGreatestLordGetAiType();

    void __stdcall GetLowestRankedAlivePlayer();

    void __stdcall ComputeCurrentPlayerRanking();

    void __stdcall PlaySFXVoices();

    void __stdcall InitBlendFilterArraysUnk();

    void __cdecl PrintToDestination(wchar_t* destination, wchar_t* format);

    EuroRecruitableStateInt __cdecl IsEuroUnitRecruitableUnk(int barrackUnitIdUnk);

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

    void __cdecl SetPlayerBuyingResultStateUnk(int state, ResourceTypeInt resourceTypePlus1);

    void __cdecl ProcessBuyOrSell(int playerID, int buyOrSell, ResourceTypeInt resourceType);

    void __cdecl TryAcquireAmmunitionOrPlanToBuyStone(int param_1, int param_2);

    short* __cdecl SelectionReplenishAmmo(int playerID, int param_2);

    void __cdecl ProcessBuildingSleepUpdate(int playerID, int buildingType);

    void __cdecl ProcessTowerRepair(
        int playerID, int buildingID, int requiredWood, int requiredStone, int gameObjectID);

    void __cdecl ReleaseDogs2(int param_1, int buildingID, int buildingUID);

    void __stdcall SetEnoughGoldForRequestedUnitToTrueUnk();

    void __stdcall SetSomeColorsUnk();

    HRESULT __stdcall EnumDisplayModesCallback(DDSURFACEDESC* displayDesc, LPVOID userParam);

    void __stdcall FUN_Useless();

    byte __stdcall RotateByteLeft(byte value, int bits);

    char* __cdecl GetStringBasedOnHardcodedMaps(char* mapName, int* hardcodedMapDescriptionGroupNum);

    DirectDrawStatusInt __stdcall DetectDXVersionByLoadingDDRAW();

    byte __stdcall TestOSVersion();

    BOOL __stdcall EnumConnectionsCallback(
        LPCGUID lpguidSP, LPVOID lpConnection, DWORD dwConnectionSize, DPNAME* lpName, DWORD dwFlags, LPVOID lpContext);

    bool __stdcall EnumSessionsCallback_addSession_async(
        DPSESSIONDESC2* lpThisSD, LPDWORD lpdwTimeOut, DWORD dwFlags, LPVOID lpContext);

    BOOLEnum __stdcall DirectPlayModemRelated_MemoryAllocationFunction(int* param_1, undefined4 param_2, char* param_3);

    int __stdcall CompressOrCreateLengthPrefixedPacketUnk(int size, char* src, void* dst);

    int __stdcall ComputeSomeHashOnUnitArray();

    void __stdcall UpgradeOldSection1124();

    void __cdecl MemCopyFromParameter(char* dest, size_t size, undefined4 playerID);

    void __stdcall SetupPreviewMinimapDataUnk();

    void __stdcall ProgressBarRelated();

    void __stdcall ClearPathFindingTileMaps();

    void __stdcall UpdateLadderManState01();

    void __stdcall UpdateLadderManState03();

    void __stdcall UpdateLadderManState04();

    void __stdcall UpdateLadderManState05();

    void __stdcall UpdateLadderManState07();

    void __cdecl ProcessAllyAcceptsRequest(int param_1, int param_2);

    void __cdecl ProcessAllyDeniesRequest2(int param_1, int param_2);

    void __cdecl ProcessAllyRequestAttackDefense(
        int targetPlayerID, int playerID, int requestedByPlayerID, int param_4);

    void __cdecl ProcessAllyRequestingGoods(int askedPlayerID, int param_2, int amount, int askee);

    void __cdecl ProcessAllyGoodsRequest(int param_1, ResourceTypeInt param_2, int param_3, int param_4);

    void __cdecl ProcessAllyDeniesRequest(int param_1, int param_2);

    DisplayElement* __cdecl FindDisplayElementWithID(int elementID);

    void __cdecl CheckDisplayElementByIDAndSetForUnlimitedDisplay(
        DisplayElementIDInt displayElementID, dword elementState);

    void __cdecl ActivateGameSpeedAndResourceLackDisplayElementUnk(
        DisplayElementIDInt elementId, dword elementState, int displayDuration);

    BOOLEnum __cdecl GetIfDisplayElementStateNotZero(DisplayElementIDInt displayElementID);

    LRESULT __stdcall WindowMsgProcessingFunc(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam);

    int __stdcall GetDifficultyMultipliedValue(int param_1);

    void __cdecl SumUnitPoints();

    void __cdecl FUN_004bc690(int param_1, BuildingTypeInt buildingType);

    void __stdcall FUN_004bc770();

    void __cdecl SetupSkirmishMode(int skirmishTrailMission);

    void __cdecl LoadSkirmishCampaignData(int missionID);

    int __stdcall StoreTime();

    AIVUnitTypeInt __stdcall GetUnitTypeIndexForUnitID(int unitID, int param_2);

    int __stdcall ChecksAndGenerateAITribesForPlayerIfNotExisting(int playerID, int maxAmount, BOOLEnum checkOnly);

    BOOLEnum __stdcall CheckTribeActivityPercentages(int tribeID, BOOLEnum ignoreShooting, BOOLEnum includeMoving);

    void __stdcall PlayTauntToAttackedPlayerBikFromPlayer(int playerID);

    void __stdcall PlayGoodsRequestBikFromPlayerToPlayer(int playerID, int targetPlayerID);

    void __stdcall PlayNervous2BikFromPlayer(int playerID);

    void __stdcall PlayGoodsNotSentBikFromPlayer(int playerID);

    void __stdcall PlayGoodsSentBikFromPlayerToPlayer(int playerID, int targetPlayerID);

    void __stdcall PlayAnger2BikFromPlayerToPlayer(int playerID, int targetPlayerID);

    void __stdcall PlayVictory2BikFromPlayerToPlayer(int playerID, int targetPlayerID);

    void __stdcall PlayNervous1BikFromPlayer(int playerID);

    void __stdcall PlayRequestHelpBikFromPlayer(int playerID);

    void __stdcall PlayWillNotHelp1BikFromPlayerToPlayer(int playerID, int targetPlayerID);

    void __stdcall PlayWillNotHelp2BikFromPlayerToPlayer(int playerID, int targetPlayerID);

    void __stdcall PlayWillHelpBikFromPlayerToPlayer(int playerID, int targetPlayerID);

    void __stdcall PlayWillNotAttack1BikFromPlayerToPlayer(int playerID, int targetPlayerID);

    void __stdcall PlayWillNotAttack2BikFromPlayerToPlayer(int playerID, int targetPlayerID);

    void __stdcall PlayWillAttackBikFromPlayerToPlayer(int playerID, int targetPlayerID);

    void __stdcall PlayJokeBikFromAIToHuman(int playerID, int aiType);

    void __stdcall PlayFriendlyVictoryBikFromPlayer(int playerID);

    void __stdcall PlayTeamWinningBikFromPlayer(int playerID);

    void __stdcall PlayNoHelpBikFromPlayer(int playerID);

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

    void __stdcall renderSomethingMap3(int param_1, int param_2, int param_3, undefined4 param_4, int param_5);

    int __stdcall SomeComputationWithSeparateAreas();

    void __stdcall VersioningFixTrees();

    void __stdcall RemoveCertainRockTypesUnk();

    void __stdcall RemoveRocksBeyond1000();

    int __stdcall ReturnMoatIDForPlayerIDs(int playerID, int playerID2);

    void __stdcall UpgradeMapLogicToVersion_125();

    void __stdcall UpgradeMapLogicToVersion_128();

    void __stdcall UpgradeMapLogicToVersion_102();

    void __stdcall UpgradeMapLogicToVersion_120();

    void __stdcall UpgradeMapLogicToVersion_145();

    void __stdcall UpgradeMapLogicToVersion_147();

    BOOLEnum __stdcall AttackInfoHasHigh2Building(int buildingID);

    undefined4 __stdcall AttackInfoHasArch2Building(int buildingID);

    int __stdcall AssignTribeToSupportPoint(uint x, uint y, int tribeID);

    void __cdecl DecrementTileMap1104();

    void __stdcall ClearAnimalSpawnLocationsUnk();

    void __cdecl updateLogicAndClimbData(int unitID);

    void __cdecl detachLadderman(int unitID);

    void __stdcall UpdateSiegeTent();

    void __stdcall UpdateBurningAnimal1();

    void __stdcall UpdateBurningAnimal2();

    void __cdecl IncrementAndOptionalUpdateAVValueRelated(int unitID, BOOLEnum updateAV);

    BOOLEnum __cdecl ConsiderHavingABreakNowUnk(int unitID, UnitStateShort nextUnitState);

    undefined4 __cdecl SetStateToFreetimeWalking(int unitID, int shouldFindNewGoodThing, int param_3);

    bool __cdecl FUN_00530d50(int param_1);

    int __cdecl ComputeGoodsProduced(int unitID, int goodsCount, BOOLEnum boost);

    BuildingTypeShort* __stdcall FUN_00530e00();

    uint __stdcall TryPlayStockpileIsFullNoiseUnk();

    BuildingTypeShort* __stdcall PlaySound_StockpileIsFullMyLordUnk();

    BOOLEnum __cdecl CurrentUnitHasHealer();

    void __stdcall UpdateBurningMan();

    void __stdcall UpdateCamel();

    void __stdcall UpdateShield();

    BOOLEnum __cdecl ConsiderTakingABreakUnk(int unitID);

    void __stdcall UpdatePeasant();

    void __stdcall UpdateOx();

    void __stdcall UpdateMiner();

    void __stdcall UpdateHealer();

    void __stdcall UpdateInnkeeper();

    void __stdcall UpdateMerchant();

    void __stdcall UpdateMerchantHorse();

    void __stdcall UpdateDeer();

    void __stdcall UpdateRabbit();

    void __stdcall UpdateCow();

    void __stdcall UpdateFireWatch();

    void __stdcall UpdateGhost();

    void __stdcall UpdateLady();

    void __stdcall UpdateSiegeTower();

    void __stdcall UpdateBatteringRam();

    void __stdcall UpdateChicken();

    void __stdcall UpdateMother();

    void __stdcall UpdateChild();

    void __stdcall UpdateJuggler();

    void __stdcall UpdateFireEater();

    undefined4 __cdecl SetRestingForUnit(int unitID);

    BOOLEnum __stdcall UpdateWoodcutter();

    void __stdcall UpdateFletcher();

    void __stdcall UpdateTunneler();

    void __stdcall UpdateHunter();

    void __stdcall UpdateQuarryMason();

    void __stdcall UpdateQuarryWorker();

    void __stdcall UpdatePitchman();

    void __stdcall UpdateWheatFarmer();

    void __stdcall UpdateHopsFarmer();

    void __stdcall UpdateAppleFarmer();

    void __stdcall UpdateDairyFarmer();

    void __stdcall UpdateMiller();

    void __stdcall UpdateBaker();

    void __stdcall UpdateBrewer();

    void __stdcall UpdatePoleTurner();

    void __stdcall UpdateBlacksmith();

    void __stdcall UpdateArmorer();

    void __stdcall UpdateTanner();

    void __stdcall UpdateCrusaderArcher();

    void __stdcall UpdateCrossbowman();

    void __stdcall UpdateSpearman();

    void __stdcall UpdatePikeman();

    void __stdcall UpdateMaceman();

    void __stdcall UpdateSwordsman();

    void __stdcall UpdateKnight();

    void __stdcall UpdateLadderman();

    void __stdcall UpdateEngineer();

    void __stdcall UpdateMinerIronFetcher();

    void __stdcall UpdatePriest();

    void __stdcall UpdateDrunkard();

    void __stdcall UpdateMonk();

    void __stdcall UpdateCatapult();

    void __stdcall UpdateTrebuchet();

    void __stdcall UpdateMangonel();

    void __stdcall UpdateLion();

    void __stdcall UpdateHunterDog();

    void __stdcall UpdateLord();

    void __stdcall UpdateJester();

    void __stdcall UpdateBallista();

    void __stdcall UpdateCageDog();

    void __stdcall UpdateArabianArcher();

    void __stdcall UpdateSlave();

    void __stdcall UpdateSlinger();

    void __stdcall UpdateAssassin();

    void __cdecl HorseArcher_DoShooting(short* unitID);

    void __stdcall UpdateArabianSwordsman();

    void __stdcall UpdateFireThrower();

    void __stdcall UpdateFireBallista();

    void __stdcall UpdateHorseArcher();

    void __stdcall PlayJokeVideoBasedOnCurrentTimeAndPlayTime();

    int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);

    void __cdecl SetRNGSeed(ulong param_1);

    char* __cdecl StringToLowerCase(char* string);

    int __cdecl GetFilePtrPos(HANDLE hFile);

} // namespace Global
} // namespace OpenSHC
