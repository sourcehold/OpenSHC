/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Game/Skirmish/SkirmishDefinedData.hpp'
*/

#pragma once

#include "OpenSHC/AI/AIC/AITribeTypeCountPair.hpp"
#include "OpenSHC/AI/AIC/AIUnitBehaviourRequiredMapEntry.hpp"
#include "OpenSHC/AI/Trading/ResourceAICResourceMappingEntry.hpp"
#include "OpenSHC/AI/Tribes/AIVUnitTypeMaxLocationPair.hpp"
#include "OpenSHC/Game/CampaignTrailMission.hpp"
#include "OpenSHC/Game/Resources/ResourceTypeInt.hpp"
#include "OpenSHC/Game/Skirmish/MaxLordHealthMapEntry.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeInt.hpp"
#include "OpenSHC/Map/Units/EngineerSiegeEngineMapping.hpp"
#include "OpenSHC/Map/Units/UnitTypeInt.hpp"

namespace OpenSHC {
namespace Game {
    namespace Skirmish {

        using OpenSHC::AI::AIC::AITribeTypeCountPair;
        using OpenSHC::AI::AIC::AIUnitBehaviourRequiredMapEntry;
        using OpenSHC::AI::Trading::ResourceAICResourceMappingEntry;
        using OpenSHC::AI::Tribes::AIVUnitTypeMaxLocationPair;
        using OpenSHC::Game::CampaignTrailMission;
        using OpenSHC::Game::Resources::ResourceTypeInt;
        using OpenSHC::Game::Skirmish::MaxLordHealthMapEntry;
        using OpenSHC::Map::Buildings::BuildingTypeInt;
        using OpenSHC::Map::Units::EngineerSiegeEngineMapping;
        using OpenSHC::Map::Units::UnitTypeInt;

#pragma pack(push, 1)
        // SIZE: 0x0000401C
        typedef struct SkirmishDefinedData {

            UnitTypeInt RangedAndArmoredUnits[7]; // 0x00000000 length: 28
            MaxLordHealthMapEntry MaxLordHealthMapping[17]; // 0x0000001C length: 136
            char** field2_0xa4; // 0x000000A4 length: 4
            char** field3_0xa8; // 0x000000A8 length: 4
            char** field4_0xac; // 0x000000AC length: 4
            char** field5_0xb0; // 0x000000B0 length: 4
            char** field6_0xb4; // 0x000000B4 length: 4
            char** field7_0xb8; // 0x000000B8 length: 4
            char** field8_0xbc; // 0x000000BC length: 4
            char** field9_0xc0; // 0x000000C0 length: 4
            char** field10_0xc4; // 0x000000C4 length: 4
            char** field11_0xc8; // 0x000000C8 length: 4
            char** field12_0xcc; // 0x000000CC length: 4
            char** field13_0xd0; // 0x000000D0 length: 4
            char** field14_0xd4; // 0x000000D4 length: 4
            char** field15_0xd8; // 0x000000D8 length: 4
            char** field16_0xdc; // 0x000000DC length: 4
            char** field17_0xe0; // 0x000000E0 length: 4
            char** field18_0xe4; // 0x000000E4 length: 4
            int AIUnitBehaviourTypeMapping[11]; // 0x000000E8 length: 44
            CampaignTrailMission SkirmishTrailMissions[50]; // 0x00000114 length: 7200
            CampaignTrailMission WarchestTrailMissions[30]; // 0x00001D34 length: 4320
            CampaignTrailMission ExtremeTrailMissions[20]; // 0x00002E14 length: 2880
            ResourceAICResourceMappingEntry AIResourceTradeAICMapping[20]; // 0x00003954 length: 160
            ResourceTypeInt ResourceAcquisitionPreferenceOrder[20]; // 0x000039F4 length: 80
            int field25_0x3a44[6]; // 0x00003A44 length: 24
            AIUnitBehaviourRequiredMapEntry attackUnitRequired[11]; // 0x00003A5C length: 88
            UnitTypeInt SomeAIUnitTypeArray[20]; // 0x00003AB4 length: 80
            int AITribeIDOffsetForUnitType[20]; // 0x00003B04 length: 80
            EngineerSiegeEngineMapping SiegeEngineMetaInfoArray[4]; // 0x00003B54 length: 64
            UnitTypeInt DefenseTribesUnitTypeArray[20]; // 0x00003B94 length: 80
            AIVUnitTypeMaxLocationPair MaxAIVLocationForRangedUnits[6]; // 0x00003BE4 length: 48
            AIVUnitTypeMaxLocationPair MaxAIVLocationForGroundUnits[6]; // 0x00003C14 length: 48
            AIVUnitTypeMaxLocationPair MaxAIVLocationForPatrolUnits[3]; // 0x00003C44 length: 24
            int TribeTypeID[6]; // 0x00003C5C length: 24
            BuildingTypeInt BuildingTargetPrioritySet1[46]; // 0x00003C74 length: 184
            BuildingTypeInt BuildingTargetPrioritySet2[46]; // 0x00003D2C length: 184
            BuildingTypeInt BuildingTargetPrioritySet3[46]; // 0x00003DE4 length: 184
            AITribeTypeCountPair MaxAttackTribes1[11]; // 0x00003E9C length: 88
            int SiegeEngineCommandBuildingTypes[6]; // 0x00003EF4 length: 24
            int SiegeEngineUnitType[6]; // 0x00003F0C length: 24
            int SiegeEngineTypeRequiredEngineers[6]; // 0x00003F24 length: 24
            AITribeTypeCountPair MaxBreachTribes[11]; // 0x00003F3C length: 88
            int field43_0x3f94[34]; // 0x00003F94 length: 136

        } SkirmishDefinedData;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(SkirmishDefinedData) == 16412, SkirmishDefinedData);
    } // namespace Skirmish
} // namespace Game
} // namespace OpenSHC
