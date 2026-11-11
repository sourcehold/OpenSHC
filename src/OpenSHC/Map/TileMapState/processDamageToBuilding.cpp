#include "../TileMapState.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Entities.func.hpp"
#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Version.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_BUILDING;
    using OpenSHC::Map::LogicHelpers::L_CRENEL;
    using OpenSHC::Map::LogicHelpers::L_CRENEL_VARIATIONUnk;
    using OpenSHC::Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE;
    using OpenSHC::Map::LogicHelpers::L_STAIRS;
    using OpenSHC::Map::LogicHelpers::L_STOCKPILEUnk;
    using OpenSHC::Map::LogicHelpers::L_UNKNOWN_WALL_RELATED;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    using OpenSHC::DE::SHCDE::eSFX;
    using OpenSHC::Game::GameMode;
    using OpenSHC::Map::Buildings::BuildingLogicalState;
    using OpenSHC::Map::Entities::EntityType;
    using OpenSHC::Map::Units::States::UnitState;

    // FUNCTION: STRONGHOLDCRUSADER 0x00516B80
    BOOLEnum TileMapState::processDamageToBuilding(int tile, uint xPosition, uint yPosition, int damageUnk,
        int suppressDamage, int playerID, BOOLEnum aiBuildDelayRelated, int unitID)
    {
        BOOLEnum destroyed = FALSE;
        int replaced = 0;
        // a negative player id is a request to spare that player's own team
        BOOLEnum spareOwnTeam = FALSE;
        if (playerID < 0) {
            playerID = -playerID;
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] == -1) {
                spareOwnTeam = TRUE;
            }
        }

        uint logic = this->LogicLayer[tile];
        if ((logic & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) == 0 && this->BuildingLayer[tile] == 0) {
            if ((logic & L_WALL_OR_GATEHOUSE) == 0) {
                destroyed = TRUE;
            } else {
                if ((logic & L_STOCKPILEUnk) != 0) {
                    return FALSE;
                }
                int wallOwner = (this->WallOwnerLayer[tile] & 7) + 1;
                if (spareOwnTeam != FALSE
                    && DAT_GameState::instance.mapAndTime.playerTeams[playerID]
                        == DAT_GameState::instance.mapAndTime.playerTeams[wallOwner]) {
                    return FALSE;
                }
                DAT_GameState::instance.playerDataArray[wallOwner].defensesDamagedByPlayer = (short)playerID;
                if (unitID != 0) {
                    if (DAT_GameState::instance.mapAndTime.playerTeams[wallOwner]
                        == DAT_GameState::instance.mapAndTime.playerTeams[playerID]) {
                        DAT_UnitsState::instance.units[unitID].friendlyFireCounterUnk += 1;
                    } else {
                        DAT_UnitsState::instance.units[unitID].friendlyFireCounterUnk = 0;
                    }
                }
                // a wall standing alone takes half again the damage, a well connected one half
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::countLogicPropertyInSurroundingTiles, this)(
                    tile, yPosition, L_KEEP_NON_MANOR_HOUSE | L_WALL_OR_GATEHOUSE);
                if ((int)this->DAT_CardinalTilesAroundTile <= 1) {
                    damageUnk += damageUnk / 2;
                } else if ((int)this->DAT_CardinalTilesAroundTile > 2) {
                    damageUnk /= 2;
                }
                if (suppressDamage != 0) {
                    damageUnk = 0;
                }
                DAT_TroopValueState::instance.attackInfo.buildingDamageEventCount += 1;
                DAT_GameCore::instance.cowPoisonTrackerUnk += damageUnk * 10;
                if (suppressDamage == 0 && (this->LogicLayer[tile] & L_UNKNOWN_WALL_RELATED) == 0
                    && this->DamageLayer[tile] == 0 && this->HeightLayer[tile] > this->DefaultHeightLayer[tile] + 60) {
                    this->HeightLayer[tile] -= 20;
                }
                for (int hit = 0; hit < damageUnk; hit++) {
                    if (this->HeightLayer[tile] <= this->DefaultHeightLayer[tile]) {
                        MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::destroyEntitiesOnTile,
                            DAT_EntityState::ptr)(tile);
                        this->LogicLayer[tile] &= ~(
                            L_WALL_OR_GATEHOUSE | L_CRENEL | L_STAIRS | L_UNKNOWN_WALL_RELATED | L_CRENEL_VARIATIONUnk);
                        this->HeightLayer[tile] = this->DefaultHeightLayer[tile];
                        this->DamageLayer[tile] = 0;
                        DAT_PathFindingState::instance.toggleUpdateSeparateAreaTileMap = 1;
                        DAT_TileMapState::instance.field_0x554a30 = 1;
                        destroyed = TRUE;
                        break;
                    }
                    this->HeightLayer[tile] -= 1;
                    if ((char)this->DamageLayer[tile] < 200) {
                        this->DamageLayer[tile] += 1;
                    }
                }
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkagesInAllEightDirections,
                    DAT_PathFindingState::ptr)(yPosition, tile);
            }
        } else {

            int buildingID = this->BuildingLayer[tile];
            if (DAT_BuildingsState::instance.buildings[buildingID].logicalState == (BuildingLogicalState)0) {
                return TRUE;
            }
            if (DAT_BuildingsState::instance.buildings[buildingID].logicalState
                == OpenSHC::Map::Buildings::BLS_REMOVE) {
                return TRUE;
            }
            short health = DAT_BuildingsState::instance.buildings[buildingID].currentHealth;
            if (health == 0) {
                return TRUE;
            }
            DAT_GameCore::instance.cowPoisonTrackerUnk += damageUnk * 10;
            if (DAT_BuildingDefinedData::instance
                    .BuildingTypeHasHealth[(short)DAT_BuildingsState::instance.buildings[buildingID].buildingType]
                == 0) {
                return TRUE;
            }
            if ((this->LogicLayer[tile] & 0xf000000) != 0) {
                return TRUE;
            }
            if (spareOwnTeam != FALSE
                && DAT_GameState::instance.mapAndTime.playerTeams[playerID]
                    == DAT_GameState::instance.mapAndTime
                        .playerTeams[DAT_BuildingsState::instance.buildings[buildingID].owner]) {
                return FALSE;
            }
            DAT_BuildingsState::instance.buildings[buildingID].currentHealth = health - (short)damageUnk;

            if (aiBuildDelayRelated == TRUE
                && (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                        == OpenSHC::Map::Buildings::BT_GATEHOUSELARGE
                    || DAT_BuildingsState::instance.buildings[buildingID].buildingType
                        == OpenSHC::Map::Buildings::BT_GATEHOUSESMALL)) {
                // a damaged gatehouse loses its drawbridges straight away
                int bridge = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::findParticularBuilding,
                    DAT_BuildingsState::ptr)(DAT_BuildingsState::instance.buildings[buildingID].owner,
                    (short)DAT_BuildingsState::instance.buildings[buildingID].x,
                    (short)DAT_BuildingsState::instance.buildings[buildingID].y,
                    DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight,
                    OpenSHC::Map::Buildings::BT_DRAWBRIDGE, 0);
                if (bridge != 0) {
                    this->showNoRubbleWhenDestroyingBuilding
                        = DAT_BuildingDefinedData::instance.BuildingShowRubbleWhenDestroyed
                              [(short)DAT_BuildingsState::instance.buildings[bridge].buildingType]
                        == 0;
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Buildings::BuildingsState_Func::destroyBuilding, DAT_BuildingsState::ptr)(bridge);
                    int second = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::findParticularBuilding,
                        DAT_BuildingsState::ptr)(DAT_BuildingsState::instance.buildings[buildingID].owner,
                        (short)DAT_BuildingsState::instance.buildings[buildingID].x,
                        (short)DAT_BuildingsState::instance.buildings[buildingID].y,
                        DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight,
                        OpenSHC::Map::Buildings::BT_DRAWBRIDGE, bridge);
                    if (second != 0) {
                        this->showNoRubbleWhenDestroyingBuilding
                            = DAT_BuildingDefinedData::instance.BuildingShowRubbleWhenDestroyed
                                  [(short)DAT_BuildingsState::instance.buildings[second].buildingType]
                            == 0;
                        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::destroyBuilding,
                            DAT_BuildingsState::ptr)(second);
                    }
                }
            }

            switch (DAT_BuildingsState::instance.buildings[buildingID].buildingType) {
            case OpenSHC::Map::Buildings::BT_GATEHOUSELARGE:
            case OpenSHC::Map::Buildings::BT_GATEHOUSESMALL:
            case OpenSHC::Map::Buildings::BT_TOWER1:
            case OpenSHC::Map::Buildings::BT_TOWER2:
            case OpenSHC::Map::Buildings::BT_TOWER3:
            case OpenSHC::Map::Buildings::BT_TOWER4:
            case OpenSHC::Map::Buildings::BT_TOWER5:
                DAT_GameState::instance.playerDataArray[DAT_BuildingsState::instance.buildings[buildingID].owner]
                    .defensesDamagedByPlayer = (short)playerID;
                break;
            default:
                break;
            }
            if (unitID != 0) {
                if (DAT_GameState::instance.mapAndTime
                        .playerTeams[DAT_BuildingsState::instance.buildings[buildingID].owner]
                    == DAT_GameState::instance.mapAndTime.playerTeams[playerID]) {
                    DAT_UnitsState::instance.units[unitID].friendlyFireCounterUnk += 1;
                } else {
                    DAT_UnitsState::instance.units[unitID].friendlyFireCounterUnk = 0;
                }
            }

            short remaining = DAT_BuildingsState::instance.buildings[buildingID].currentHealth;
            if (remaining > 0) {
                // a siege tower's rider takes the damage with it
                if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                        == OpenSHC::Map::Buildings::BT_SIEGETOWER_PLACED
                    && DAT_BuildingsState::instance.buildings[buildingID].unitRefID != 0
                    && DAT_BuildingsState::instance.buildings[buildingID].unitRefUID
                        == DAT_UnitsState::instance.units[DAT_BuildingsState::instance.buildings[buildingID].unitRefID]
                            .uid
                    && DAT_BuildingsState::instance.buildings[buildingID].maxHealth != 0) {
                    DAT_UnitsState::instance.units[DAT_BuildingsState::instance.buildings[buildingID].unitRefID].health
                        = ((int)remaining
                              * DAT_UnitsState::instance
                                  .units[DAT_BuildingsState::instance.buildings[buildingID].unitRefID]
                                  .maxHealth)
                        / (int)DAT_BuildingsState::instance.buildings[buildingID].maxHealth;
                }
            } else {

                if (DAT_BuildingsState::instance.buildings[buildingID].owner
                    == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                    MACRO_CALL(OpenSHC::Map::Version_Func::UpdateDestroyedBuildingCountData)(1);
                }
                int owner = DAT_BuildingsState::instance.buildings[buildingID].owner;
                if (aiBuildDelayRelated == TRUE
                    && DAT_GameState::instance.playerDataArray[owner].resourceRebuildDelay == 0) {
                    DAT_GameState::instance.playerDataArray[owner].resourceRebuildDelay = 1;
                }
                int destroyedType = (short)DAT_BuildingsState::instance.buildings[buildingID].buildingType;
                if (destroyedType != OpenSHC::Map::Buildings::BT_UNKNOWN3
                    && (destroyedType <= 85 || destroyedType > 89)) {
                    DAT_GameSynchronyState::instance.finalResults.finalBuildingsBurned[playerID] += 1;
                    DAT_GameSynchronyState::instance.finalResults.finalBuildingsDestroyedWeighted[playerID]
                        += DAT_BuildingDefinedData::instance.BuildingDestroyedScoreWeight[destroyedType];
                    DAT_GameSynchronyState::instance.finalResults.finalBuidingsDestroyed[owner] += 1;
                    DAT_GameState::instance.playerDataArray[owner].attackedByPlayerArrayUnk[playerID][1] += 1;
                }
                switch (DAT_BuildingsState::instance.buildings[buildingID].buildingType) {
                case OpenSHC::Map::Buildings::BT_OILSMELTER:
                case OpenSHC::Map::Buildings::BT_GATEHOUSELARGE:
                case OpenSHC::Map::Buildings::BT_GATEHOUSESMALL:
                case OpenSHC::Map::Buildings::BT_TOWER1:
                case OpenSHC::Map::Buildings::BT_TOWER2:
                case OpenSHC::Map::Buildings::BT_TOWER3:
                case OpenSHC::Map::Buildings::BT_TOWER4:
                case OpenSHC::Map::Buildings::BT_TOWER5:
                    MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::playAnger2BikFromPlayerToPlayer, DAT_AICState::ptr)(
                        owner, playerID);
                    break;
                default:
                    MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::playVictory2BikFromPlayerToPlayer, DAT_AICState::ptr)(
                        owner, playerID);
                }
                if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY
                    && playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID
                    && DAT_GameState::instance.mapAndTime.playerTeams[owner]
                        != DAT_GameState::instance.mapAndTime
                            .playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    && (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                            == OpenSHC::Map::Buildings::BT_TOWER4
                        || DAT_BuildingsState::instance.buildings[buildingID].buildingType
                            == OpenSHC::Map::Buildings::BT_TOWER5
                        || DAT_BuildingsState::instance.buildings[buildingID].buildingType
                            == OpenSHC::Map::Buildings::BT_GATEHOUSELARGE
                        || DAT_BuildingsState::instance.buildings[buildingID].buildingType
                            == OpenSHC::Map::Buildings::BT_CHURCH
                        || DAT_BuildingsState::instance.buildings[buildingID].buildingType
                            == OpenSHC::Map::Buildings::BT_CATHEDRAL)
                    && MACRO_CALL_MEMBER(
                           OpenSHC::Audio::MSS::SoundSystem_Func::shouldSoundXNotBePlaying, DAT_SoundSystemState::ptr)()
                        == FALSE) {
                    MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber1, SEC_RNG::ptr)();
                    if (DAT_GameCore::instance.genieVoiceActive != FALSE) {
                        // "Watch it crumble"
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                            "Genie_36.wav");
                    }
                }

                switch (DAT_BuildingsState::instance.buildings[buildingID].buildingType) {
                case OpenSHC::Map::Buildings::BT_TOWER1: {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processDamageToUnitsOnBuilding,
                        DAT_BuildingsState::ptr)(buildingID, 25);
                    int towerOwner = DAT_BuildingsState::instance.buildings[buildingID].owner;
                    int towerX = (short)DAT_BuildingsState::instance.buildings[buildingID].x;
                    DAT_BuildingsState::instance.buildings[buildingID].noRubble = 0;
                    int towerY = (short)DAT_BuildingsState::instance.buildings[buildingID].y;
                    MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::deleteBuilding,
                        DAT_BuildingsState::ptr)(buildingID);
                    // a destroyed tower leaves its ruin behind
                    MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::placeBuilding, this)(
                        towerOwner, towerX, towerY, OpenSHC::Commands::M_MAPPER_TOWER1_DESTROYED, 3, 15);
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        towerX, towerY, OpenSHC::DE::SHCDE::FX_TOWER_SMASH);
                    replaced = 1;
                    destroyed = TRUE;
                } break;
                case OpenSHC::Map::Buildings::BT_TOWER2: {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processDamageToUnitsOnBuilding,
                        DAT_BuildingsState::ptr)(buildingID, 50);
                    int towerOwner = DAT_BuildingsState::instance.buildings[buildingID].owner;
                    int towerX = (short)DAT_BuildingsState::instance.buildings[buildingID].x;
                    DAT_BuildingsState::instance.buildings[buildingID].noRubble = 0;
                    int towerY = (short)DAT_BuildingsState::instance.buildings[buildingID].y;
                    MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::deleteBuilding,
                        DAT_BuildingsState::ptr)(buildingID);
                    // a destroyed tower leaves its ruin behind
                    MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::placeBuilding, this)(
                        towerOwner, towerX, towerY, OpenSHC::Commands::M_MAPPER_TOWER2_DESTROYED, 4, 15);
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        towerX, towerY, OpenSHC::DE::SHCDE::FX_TOWER_SMASH);
                    replaced = 1;
                    destroyed = TRUE;
                } break;
                case OpenSHC::Map::Buildings::BT_TOWER3: {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processDamageToUnitsOnBuilding,
                        DAT_BuildingsState::ptr)(buildingID, 50);
                    int towerOwner = DAT_BuildingsState::instance.buildings[buildingID].owner;
                    int towerX = (short)DAT_BuildingsState::instance.buildings[buildingID].x;
                    DAT_BuildingsState::instance.buildings[buildingID].noRubble = 0;
                    int towerY = (short)DAT_BuildingsState::instance.buildings[buildingID].y;
                    MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::deleteBuilding,
                        DAT_BuildingsState::ptr)(buildingID);
                    // a destroyed tower leaves its ruin behind
                    MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::placeBuilding, this)(
                        towerOwner, towerX, towerY, OpenSHC::Commands::M_MAPPER_TOWER3_DESTROYED, 5, 15);
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        towerX, towerY, OpenSHC::DE::SHCDE::FX_TOWER_SMASH);
                    replaced = 1;
                    destroyed = TRUE;
                } break;
                case OpenSHC::Map::Buildings::BT_TOWER4: {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processDamageToUnitsOnBuilding,
                        DAT_BuildingsState::ptr)(buildingID, 50);
                    int towerOwner = DAT_BuildingsState::instance.buildings[buildingID].owner;
                    int towerX = (short)DAT_BuildingsState::instance.buildings[buildingID].x;
                    DAT_BuildingsState::instance.buildings[buildingID].noRubble = 0;
                    int towerY = (short)DAT_BuildingsState::instance.buildings[buildingID].y;
                    MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::deleteBuilding,
                        DAT_BuildingsState::ptr)(buildingID);
                    // a destroyed tower leaves its ruin behind
                    MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::placeBuilding, this)(
                        towerOwner, towerX, towerY, OpenSHC::Commands::M_MAPPER_TOWER4_DESTROYED, 6, 15);
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        towerX, towerY, OpenSHC::DE::SHCDE::FX_TOWER_SMASH);
                    replaced = 1;
                    destroyed = TRUE;
                } break;
                case OpenSHC::Map::Buildings::BT_TOWER5: {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processDamageToUnitsOnBuilding,
                        DAT_BuildingsState::ptr)(buildingID, 50);
                    int towerOwner = DAT_BuildingsState::instance.buildings[buildingID].owner;
                    int towerX = (short)DAT_BuildingsState::instance.buildings[buildingID].x;
                    DAT_BuildingsState::instance.buildings[buildingID].noRubble = 0;
                    int towerY = (short)DAT_BuildingsState::instance.buildings[buildingID].y;
                    MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::deleteBuilding,
                        DAT_BuildingsState::ptr)(buildingID);
                    // a destroyed tower leaves its ruin behind
                    MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::placeBuilding, this)(
                        towerOwner, towerX, towerY, OpenSHC::Commands::M_MAPPER_TOWER5_DESTROYED, 6, 15);
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        towerX, towerY, OpenSHC::DE::SHCDE::FX_TOWER_SMASH);
                    replaced = 1;
                    destroyed = TRUE;
                } break;
                case OpenSHC::Map::Buildings::BT_OILSMELTER: {
                    int oilAmount = DAT_BuildingsState::instance.buildings[buildingID].resources[7];
                    if (oilAmount == 0) {
                        // an empty smelter goes like any other building (the original shares that block)
                        goto destroyNormally;
                    }
                    // a smelter with oil in it goes up, and a full one throws burning oil about
                    uint smelterTile = DAT_BuildingsState::instance.buildings[buildingID].currentTilePositionAdjusted;
                    int smelterX = (short)DAT_BuildingsState::instance.buildings[buildingID].x;
                    int smelterOwner = DAT_BuildingsState::instance.buildings[buildingID].owner;
                    DAT_BuildingsState::instance.buildings[buildingID].noRubble = 0;
                    int smelterY = (short)DAT_BuildingsState::instance.buildings[buildingID].y;
                    MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::deleteBuilding,
                        DAT_BuildingsState::ptr)(buildingID);
                    if (oilAmount <= 4) {
                        MACRO_CALL(OpenSHC::Map::Entities_Func::SetPlaceOnFire)(smelterOwner, smelterX * 8 + 16,
                            smelterY * 8 + 16, DAT_TileMapState::instance.HeightLayer[smelterTile], 3);
                    } else {
                        MACRO_CALL(OpenSHC::Map::Entities_Func::SetPlaceOnFire)(smelterOwner, smelterX * 8 + 16,
                            smelterY * 8 + 16, DAT_TileMapState::instance.HeightLayer[smelterTile], 5);
                        MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::spawnProjectileEntity,
                            DAT_EntityState::ptr)(0, smelterOwner, 0, smelterX * 8 + 16, smelterY * 8 + 16,
                            DAT_TileMapState::instance.HeightLayer[smelterTile], 0, 0, 0,
                            OpenSHC::Map::Entities::EntityTypeInt__ET_EXPLOSION, 0);
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        smelterX, smelterY, OpenSHC::DE::SHCDE::FX_IGNITE_PITCH);
                    destroyed = TRUE;
                } break;
                case OpenSHC::Map::Buildings::BT_GATEHOUSELARGE:
                case OpenSHC::Map::Buildings::BT_GATEHOUSESMALL: {
                    int bridge = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::findParticularBuilding,
                        DAT_BuildingsState::ptr)(DAT_BuildingsState::instance.buildings[buildingID].owner,
                        (short)DAT_BuildingsState::instance.buildings[buildingID].x,
                        (short)DAT_BuildingsState::instance.buildings[buildingID].y,
                        DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight,
                        OpenSHC::Map::Buildings::BT_DRAWBRIDGE, 0);
                    if (bridge != 0) {
                        if (DAT_BuildingDefinedData::instance.BuildingShowRubbleWhenDestroyed
                                [(short)DAT_BuildingsState::instance.buildings[bridge].buildingType]
                            != 0) {
                            this->showNoRubbleWhenDestroyingBuilding = FALSE;
                        } else {
                            this->showNoRubbleWhenDestroyingBuilding = TRUE;
                        }
                        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::destroyBuilding,
                            DAT_BuildingsState::ptr)(bridge);
                        int second
                            = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::findParticularBuilding,
                                DAT_BuildingsState::ptr)(DAT_BuildingsState::instance.buildings[buildingID].owner,
                                (short)DAT_BuildingsState::instance.buildings[buildingID].x,
                                (short)DAT_BuildingsState::instance.buildings[buildingID].y,
                                DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight,
                                OpenSHC::Map::Buildings::BT_DRAWBRIDGE, bridge);
                        if (second != 0) {
                            this->showNoRubbleWhenDestroyingBuilding
                                = DAT_BuildingDefinedData::instance.BuildingShowRubbleWhenDestroyed
                                      [(short)DAT_BuildingsState::instance.buildings[second].buildingType]
                                == 0;
                            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::destroyBuilding,
                                DAT_BuildingsState::ptr)(second);
                        }
                    }
                    int gateX = (short)DAT_BuildingsState::instance.buildings[buildingID].x;
                    int gateY = (short)DAT_BuildingsState::instance.buildings[buildingID].y;
                    MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processDamageToUnitsOnBuilding,
                        DAT_BuildingsState::ptr)(buildingID, 50);
                    this->showNoRubbleWhenDestroyingBuilding
                        = DAT_BuildingDefinedData::instance.BuildingShowRubbleWhenDestroyed
                              [(short)DAT_BuildingsState::instance.buildings[buildingID].buildingType]
                        == 0;
                    MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::destroyBuilding,
                        DAT_BuildingsState::ptr)(buildingID);
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        gateX, gateY, OpenSHC::DE::SHCDE::FX_TOWER_SMASH);
                    destroyed = TRUE;
                } break;
                case OpenSHC::Map::Buildings::BT_TUNNEL: {
                    // the tunneller inside is buried where he stands, then the tunnel goes like any other building
                    int tunneller = DAT_BuildingsState::instance.buildings[buildingID].unitRefID;
                    if (DAT_UnitsState::instance.units[tunneller].state.generic
                        != (OpenSHC::Map::Units::States::US_STAND_UPUnk | OpenSHC::Map::Units::States::US_IDLEUnk)) {
                        DAT_UnitsState::instance.units[tunneller].totalSizeOfPathPlan
                            = DAT_UnitsState::instance.units[tunneller].currentIndexInPathPlan;
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::applyTunnelDamageAlongPathPlan,
                            DAT_UnitsState::ptr)(tunneller);
                    }
                    DAT_UnitsState::instance.units[tunneller].state.generic = OpenSHC::Map::Units::States::US_DISAPPEAR;
                    DAT_UnitsState::instance.units[tunneller].disappearFadeAlphaCountdown = 32;
                    DAT_UnitsState::instance.units[tunneller].updateTickTracker = 32;
                }
                default:
                destroyNormally: {
                    int rubbleType = (short)DAT_BuildingsState::instance.buildings[buildingID].buildingType;
                    int rubbleOwner = DAT_BuildingsState::instance.buildings[buildingID].owner;
                    this->showNoRubbleWhenDestroyingBuilding
                        = DAT_BuildingDefinedData::instance.BuildingShowRubbleWhenDestroyed[rubbleType] == 0;
                    MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::destroyBuilding,
                        DAT_BuildingsState::ptr)(buildingID);
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        (short)DAT_BuildingsState::instance.buildings[buildingID].x,
                        (short)DAT_BuildingsState::instance.buildings[buildingID].y,
                        OpenSHC::DE::SHCDE::FX_BUILDING_SMASH);
                    if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY
                        && playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID
                        && DAT_GameState::instance.mapAndTime.playerTeams[rubbleOwner]
                            != DAT_GameState::instance.mapAndTime
                                .playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        && DAT_GameCore::instance.genieVoiceActive != FALSE) {
                        if (rubbleType == OpenSHC::Map::Buildings::BT_GRANARY
                            || rubbleType == OpenSHC::Map::Buildings::BT_ARMORY) {
                            // "Excellent"
                            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                                "Genie_23.wav");
                        }
                        if (rubbleType == OpenSHC::Map::Buildings::BT_MERCENARYPOST
                            || rubbleType == OpenSHC::Map::Buildings::BT_BARRACKS) {
                            // "Bravo"
                            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                                "Genie_24.wav");
                        }
                    }
                    destroyed = TRUE;
                } break;
                case OpenSHC::Map::Buildings::BT_SIEGETOWER_PLACED: {
                    int rider = DAT_BuildingsState::instance.buildings[buildingID].unitRefID;
                    if (rider != 0
                        && DAT_BuildingsState::instance.buildings[buildingID].unitRefUID
                            == DAT_UnitsState::instance.units[rider].uid) {
                        DAT_UnitsState::instance.units[rider].state.generic = OpenSHC::Map::Units::States::US_DISAPPEAR;
                        DAT_UnitsState::instance.units[rider].disappearFadeAlphaCountdown = 0;
                        DAT_UnitsState::instance.units[rider].updateTickTracker = 0;
                        DAT_UnitsState::instance.units[rider].workplaceBuildingID_1 = 0;
                    }
                    DAT_BuildingsState::instance.buildings[buildingID].noRubble = 0;
                    MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::deleteBuilding,
                        DAT_BuildingsState::ptr)(buildingID);
                    destroyed = TRUE;
                } break;
                }
            }
        }
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer,
            DAT_PathFindingState::ptr)(7, xPosition, yPosition);
        return replaced != 0 ? FALSE : destroyed;
    }

}
}
