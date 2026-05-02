/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Global.func.hpp'
*/

#pragma once

#include "OpenSHC/AI/AIVUnitTypeInt.hpp"
#include "OpenSHC/DirectPlay/DPNAME.hpp"
#include "OpenSHC/DirectPlay/DPSESSIONDESC2.hpp"
#include "OpenSHC/Game/Resources/ResourceTypeInt.hpp"
#include "OpenSHC/Global.hpp"
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
namespace Global_Func {

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

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00410CA0, &OpenSHC::Global::UpdateHovel)
    UpdateHovel;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00410D20, &OpenSHC::Global::UpdateWoodcuttersHut)
    UpdateWoodcuttersHut;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00410EE0, &OpenSHC::Global::UpdatePitchRig)
    UpdatePitchRig;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004113C0, &OpenSHC::Global::UpdateMercenaryPost)
    UpdateMercenaryPost;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00411480, &OpenSHC::Global::UpdateBarracks)
    UpdateBarracks;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00411540, &OpenSHC::Global::UpdateOutpostBuilding)
    UpdateOutpostBuilding;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00412360, &OpenSHC::Global::UpdateStockpile)
    UpdateStockpile;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00412730, &OpenSHC::Global::UpdateArmory)
    UpdateArmory;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00412D50, &OpenSHC::Global::UpdateFletchersWorkshop)
    UpdateFletchersWorkshop;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004130D0, &OpenSHC::Global::UpdateBlacksmithsWorkshop)
    UpdateBlacksmithsWorkshop;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004138D0, &OpenSHC::Global::UpdatePoleturnersWorkshop)
    UpdatePoleturnersWorkshop;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00413DC0, &OpenSHC::Global::UpdateArmorersWorkshop)
    UpdateArmorersWorkshop;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004140B0, &OpenSHC::Global::UpdateTannersWorkshop)
    UpdateTannersWorkshop;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00414720, &OpenSHC::Global::UpdateBakery)
    UpdateBakery;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00414B60, &OpenSHC::Global::UpdateBrewery)
    UpdateBrewery;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00415110, &OpenSHC::Global::UpdateGranary)
    UpdateGranary;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004156F0, &OpenSHC::Global::UpdateInn)
    UpdateInn;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00415A80, &OpenSHC::Global::UpdateApothecary)
    UpdateApothecary;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00415BF0, &OpenSHC::Global::UpdateTunnelersGuild)
    UpdateTunnelersGuild;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00415C90, &OpenSHC::Global::UpdateMarketplace)
    UpdateMarketplace;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00415E80, &OpenSHC::Global::UpdateOilSmelter)
    UpdateOilSmelter;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00416540, &OpenSHC::Global::UpdateWheatFarm)
    UpdateWheatFarm;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00416630, &OpenSHC::Global::UpdateHopsFarm)
    UpdateHopsFarm;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00416720, &OpenSHC::Global::UpdateAppleFarm)
    UpdateAppleFarm;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004167E0, &OpenSHC::Global::UpdateDairyFarm)
    UpdateDairyFarm;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00416F80, &OpenSHC::Global::UpdateMill)
    UpdateMill;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004174E0, &OpenSHC::Global::UpdateStables)
    UpdateStables;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00417740, &OpenSHC::Global::UpdateBuildingShared2)
    UpdateBuildingShared2;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004177E0, &OpenSHC::Global::UpdateCathedral)
    UpdateCathedral;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004178E0, &OpenSHC::Global::UpdateKeepManorHouse)
    UpdateKeepManorHouse;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004179B0, &OpenSHC::Global::UpdateKeepStoneKeep)
    UpdateKeepStoneKeep;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00417AA0, &OpenSHC::Global::UpdateKeepStronghold)
    UpdateKeepStronghold;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00417B90, &OpenSHC::Global::UpdateDrawBridge)
    UpdateDrawBridge;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00417FD0, &OpenSHC::Global::UpdateTunnel)
    UpdateTunnel;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004180E0, &OpenSHC::Global::UpdateBuildingShared1)
    UpdateBuildingShared1;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00418100, &OpenSHC::Global::UpdateCampGround)
    UpdateCampGround;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004184A0, &OpenSHC::Global::UpdateParadeGround2)
    UpdateParadeGround2;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004184D0, &OpenSHC::Global::UpdateParadeGround3)
    UpdateParadeGround3;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00418500, &OpenSHC::Global::UpdateParadeGround4)
    UpdateParadeGround4;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00418530, &OpenSHC::Global::UpdateBadBuildingGallows)
    UpdateBadBuildingGallows;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00418640, &OpenSHC::Global::UpdateBadBuildingStocks)
    UpdateBadBuildingStocks;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00418740, &OpenSHC::Global::UpdateGoodBuildingMaypole)
    UpdateGoodBuildingMaypole;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00418880, &OpenSHC::Global::UpdateGoodBuildingGarden)
    UpdateGoodBuildingGarden;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004188C0, &OpenSHC::Global::UpdatePlacedSiegeTower)
    UpdatePlacedSiegeTower;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00418900, &OpenSHC::Global::UpdateWellOrWaterpot)
    UpdateWellOrWaterpot;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004189A0, &OpenSHC::Global::UpdateKeepDoorLeft)
    UpdateKeepDoorLeft;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00418A60, &OpenSHC::Global::UpdateKeepDoorRight)
    UpdateKeepDoorRight;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00418B20, &OpenSHC::Global::UpdateKeepDoor)
    UpdateKeepDoor;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00418C80, &OpenSHC::Global::UpdateTower1)
    UpdateTower1;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00418F70,
        &OpenSHC::Global::UpdateBadBuildingCessPitOrDancingBearUnk)
    UpdateBadBuildingCessPitOrDancingBearUnk;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00418F90, &OpenSHC::Global::UpdateBadBuildingBurningStake)
    UpdateBadBuildingBurningStake;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004190D0, &OpenSHC::Global::UpdateBadBuildingGibbet)
    UpdateBadBuildingGibbet;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00419190, &OpenSHC::Global::UpdateBadBuildingDungeon)
    UpdateBadBuildingDungeon;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00419290, &OpenSHC::Global::UpdateBadBuildingStretchingRack)
    UpdateBadBuildingStretchingRack;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00419340, &OpenSHC::Global::UpdateBadBuildingRackFlogging)
    UpdateBadBuildingRackFlogging;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00419370, &OpenSHC::Global::UpdateBadBuildingChoppingBlock)
    UpdateBadBuildingChoppingBlock;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00419420, &OpenSHC::Global::UpdateBadBuildingDunkingStool)
    UpdateBadBuildingDunkingStool;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00419630, &OpenSHC::Global::UpdateGoodBuildingStatue)
    UpdateGoodBuildingStatue;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00419670, &OpenSHC::Global::UpdateGoodBuildingShrine)
    UpdateGoodBuildingShrine;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004196D0, &OpenSHC::Global::UpdateDancingBear)
    UpdateDancingBear;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0041A460,
        &OpenSHC::Global::DestroyDrawbridgesInFirst10Buildings)
    DestroyDrawbridgesInFirst10Buildings;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0041A620, &OpenSHC::Global::ClearBuildings1000AndHigher)
    ClearBuildings1000AndHigher;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0041CA00, &OpenSHC::Global::UpdateOxTether)
    UpdateOxTether;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0041CC70, &OpenSHC::Global::UpdateIronMine)
    UpdateIronMine;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0041D510, &OpenSHC::Global::UpdateQuarry)
    UpdateQuarry;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0041E240, &OpenSHC::Global::UpdateFireBallistaBuilding)
    UpdateFireBallistaBuilding;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0041E650, &OpenSHC::Global::UpdateKillingPit)
    UpdateKillingPit;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0041E870, &OpenSHC::Global::UpdateTower2)
    UpdateTower2;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0041EB00, &OpenSHC::Global::UpdateTower3)
    UpdateTower3;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0041EDA0, &OpenSHC::Global::UpdateTower4)
    UpdateTower4;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0041F110, &OpenSHC::Global::UpdateTower5)
    UpdateTower5;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0041F3B0, &OpenSHC::Global::UpdateCatapultBuilding)
    UpdateCatapultBuilding;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0041F7C0, &OpenSHC::Global::UpdateTrebutchetBuilding)
    UpdateTrebutchetBuilding;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0041FC90, &OpenSHC::Global::UpdateSiegeTowerBuilding)
    UpdateSiegeTowerBuilding;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00420120, &OpenSHC::Global::UpdateBatteringRamBuilding)
    UpdateBatteringRamBuilding;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004205B0, &OpenSHC::Global::UpdateShieldBuilding)
    UpdateShieldBuilding;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00420A30, &OpenSHC::Global::UpdateDogCage)
    UpdateDogCage;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00423370, &OpenSHC::Global::UpdateHuntersPost)
    UpdateHuntersPost;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004238B0, &OpenSHC::Global::UpdateGateHouseLarge)
    UpdateGateHouseLarge;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00423CD0, &OpenSHC::Global::UpdateGateHouseSmall)
    UpdateGateHouseSmall;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004240D0, &OpenSHC::Global::UpdateWoodGate1)
    UpdateWoodGate1;

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

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(undefined4 param_1), false, Address::SHC_3BB0A8C1_0x004380E0,
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

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(UnitTypeInt unitType, int actionID), false,
        Address::SHC_3BB0A8C1_0x0044B210, &OpenSHC::Global::PlayUnitSpeech)
    PlayUnitSpeech;

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
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0044B800, &OpenSHC::Global::GetLowestRankedAlivePlayer)
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

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(wchar_t* destination, wchar_t* format), false,
        Address::SHC_3BB0A8C1_0x0045D060, &OpenSHC::Global::PrintToDestination)
    PrintToDestination;

    MACRO_FUNCTION_RESOLVER(EuroRecruitableStateInt(__cdecl*)(int barrackUnitIdUnk), false,
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

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int state, ResourceTypeInt resourceTypePlus1), false,
        Address::SHC_3BB0A8C1_0x00465DB0, &OpenSHC::Global::SetPlayerBuyingResultStateUnk)
    SetPlayerBuyingResultStateUnk;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int playerID, int buyOrSell, ResourceTypeInt resourceType), false,
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

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00469F10, &OpenSHC::Global::FUN_Useless)
    FUN_Useless;

    MACRO_FUNCTION_RESOLVER(byte(__stdcall*)(byte value, int bits), false, Address::SHC_3BB0A8C1_0x0046CE30,
        &OpenSHC::Global::RotateByteLeft)
    RotateByteLeft;

    MACRO_FUNCTION_RESOLVER(char*(__cdecl*)(char* mapName, int* hardcodedMapDescriptionGroupNum), false,
        Address::SHC_3BB0A8C1_0x0046D390, &OpenSHC::Global::GetStringBasedOnHardcodedMaps)
    GetStringBasedOnHardcodedMaps;

    MACRO_FUNCTION_RESOLVER(DirectDrawStatusInt(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0046F4F0,
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

    MACRO_FUNCTION_RESOLVER(int(__stdcall*)(int size, char* src, void* dst), false, Address::SHC_3BB0A8C1_0x0047E7E0,
        &OpenSHC::Global::CompressOrCreateLengthPrefixedPacketUnk)
    CompressOrCreateLengthPrefixedPacketUnk;

    MACRO_FUNCTION_RESOLVER(
        int(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0047EEB0, &OpenSHC::Global::ComputeSomeHashOnUnitArray)
    ComputeSomeHashOnUnitArray;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00486AD0, &OpenSHC::Global::UpgradeOldSection1124)
    UpgradeOldSection1124;

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

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004A4D60, &OpenSHC::Global::UpdateLadderManState01)
    UpdateLadderManState01;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004A4E40, &OpenSHC::Global::UpdateLadderManState03)
    UpdateLadderManState03;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004A4F90, &OpenSHC::Global::UpdateLadderManState04)
    UpdateLadderManState04;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004A50E0, &OpenSHC::Global::UpdateLadderManState05)
    UpdateLadderManState05;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004A5230, &OpenSHC::Global::UpdateLadderManState07)
    UpdateLadderManState07;

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

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ResourceTypeInt param_2, int param_3, int param_4), false,
        Address::SHC_3BB0A8C1_0x004ADDD0, &OpenSHC::Global::ProcessAllyGoodsRequest)
    ProcessAllyGoodsRequest;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, int param_2), false, Address::SHC_3BB0A8C1_0x004AE010,
        &OpenSHC::Global::ProcessAllyDeniesRequest)
    ProcessAllyDeniesRequest;

    MACRO_FUNCTION_RESOLVER(DisplayElement*(__cdecl*)(int elementID), false, Address::SHC_3BB0A8C1_0x004AF630,
        &OpenSHC::Global::FindDisplayElementWithID)
    FindDisplayElementWithID;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(DisplayElementIDInt displayElementID, dword elementState), false,
        Address::SHC_3BB0A8C1_0x004AF650, &OpenSHC::Global::CheckDisplayElementByIDAndSetForUnlimitedDisplay)
    CheckDisplayElementByIDAndSetForUnlimitedDisplay;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(DisplayElementIDInt elementId, dword elementState, int displayDuration),
        false, Address::SHC_3BB0A8C1_0x004AF680, &OpenSHC::Global::ActivateGameSpeedAndResourceLackDisplayElementUnk)
    ActivateGameSpeedAndResourceLackDisplayElementUnk;

    MACRO_FUNCTION_RESOLVER(BOOLEnum(__cdecl*)(DisplayElementIDInt displayElementID), false,
        Address::SHC_3BB0A8C1_0x004AF6E0, &OpenSHC::Global::GetIfDisplayElementStateNotZero)
    GetIfDisplayElementStateNotZero;

    MACRO_FUNCTION_RESOLVER(LRESULT(__stdcall*)(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam), false,
        Address::SHC_3BB0A8C1_0x004B2AE0, &OpenSHC::Global::WindowMsgProcessingFunc)
    WindowMsgProcessingFunc;

    MACRO_FUNCTION_RESOLVER(int(__stdcall*)(int param_1), false, Address::SHC_3BB0A8C1_0x004B7AB0,
        &OpenSHC::Global::GetDifficultyMultipliedValue)
    GetDifficultyMultipliedValue;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004B8200, &OpenSHC::Global::SumUnitPoints)
    SumUnitPoints;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, BuildingTypeInt buildingType), false,
        Address::SHC_3BB0A8C1_0x004BC690, &OpenSHC::Global::FUN_004bc690)
    FUN_004bc690;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004BC770, &OpenSHC::Global::FUN_004bc770)
    FUN_004bc770;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int skirmishTrailMission), false, Address::SHC_3BB0A8C1_0x004C68D0,
        &OpenSHC::Global::SetupSkirmishMode)
    SetupSkirmishMode;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int missionID), false, Address::SHC_3BB0A8C1_0x004C6B20,
        &OpenSHC::Global::LoadSkirmishCampaignData)
    LoadSkirmishCampaignData;

    MACRO_FUNCTION_RESOLVER(int(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004C6CD0, &OpenSHC::Global::StoreTime)
    StoreTime;

    MACRO_FUNCTION_RESOLVER(AIVUnitTypeInt(__stdcall*)(int unitID, int param_2), false,
        Address::SHC_3BB0A8C1_0x004CC390, &OpenSHC::Global::GetUnitTypeIndexForUnitID)
    GetUnitTypeIndexForUnitID;

    MACRO_FUNCTION_RESOLVER(int(__stdcall*)(int playerID, int maxAmount, BOOLEnum checkOnly), false,
        Address::SHC_3BB0A8C1_0x004CCFB0, &OpenSHC::Global::ChecksAndGenerateAITribesForPlayerIfNotExisting)
    ChecksAndGenerateAITribesForPlayerIfNotExisting;

    MACRO_FUNCTION_RESOLVER(BOOLEnum(__stdcall*)(int tribeID, BOOLEnum ignoreShooting, BOOLEnum includeMoving), false,
        Address::SHC_3BB0A8C1_0x004CD070, &OpenSHC::Global::CheckTribeActivityPercentages)
    CheckTribeActivityPercentages;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(int playerID), false, Address::SHC_3BB0A8C1_0x004D07C0,
        &OpenSHC::Global::PlayTauntToAttackedPlayerBikFromPlayer)
    PlayTauntToAttackedPlayerBikFromPlayer;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(int playerID, int targetPlayerID), false, Address::SHC_3BB0A8C1_0x004D0A20,
        &OpenSHC::Global::PlayGoodsRequestBikFromPlayerToPlayer)
    PlayGoodsRequestBikFromPlayerToPlayer;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(int playerID), false, Address::SHC_3BB0A8C1_0x004D0B10,
        &OpenSHC::Global::PlayNervous2BikFromPlayer)
    PlayNervous2BikFromPlayer;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(int playerID), false, Address::SHC_3BB0A8C1_0x004D0B70,
        &OpenSHC::Global::PlayGoodsNotSentBikFromPlayer)
    PlayGoodsNotSentBikFromPlayer;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(int playerID, int targetPlayerID), false, Address::SHC_3BB0A8C1_0x004D0BB0,
        &OpenSHC::Global::PlayGoodsSentBikFromPlayerToPlayer)
    PlayGoodsSentBikFromPlayerToPlayer;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(int playerID, int targetPlayerID), false, Address::SHC_3BB0A8C1_0x004D0C00,
        &OpenSHC::Global::PlayAnger2BikFromPlayerToPlayer)
    PlayAnger2BikFromPlayerToPlayer;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(int playerID, int targetPlayerID), false, Address::SHC_3BB0A8C1_0x004D0C70,
        &OpenSHC::Global::PlayVictory2BikFromPlayerToPlayer)
    PlayVictory2BikFromPlayerToPlayer;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(int playerID), false, Address::SHC_3BB0A8C1_0x004D0CF0,
        &OpenSHC::Global::PlayNervous1BikFromPlayer)
    PlayNervous1BikFromPlayer;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(int playerID), false, Address::SHC_3BB0A8C1_0x004D0D40,
        &OpenSHC::Global::PlayRequestHelpBikFromPlayer)
    PlayRequestHelpBikFromPlayer;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(int playerID, int targetPlayerID), false, Address::SHC_3BB0A8C1_0x004D0DB0,
        &OpenSHC::Global::PlayWillNotHelp1BikFromPlayerToPlayer)
    PlayWillNotHelp1BikFromPlayerToPlayer;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(int playerID, int targetPlayerID), false, Address::SHC_3BB0A8C1_0x004D0E00,
        &OpenSHC::Global::PlayWillNotHelp2BikFromPlayerToPlayer)
    PlayWillNotHelp2BikFromPlayerToPlayer;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(int playerID, int targetPlayerID), false, Address::SHC_3BB0A8C1_0x004D0E50,
        &OpenSHC::Global::PlayWillHelpBikFromPlayerToPlayer)
    PlayWillHelpBikFromPlayerToPlayer;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(int playerID, int targetPlayerID), false, Address::SHC_3BB0A8C1_0x004D0EA0,
        &OpenSHC::Global::PlayWillNotAttack1BikFromPlayerToPlayer)
    PlayWillNotAttack1BikFromPlayerToPlayer;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(int playerID, int targetPlayerID), false, Address::SHC_3BB0A8C1_0x004D0EF0,
        &OpenSHC::Global::PlayWillNotAttack2BikFromPlayerToPlayer)
    PlayWillNotAttack2BikFromPlayerToPlayer;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(int playerID, int targetPlayerID), false, Address::SHC_3BB0A8C1_0x004D0F40,
        &OpenSHC::Global::PlayWillAttackBikFromPlayerToPlayer)
    PlayWillAttackBikFromPlayerToPlayer;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(int playerID, int aiType), false, Address::SHC_3BB0A8C1_0x004D0F90,
        &OpenSHC::Global::PlayJokeBikFromAIToHuman)
    PlayJokeBikFromAIToHuman;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(int playerID), false, Address::SHC_3BB0A8C1_0x004D0FC0,
        &OpenSHC::Global::PlayFriendlyVictoryBikFromPlayer)
    PlayFriendlyVictoryBikFromPlayer;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(int playerID), false, Address::SHC_3BB0A8C1_0x004D1000,
        &OpenSHC::Global::PlayTeamWinningBikFromPlayer)
    PlayTeamWinningBikFromPlayer;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(int playerID), false, Address::SHC_3BB0A8C1_0x004D1050,
        &OpenSHC::Global::PlayNoHelpBikFromPlayer)
    PlayNoHelpBikFromPlayer;

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

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(int param_1, int param_2, int param_3, undefined4 param_4, int param_5),
        false, Address::SHC_3BB0A8C1_0x004E3870, &OpenSHC::Global::renderSomethingMap3)
    renderSomethingMap3;

    MACRO_FUNCTION_RESOLVER(
        int(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004EDD00, &OpenSHC::Global::SomeComputationWithSeparateAreas)
    SomeComputationWithSeparateAreas;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004F37B0, &OpenSHC::Global::VersioningFixTrees)
    VersioningFixTrees;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004F3840, &OpenSHC::Global::RemoveCertainRockTypesUnk)
    RemoveCertainRockTypesUnk;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004F3900, &OpenSHC::Global::RemoveRocksBeyond1000)
    RemoveRocksBeyond1000;

    MACRO_FUNCTION_RESOLVER(int(__stdcall*)(int playerID, int playerID2), false, Address::SHC_3BB0A8C1_0x00500290,
        &OpenSHC::Global::ReturnMoatIDForPlayerIDs)
    ReturnMoatIDForPlayerIDs;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x005011C0, &OpenSHC::Global::UpgradeMapLogicToVersion_125)
    UpgradeMapLogicToVersion_125;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00501440, &OpenSHC::Global::UpgradeMapLogicToVersion_128)
    UpgradeMapLogicToVersion_128;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00501490, &OpenSHC::Global::UpgradeMapLogicToVersion_102)
    UpgradeMapLogicToVersion_102;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x005014F0, &OpenSHC::Global::UpgradeMapLogicToVersion_120)
    UpgradeMapLogicToVersion_120;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x005016D0, &OpenSHC::Global::UpgradeMapLogicToVersion_145)
    UpgradeMapLogicToVersion_145;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00501730, &OpenSHC::Global::UpgradeMapLogicToVersion_147)
    UpgradeMapLogicToVersion_147;

    MACRO_FUNCTION_RESOLVER(BOOLEnum(__stdcall*)(int buildingID), false, Address::SHC_3BB0A8C1_0x0051AC80,
        &OpenSHC::Global::AttackInfoHasHigh2Building)
    AttackInfoHasHigh2Building;

    MACRO_FUNCTION_RESOLVER(undefined4(__stdcall*)(int buildingID), false, Address::SHC_3BB0A8C1_0x0051ACB0,
        &OpenSHC::Global::AttackInfoHasArch2Building)
    AttackInfoHasArch2Building;

    MACRO_FUNCTION_RESOLVER(int(__stdcall*)(uint x, uint y, int tribeID), false, Address::SHC_3BB0A8C1_0x0051B190,
        &OpenSHC::Global::AssignTribeToSupportPoint)
    AssignTribeToSupportPoint;

    MACRO_FUNCTION_RESOLVER(
        void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x0051D5D0, &OpenSHC::Global::DecrementTileMap1104)
    DecrementTileMap1104;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x005232E0, &OpenSHC::Global::ClearAnimalSpawnLocationsUnk)
    ClearAnimalSpawnLocationsUnk;

    MACRO_FUNCTION_RESOLVER(
        void(__cdecl*)(int unitID), false, Address::SHC_3BB0A8C1_0x00530720, &OpenSHC::Global::updateLogicAndClimbData)
    updateLogicAndClimbData;

    MACRO_FUNCTION_RESOLVER(
        void(__cdecl*)(int unitID), false, Address::SHC_3BB0A8C1_0x00530760, &OpenSHC::Global::detachLadderman)
    detachLadderman;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x005307B0, &OpenSHC::Global::UpdateSiegeTent)
    UpdateSiegeTent;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x005309E0, &OpenSHC::Global::UpdateBurningAnimal1)
    UpdateBurningAnimal1;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00530A90, &OpenSHC::Global::UpdateBurningAnimal2)
    UpdateBurningAnimal2;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int unitID, BOOLEnum updateAV), false, Address::SHC_3BB0A8C1_0x00530B40,
        &OpenSHC::Global::IncrementAndOptionalUpdateAVValueRelated)
    IncrementAndOptionalUpdateAVValueRelated;

    MACRO_FUNCTION_RESOLVER(BOOLEnum(__cdecl*)(int unitID, UnitStateShort nextUnitState), false,
        Address::SHC_3BB0A8C1_0x00530C40, &OpenSHC::Global::ConsiderHavingABreakNowUnk)
    ConsiderHavingABreakNowUnk;

    MACRO_FUNCTION_RESOLVER(undefined4(__cdecl*)(int unitID, int shouldFindNewGoodThing, int param_3), false,
        Address::SHC_3BB0A8C1_0x00530CF0, &OpenSHC::Global::SetStateToFreetimeWalking)
    SetStateToFreetimeWalking;

    MACRO_FUNCTION_RESOLVER(
        bool(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00530D50, &OpenSHC::Global::FUN_00530d50)
    FUN_00530d50;

    MACRO_FUNCTION_RESOLVER(int(__cdecl*)(int unitID, int goodsCount, BOOLEnum boost), false,
        Address::SHC_3BB0A8C1_0x00530D70, &OpenSHC::Global::ComputeGoodsProduced)
    ComputeGoodsProduced;

    MACRO_FUNCTION_RESOLVER(
        BuildingTypeShort*(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00530E00, &OpenSHC::Global::FUN_00530e00)
    FUN_00530e00;

    MACRO_FUNCTION_RESOLVER(
        uint(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00530EB0, &OpenSHC::Global::TryPlayStockpileIsFullNoiseUnk)
    TryPlayStockpileIsFullNoiseUnk;

    MACRO_FUNCTION_RESOLVER(BuildingTypeShort*(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00530F20,
        &OpenSHC::Global::PlaySound_StockpileIsFullMyLordUnk)
    PlaySound_StockpileIsFullMyLordUnk;

    MACRO_FUNCTION_RESOLVER(
        BOOLEnum(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x0053A020, &OpenSHC::Global::CurrentUnitHasHealer)
    CurrentUnitHasHealer;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0053BC20, &OpenSHC::Global::UpdateBurningMan)
    UpdateBurningMan;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0053BE00, &OpenSHC::Global::UpdateCamel)
    UpdateCamel;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0053C300, &OpenSHC::Global::UpdateShield)
    UpdateShield;

    MACRO_FUNCTION_RESOLVER(BOOLEnum(__cdecl*)(int unitID), false, Address::SHC_3BB0A8C1_0x0053CAC0,
        &OpenSHC::Global::ConsiderTakingABreakUnk)
    ConsiderTakingABreakUnk;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0053EAA0, &OpenSHC::Global::UpdatePeasant)
    UpdatePeasant;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0053F940, &OpenSHC::Global::UpdateOx)
    UpdateOx;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x005401D0, &OpenSHC::Global::UpdateMiner)
    UpdateMiner;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00540440, &OpenSHC::Global::UpdateHealer)
    UpdateHealer;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00540EC0, &OpenSHC::Global::UpdateInnkeeper)
    UpdateInnkeeper;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x005416B0, &OpenSHC::Global::UpdateMerchant)
    UpdateMerchant;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00541A30, &OpenSHC::Global::UpdateMerchantHorse)
    UpdateMerchantHorse;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00541DE0, &OpenSHC::Global::UpdateDeer)
    UpdateDeer;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00542630, &OpenSHC::Global::UpdateRabbit)
    UpdateRabbit;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00542D10, &OpenSHC::Global::UpdateCow)
    UpdateCow;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00543340, &OpenSHC::Global::UpdateFireWatch)
    UpdateFireWatch;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00543B80, &OpenSHC::Global::UpdateGhost)
    UpdateGhost;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00543DC0, &OpenSHC::Global::UpdateLady)
    UpdateLady;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00544750, &OpenSHC::Global::UpdateSiegeTower)
    UpdateSiegeTower;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x005459B0, &OpenSHC::Global::UpdateBatteringRam)
    UpdateBatteringRam;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x005464F0, &OpenSHC::Global::UpdateChicken)
    UpdateChicken;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00546BC0, &OpenSHC::Global::UpdateMother)
    UpdateMother;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x005477C0, &OpenSHC::Global::UpdateChild)
    UpdateChild;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00549090, &OpenSHC::Global::UpdateJuggler)
    UpdateJuggler;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00549650, &OpenSHC::Global::UpdateFireEater)
    UpdateFireEater;

    MACRO_FUNCTION_RESOLVER(
        undefined4(__cdecl*)(int unitID), false, Address::SHC_3BB0A8C1_0x00549B30, &OpenSHC::Global::SetRestingForUnit)
    SetRestingForUnit;

    MACRO_FUNCTION_RESOLVER(
        BOOLEnum(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0054C710, &OpenSHC::Global::UpdateWoodcutter)
    UpdateWoodcutter;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0054D8F0, &OpenSHC::Global::UpdateFletcher)
    UpdateFletcher;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0054E6C0, &OpenSHC::Global::UpdateTunneler)
    UpdateTunneler;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0054F860, &OpenSHC::Global::UpdateHunter)
    UpdateHunter;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00550A50, &OpenSHC::Global::UpdateQuarryMason)
    UpdateQuarryMason;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00550D70, &OpenSHC::Global::UpdateQuarryWorker)
    UpdateQuarryWorker;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00551980, &OpenSHC::Global::UpdatePitchman)
    UpdatePitchman;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x005521D0, &OpenSHC::Global::UpdateWheatFarmer)
    UpdateWheatFarmer;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00552F80, &OpenSHC::Global::UpdateHopsFarmer)
    UpdateHopsFarmer;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00553AE0, &OpenSHC::Global::UpdateAppleFarmer)
    UpdateAppleFarmer;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00554500, &OpenSHC::Global::UpdateDairyFarmer)
    UpdateDairyFarmer;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00554CC0, &OpenSHC::Global::UpdateMiller)
    UpdateMiller;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00555880, &OpenSHC::Global::UpdateBaker)
    UpdateBaker;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x005565D0, &OpenSHC::Global::UpdateBrewer)
    UpdateBrewer;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00557230, &OpenSHC::Global::UpdatePoleTurner)
    UpdatePoleTurner;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00557F70, &OpenSHC::Global::UpdateBlacksmith)
    UpdateBlacksmith;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00558CB0, &OpenSHC::Global::UpdateArmorer)
    UpdateArmorer;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x005598D0, &OpenSHC::Global::UpdateTanner)
    UpdateTanner;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0055A800, &OpenSHC::Global::UpdateCrusaderArcher)
    UpdateCrusaderArcher;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0055C7B0, &OpenSHC::Global::UpdateCrossbowman)
    UpdateCrossbowman;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0055DA50, &OpenSHC::Global::UpdateSpearman)
    UpdateSpearman;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0055F110, &OpenSHC::Global::UpdatePikeman)
    UpdatePikeman;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00560700, &OpenSHC::Global::UpdateMaceman)
    UpdateMaceman;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00561C10, &OpenSHC::Global::UpdateSwordsman)
    UpdateSwordsman;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00562AA0, &OpenSHC::Global::UpdateKnight)
    UpdateKnight;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00563910, &OpenSHC::Global::UpdateLadderman)
    UpdateLadderman;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00564250, &OpenSHC::Global::UpdateEngineer)
    UpdateEngineer;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00566010, &OpenSHC::Global::UpdateMinerIronFetcher)
    UpdateMinerIronFetcher;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00566750, &OpenSHC::Global::UpdatePriest)
    UpdatePriest;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00567320, &OpenSHC::Global::UpdateDrunkard)
    UpdateDrunkard;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00567640, &OpenSHC::Global::UpdateMonk)
    UpdateMonk;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00568320, &OpenSHC::Global::UpdateCatapult)
    UpdateCatapult;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00569410, &OpenSHC::Global::UpdateTrebuchet)
    UpdateTrebuchet;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0056A3F0, &OpenSHC::Global::UpdateMangonel)
    UpdateMangonel;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0056B0E0, &OpenSHC::Global::UpdateLion)
    UpdateLion;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0056B970, &OpenSHC::Global::UpdateHunterDog)
    UpdateHunterDog;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0056C560, &OpenSHC::Global::UpdateLord)
    UpdateLord;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0056E190, &OpenSHC::Global::UpdateJester)
    UpdateJester;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0056ECD0, &OpenSHC::Global::UpdateBallista)
    UpdateBallista;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0056F9B0, &OpenSHC::Global::UpdateCageDog)
    UpdateCageDog;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00570400, &OpenSHC::Global::UpdateArabianArcher)
    UpdateArabianArcher;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00571C00, &OpenSHC::Global::UpdateSlave)
    UpdateSlave;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00572E80, &OpenSHC::Global::UpdateSlinger)
    UpdateSlinger;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x005744D0, &OpenSHC::Global::UpdateAssassin)
    UpdateAssassin;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(short* unitID), false, Address::SHC_3BB0A8C1_0x00575820,
        &OpenSHC::Global::HorseArcher_DoShooting)
    HorseArcher_DoShooting;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00575C40, &OpenSHC::Global::UpdateArabianSwordsman)
    UpdateArabianSwordsman;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x005769F0, &OpenSHC::Global::UpdateFireThrower)
    UpdateFireThrower;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00577CC0, &OpenSHC::Global::UpdateFireBallista)
    UpdateFireBallista;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0057AB50, &OpenSHC::Global::UpdateHorseArcher)
    UpdateHorseArcher;

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
        char*(__cdecl*)(char* string), false, Address::SHC_3BB0A8C1_0x005818EB, &OpenSHC::Global::StringToLowerCase)
    StringToLowerCase;

    MACRO_FUNCTION_RESOLVER(
        int(__cdecl*)(HANDLE hFile), false, Address::SHC_3BB0A8C1_0x005826FB, &OpenSHC::Global::GetFilePtrPos)
    GetFilePtrPos;

} // namespace Global_Func
} // namespace OpenSHC
