#include "../UnitsState.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Units/Pathfinding/DestinationNeededEnum.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitHasBecomeIdle.hpp"
#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_UpdateUnitsTracker.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::DE::SHCDE::eSFX;
        using OpenSHC::Map::Buildings::BuildingLogicalState;
        using OpenSHC::Map::Buildings::BuildingType;
        using OpenSHC::Map::Buildings::BuildingTypeShort;
        using OpenSHC::Map::Units::UnitInstructionType;
        using OpenSHC::Map::Units::UnitLogicState;
        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::Map::Units::Pathfinding::DestinationNeededEnum;
        using OpenSHC::Map::Units::States::UnitState;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00579300
        void UnitsState::updateUnits()

        {
            /* the 16th of the units checked for being stuck this tick */
            int const _checkedSlotRemainder = (int)SEC_RNG::instance.currentNumber2 % 16;
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                80400, '\0', (void*)((int)(DAT_TileMapState::instance.OccupancyLayer)));
            DAT_GameState::instance.playerDataArray[0].healerCount = 0;
            DAT_GameState::instance.playerDataArray[1].healerCount = 0;
            DAT_GameState::instance.playerDataArray[2].healerCount = 0;
            DAT_GameState::instance.playerDataArray[3].healerCount = 0;
            DAT_GameState::instance.playerDataArray[4].healerCount = 0;
            DAT_GameState::instance.playerDataArray[5].healerCount = 0;
            DAT_GameState::instance.playerDataArray[6].healerCount = 0;
            DAT_GameState::instance.playerDataArray[7].healerCount = 0;
            DAT_GameState::instance.playerDataArray[8].healerCount = 0;
            this->unitCount = 0;
            this->maxUnitCount = 0;
            for (DAT_CurrentUnitSlotID::instance = 1; DAT_CurrentUnitSlotID::instance < 2500;
                DAT_CurrentUnitSlotID::instance = DAT_CurrentUnitSlotID::instance + 1) {
                if (this->units[DAT_CurrentUnitSlotID::instance].logicalState == OpenSHC::Map::Units::ULS_INVISIBLE) {
                    continue;
                }
                this->maxUnitCount = DAT_CurrentUnitSlotID::instance + 1;
                this->units[DAT_CurrentUnitSlotID::instance].field_0x39a = 0;
                this->units[DAT_CurrentUnitSlotID::instance].attackedBy = 0;
                this->units[DAT_CurrentUnitSlotID::instance].huntedBy = 0;
                this->units[DAT_CurrentUnitSlotID::instance].field_0x3dc = 0;
                this->units[DAT_CurrentUnitSlotID::instance].field_0x64 = 0;
                /*
                  This literally does nothing, this variable is not used elsewhere, what the
                   hell?
                 */

                if (this->units[DAT_CurrentUnitSlotID::instance].targetShootRelated != 0) {
                    this->units[DAT_CurrentUnitSlotID::instance].targetShootRelated
                        = this->units[DAT_CurrentUnitSlotID::instance].targetShootRelated - 1;
                }
                if (this->units[DAT_CurrentUnitSlotID::instance].state.generic
                        == OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk
                    && MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::isUnitRegisteredOnItsOwnTile, this)(
                           DAT_CurrentUnitSlotID::instance)
                        == FALSE) {
                    this->lostChimps = this->lostChimps + 1;
                    this->units[DAT_CurrentUnitSlotID::instance].logicalState = OpenSHC::Map::Units::ULS_REMOVE;
                }
                int const _owner = this->units[DAT_CurrentUnitSlotID::instance].owner;
                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[_owner] != -1) {
                    this->units[DAT_CurrentUnitSlotID::instance].siegeTargetPlayerID = 0;
                } else {
                    this->units[DAT_CurrentUnitSlotID::instance].siegeTargetPlayerID
                        = DAT_GameState::instance.playerDataArray[_owner].attackedPlayerID;
                }
                if (this->units[DAT_CurrentUnitSlotID::instance].blessedAmount != 0) {
                    this->units[DAT_CurrentUnitSlotID::instance].blessedAmount
                        = this->units[DAT_CurrentUnitSlotID::instance].blessedAmount - 1;
                    DAT_GameState::instance.playerDataArray[_owner].blessedPeopleCountUnk
                        = DAT_GameState::instance.playerDataArray[_owner].blessedPeopleCountUnk + 1;
                } else if (DAT_UnitPropertiesDefinedData::instance
                               .NotBlessableUnits[this->units[DAT_CurrentUnitSlotID::instance].unitType]
                    == 0) {
                    DAT_GameState::instance.playerDataArray[_owner].unblessedPeopleCountUnk
                        = DAT_GameState::instance.playerDataArray[_owner].unblessedPeopleCountUnk + 1;
                }
                // every 16th unit per tick is checked for being stuck somewhere it cannot be
                if (DAT_CurrentUnitSlotID::instance % 16 == _checkedSlotRemainder) {
                    int const _unitTile = this->units[DAT_CurrentUnitSlotID::instance].tile;
                    if (DAT_TileMapState::instance.PathConnectionLayer[_unitTile] == 0
                        && (DAT_TileMapState::instance.LogicLayer[_unitTile] & 0x40000000U) == 0
                        && this->units[DAT_CurrentUnitSlotID::instance].moveRelatedFlag != 1) {
                        short const _tileBuildingID = DAT_TileMapState::instance.BuildingLayer[_unitTile];
                        if ((_tileBuildingID == 0
                                || (DAT_BuildingsState::instance.buildings[_tileBuildingID].logicalState
                                        == OpenSHC::Map::Buildings::BLS_NORMAL
                                    && DAT_BuildingDefinedData::instance.BuildingIsGateHouseArray[(
                                           short)DAT_BuildingsState::instance.buildings[_tileBuildingID]
                                               .buildingType]
                                        == 0
                                    && DAT_BuildingsState::instance.buildings[_tileBuildingID].buildingType
                                        != OpenSHC::Map::Buildings::BT_DRAWBRIDGE))
                            && this->units[DAT_CurrentUnitSlotID::instance].state.generic
                                != OpenSHC::Map::Units::States::US_DISAPPEAR) {
                            if (this->units[DAT_CurrentUnitSlotID::instance].unitType
                                == OpenSHC::Map::Units::UT_CHICKEN) {
                                MACRO_CALL_MEMBER(
                                    OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y,
                                    OpenSHC::DE::SHCDE::FX_CHICKEN_FLAP);
                            }
                            if ((int)(DAT_GameCore::instance.mapTimeInTicks
                                    - this->units[DAT_CurrentUnitSlotID::instance].time)
                                    >= 1000
                                && this->units[DAT_CurrentUnitSlotID::instance].unitType
                                    != OpenSHC::Map::Units::UT_S_TOWER) {
                                if (this->units[DAT_CurrentUnitSlotID::instance].unitType
                                    == OpenSHC::Map::Units::UT_LORD) {
                                    int const _targetY
                                        = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetY_2;
                                    int const _targetX
                                        = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetX_2;
                                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setPositionOfUnit, this)(
                                        DAT_CurrentUnitSlotID::instance, _targetX, _targetY,
                                        DAT_TileMapState::instance.HeightLayer
                                            [DAT_ViewportRenderState::instance.translationMatrix[_targetY].addXgetTile
                                                + _targetX]);
                                    this->units[DAT_CurrentUnitSlotID::instance].state.generic
                                        = OpenSHC::Map::Units::States::US_IDLEUnk;
                                    this->units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                                        = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET;
                                } else {
                                    this->units[DAT_CurrentUnitSlotID::instance].state.generic
                                        = OpenSHC::Map::Units::States::US_DISAPPEAR;
                                    this->units[DAT_CurrentUnitSlotID::instance].updateTickTracker = 0;
                                }
                            }
                        }
                    }
                    if ((this->units[DAT_CurrentUnitSlotID::instance].unitType == OpenSHC::Map::Units::UT_S_CATAPULT
                            || this->units[DAT_CurrentUnitSlotID::instance].unitType
                                == OpenSHC::Map::Units::UT_S_FBALLISTA)
                        && (DAT_TileMapState::instance.LogicLayer[this->units[DAT_CurrentUnitSlotID::instance].tile]
                               & 0x50000000U)
                            != 0) {
                        this->units[DAT_CurrentUnitSlotID::instance].state.generic
                            = OpenSHC::Map::Units::States::US_DISAPPEAR;
                        this->units[DAT_CurrentUnitSlotID::instance].updateTickTracker = 0;
                    }
                }
                if (this->units[DAT_CurrentUnitSlotID::instance].logicalState == OpenSHC::Map::Units::ULS_NORMAL
                    && (this->units[DAT_CurrentUnitSlotID::instance].x == 0
                        || this->units[DAT_CurrentUnitSlotID::instance].y == 0
                        || this->units[DAT_CurrentUnitSlotID::instance].tile < 0)) {
                    this->units[DAT_CurrentUnitSlotID::instance].state.generic
                        = OpenSHC::Map::Units::States::US_DISAPPEAR;
                    this->units[DAT_CurrentUnitSlotID::instance].updateTickTracker = 0;
                }
            }
            for (DAT_CurrentUnitSlotID::instance = 1; DAT_CurrentUnitSlotID::instance < this->maxUnitCount;
                DAT_CurrentUnitSlotID::instance = DAT_CurrentUnitSlotID::instance + 1) {
                if (this->units[DAT_CurrentUnitSlotID::instance].logicalState == OpenSHC::Map::Units::ULS_INVISIBLE) {
                    continue;
                }
                if (this->units[DAT_CurrentUnitSlotID::instance].state.generic
                    == OpenSHC::Map::Units::States::US_MELEE_ATTACK) {
                    int const _attackedUnitID = this->units[DAT_CurrentUnitSlotID::instance].attackedUnitID;
                    this->units[_attackedUnitID].attackedBy = this->units[_attackedUnitID].attackedBy + 1;
                    if (this->units[_attackedUnitID].attackedUnitID != DAT_CurrentUnitSlotID::instance) {
                        this->units[DAT_CurrentUnitSlotID::instance].attackedBy
                            = this->units[DAT_CurrentUnitSlotID::instance].attackedBy + 1;
                    }
                    if (this->units[_attackedUnitID].attackedBy == 1 && this->units[_attackedUnitID].isStalked == 0) {
                        DAT_GameCore::instance.cowPoisonTrackerUnk = DAT_GameCore::instance.cowPoisonTrackerUnk + 1;
                    }
                }
                short const _huntedUnitID = this->units[DAT_CurrentUnitSlotID::instance].movementType_OR_targetUnitID;
                if (_huntedUnitID != 0) {
                    this->units[_huntedUnitID].huntedBy = this->units[_huntedUnitID].huntedBy + 1;
                }
                short const _unknownUnitID = this->units[DAT_CurrentUnitSlotID::instance].field_0x3de;
                if (_unknownUnitID != 0) {
                    this->units[_unknownUnitID].field_0x3dc = this->units[_unknownUnitID].field_0x3dc + 1;
                }
                if (this->units[DAT_CurrentUnitSlotID::instance].field_0xd0 > 0) {
                    this->units[DAT_CurrentUnitSlotID::instance].field_0xd0
                        = this->units[DAT_CurrentUnitSlotID::instance].field_0xd0 - 1;
                }
            }
            uint _tick0To64 = DAT_GameCore::instance.mapTimeInTicks & 0x3f;
            for (int _playerID = 1; _playerID < 9; _playerID = _playerID + 1) {
                DAT_GameState::instance.playerDataArray[_playerID].totalTroopsType0 = 0;
                DAT_GameState::instance.playerDataArray[_playerID].idlePeasantsCount = 0;
                DAT_GameState::instance.playerDataArray[_playerID].totalDefensiveTroopsUnk = 0;
                DAT_GameState::instance.playerDataArray[_playerID].totalRaidingTroopsUnk = 0;
                DAT_GameState::instance.playerDataArray[_playerID].totalAttackTroops = 0;
                DAT_GameState::instance.playerDataArray[_playerID].totalTroopsType6 = 0;
                DAT_GameState::instance.playerDataArray[_playerID].totalTroopsType7 = 0;
                DAT_GameState::instance.playerDataArray[_playerID].field_0x2b58 = 0;
                DAT_GameState::instance.playerDataArray[_playerID].engineerCountRelated = 0;
                DAT_GameState::instance.playerDataArray[_playerID].totalAttackingEngineerTroops = 0;
                DAT_GameState::instance.playerDataArray[_playerID].unknownHarrassingSiegeRelated = 0;
                DAT_GameState::instance.playerDataArray[_playerID].totalDiggingUnitTroops = 0;
                DAT_GameState::instance.playerDataArray[_playerID].totalAssassinTroops = 0;
                DAT_GameState::instance.playerDataArray[_playerID].totalUnit2Troops = 0;
                DAT_GameState::instance.playerDataArray[_playerID].totalLaddermenTroops = 0;
                DAT_GameState::instance.playerDataArray[_playerID].totalTunnelerTroops = 0;
                DAT_GameState::instance.playerDataArray[_playerID].totalUnitPatrolTroops = 0;
                DAT_GameState::instance.playerDataArray[_playerID].totalUnitBackupTroops = 0;
                DAT_GameState::instance.playerDataArray[_playerID].totalUnitEngageTroops = 0;
                DAT_GameState::instance.playerDataArray[_playerID].totalUnitSiegeDefTroops = 0;
                DAT_GameState::instance.playerDataArray[_playerID].totalMaxDefaultTroops = 0;
                DAT_GameState::instance.playerDataArray[_playerID].harassingSiegeEnginesCountUnk = 0;
                if (_tick0To64 == 0) {
                    DAT_GameState::instance.playerDataArray[_playerID].totalTroopValue = 0;
                }
            }
            for (DAT_CurrentUnitSlotID::instance = 1; DAT_CurrentUnitSlotID::instance < this->maxUnitCount;
                DAT_CurrentUnitSlotID::instance = DAT_CurrentUnitSlotID::instance + 1) {
                if (this->units[DAT_CurrentUnitSlotID::instance].logicalState == OpenSHC::Map::Units::ULS_INVISIBLE) {
                    continue;
                }
                this->unitCount = this->unitCount + 1;
                if (this->units[DAT_CurrentUnitSlotID::instance].field_0x90 != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::stampOccupancyFlagOnSurroundingTiles, this)(
                        DAT_CurrentUnitSlotID::instance);
                }
                DAT_TileMapState::instance.OccupancyLayer[this->units[DAT_CurrentUnitSlotID::instance].tile]
                    = DAT_TileMapState::instance.OccupancyLayer[this->units[DAT_CurrentUnitSlotID::instance].tile]
                    | this->units[DAT_CurrentUnitSlotID::instance].occupancyOrFlag;
                if (this->units[DAT_CurrentUnitSlotID::instance].isSelectable_OR_matchTime != 0) {
                    int const _ownerID = this->units[DAT_CurrentUnitSlotID::instance].owner;
                    if ((DAT_GameCore::instance.mapTimeInTicks & 0x3f) == 0) {
                        DAT_GameState::instance.playerDataArray[_ownerID].totalTroopValue += MACRO_CALL_MEMBER(
                            OpenSHC::Map::Units::TroopValueState_Func::getValueOfTroopType, DAT_TroopValueState::ptr)(
                            (UnitType)(short)this->units[DAT_CurrentUnitSlotID::instance].unitType);
                        if (this->units[DAT_CurrentUnitSlotID::instance].firstNameIndex <= 0) {
                            /*
                              Every 0x3f ticks, assign names to citizen units
                             */

                            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::assignNameToUnit, this)(
                                DAT_CurrentUnitSlotID::instance);
                        }
                    }
                    if (this->units[DAT_CurrentUnitSlotID::instance].unitType == OpenSHC::Map::Units::UT_A_HARCHER) {
                        DAT_TileMapState::instance.SEC_TileMap1104[this->units[DAT_CurrentUnitSlotID::instance].tile]
                            = 6;
                    } else if (this->units[DAT_CurrentUnitSlotID::instance].unitType
                        == OpenSHC::Map::Units::UT_A_FIRETHROWER) {
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::writeSixToTileMap1104InAllDirections,
                            this)(DAT_CurrentUnitSlotID::instance, 6);
                    }
                    if (this->units[DAT_CurrentUnitSlotID::instance].unitType != OpenSHC::Map::Units::UT_LORD) {
                        short _aiBehaviour = this->units[DAT_CurrentUnitSlotID::instance].aiUnitBehaviourType;
                        if (_aiBehaviour == 10) {
                            DAT_GameState::instance.playerDataArray[_ownerID].totalAttackingEngineerTroops
                                = DAT_GameState::instance.playerDataArray[_ownerID].totalAttackingEngineerTroops + 1;
                            DAT_GameState::instance.playerDataArray[_ownerID].totalAttackTroops
                                = DAT_GameState::instance.playerDataArray[_ownerID].totalAttackTroops + 1;
                        } else if (this->units[DAT_CurrentUnitSlotID::instance].unitType
                            != OpenSHC::Map::Units::UT_E_ENGINEER) {
                            /*
                              fixme: TODO, review this bit, cannot be true!
                             */

                            switch (_aiBehaviour) {
                            case 0:
                                DAT_GameState::instance.playerDataArray[_ownerID].totalTroopsType0
                                    = DAT_GameState::instance.playerDataArray[_ownerID].totalTroopsType0 + 1;
                                break;
                            case 1:
                            case 4:
                                DAT_GameState::instance.playerDataArray[_ownerID].totalDefensiveTroopsUnk
                                    = DAT_GameState::instance.playerDataArray[_ownerID].totalDefensiveTroopsUnk + 1;
                                break;
                            case 2:
                                DAT_GameState::instance.playerDataArray[_ownerID].totalRaidingTroopsUnk
                                    = DAT_GameState::instance.playerDataArray[_ownerID].totalRaidingTroopsUnk + 1;
                                break;
                            default:
                                break;
                            case 6:
                                DAT_GameState::instance.playerDataArray[_ownerID].totalTroopsType6
                                    = DAT_GameState::instance.playerDataArray[_ownerID].totalTroopsType6 + 1;
                                break;
                            case 7:
                                DAT_GameState::instance.playerDataArray[_ownerID].totalTroopsType7
                                    = DAT_GameState::instance.playerDataArray[_ownerID].totalTroopsType7 + 1;
                                break;
                            case 11:
                                DAT_GameState::instance.playerDataArray[_ownerID].totalDiggingUnitTroops
                                    = DAT_GameState::instance.playerDataArray[_ownerID].totalDiggingUnitTroops + 1;
                                DAT_GameState::instance.playerDataArray[_ownerID].totalAttackTroops
                                    = DAT_GameState::instance.playerDataArray[_ownerID].totalAttackTroops + 1;
                                break;
                            case 12:
                                DAT_GameState::instance.playerDataArray[_ownerID].totalAssassinTroops
                                    = DAT_GameState::instance.playerDataArray[_ownerID].totalAssassinTroops + 1;
                                DAT_GameState::instance.playerDataArray[_ownerID].totalAttackTroops
                                    = DAT_GameState::instance.playerDataArray[_ownerID].totalAttackTroops + 1;
                                break;
                            case 13:
                                DAT_GameState::instance.playerDataArray[_ownerID].totalUnit2Troops
                                    = DAT_GameState::instance.playerDataArray[_ownerID].totalUnit2Troops + 1;
                                DAT_GameState::instance.playerDataArray[_ownerID].totalAttackTroops
                                    = DAT_GameState::instance.playerDataArray[_ownerID].totalAttackTroops + 1;
                                break;
                            case 14:
                                DAT_GameState::instance.playerDataArray[_ownerID].totalLaddermenTroops
                                    = DAT_GameState::instance.playerDataArray[_ownerID].totalLaddermenTroops + 1;
                                DAT_GameState::instance.playerDataArray[_ownerID].totalAttackTroops
                                    = DAT_GameState::instance.playerDataArray[_ownerID].totalAttackTroops + 1;
                                break;
                            case 15:
                                DAT_GameState::instance.playerDataArray[_ownerID].totalTunnelerTroops
                                    = DAT_GameState::instance.playerDataArray[_ownerID].totalTunnelerTroops + 1;
                                DAT_GameState::instance.playerDataArray[_ownerID].totalAttackTroops
                                    = DAT_GameState::instance.playerDataArray[_ownerID].totalAttackTroops + 1;
                                break;
                            case 16:
                                DAT_GameState::instance.playerDataArray[_ownerID].totalUnitPatrolTroops
                                    = DAT_GameState::instance.playerDataArray[_ownerID].totalUnitPatrolTroops + 1;
                                DAT_GameState::instance.playerDataArray[_ownerID].totalAttackTroops
                                    = DAT_GameState::instance.playerDataArray[_ownerID].totalAttackTroops + 1;
                                break;
                            case 17:
                                DAT_GameState::instance.playerDataArray[_ownerID].totalUnitBackupTroops
                                    = DAT_GameState::instance.playerDataArray[_ownerID].totalUnitBackupTroops + 1;
                                DAT_GameState::instance.playerDataArray[_ownerID].totalAttackTroops
                                    = DAT_GameState::instance.playerDataArray[_ownerID].totalAttackTroops + 1;
                                break;
                            case 18:
                                DAT_GameState::instance.playerDataArray[_ownerID].totalUnitEngageTroops
                                    = DAT_GameState::instance.playerDataArray[_ownerID].totalUnitEngageTroops + 1;
                                DAT_GameState::instance.playerDataArray[_ownerID].totalAttackTroops
                                    = DAT_GameState::instance.playerDataArray[_ownerID].totalAttackTroops + 1;
                                break;
                            case 19:
                                DAT_GameState::instance.playerDataArray[_ownerID].totalUnitSiegeDefTroops
                                    = DAT_GameState::instance.playerDataArray[_ownerID].totalUnitSiegeDefTroops + 1;
                                DAT_GameState::instance.playerDataArray[_ownerID].totalAttackTroops
                                    = DAT_GameState::instance.playerDataArray[_ownerID].totalAttackTroops + 1;
                                break;
                            case 20:
                                DAT_GameState::instance.playerDataArray[_ownerID].totalMaxDefaultTroops
                                    = DAT_GameState::instance.playerDataArray[_ownerID].totalMaxDefaultTroops + 1;
                                DAT_GameState::instance.playerDataArray[_ownerID].totalAttackTroops
                                    = DAT_GameState::instance.playerDataArray[_ownerID].totalAttackTroops + 1;
                                break;
                            case 21:
                                DAT_GameState::instance.playerDataArray[_ownerID].harassingSiegeEnginesCountUnk
                                    = DAT_GameState::instance.playerDataArray[_ownerID].harassingSiegeEnginesCountUnk
                                    + 1;
                            }
                        }
                    }
                }
                if ((this->units[DAT_CurrentUnitSlotID::instance].unitType == OpenSHC::Map::Units::UT_E_ARCHER
                        || this->units[DAT_CurrentUnitSlotID::instance].unitType == OpenSHC::Map::Units::UT_A_ARCHER)
                    && (this->units[DAT_CurrentUnitSlotID::instance].state.generic
                            == OpenSHC::Map::Units::States::US_AIM_WEAPONUnk
                        || this->units[DAT_CurrentUnitSlotID::instance].state.generic
                            == OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk)) {
                    int const _targetID = this->units[DAT_CurrentUnitSlotID::instance].shootTargetedUnit;
                    if (_targetID > 0
                        && this->units[_targetID].uid == this->units[DAT_CurrentUnitSlotID::instance].targetUID) {
                        this->units[_targetID].field_0x39a = 1;
                    }
                }
                if (this->units[DAT_CurrentUnitSlotID::instance].enemyNoticeFrequencyUnk != 0
                    && (DAT_GameState::instance.mapAndTime.totalGameTicksUnk
                           & this->units[DAT_CurrentUnitSlotID::instance].enemyNoticeFrequencyUnk)
                        == (this->units[DAT_CurrentUnitSlotID::instance].fixedRng
                            & this->units[DAT_CurrentUnitSlotID::instance].enemyNoticeFrequencyUnk)) {
                    if (this->units[DAT_CurrentUnitSlotID::instance].owner == 0) {
                        this->units[DAT_CurrentUnitSlotID::instance].closestEnemyMicroDistance = MACRO_CALL_MEMBER(
                            OpenSHC::Map::Units::UnitsState_Func::computeDistanceToNearestEnemyForLegacyMissions, this)(
                            DAT_CurrentUnitSlotID::instance);
                    } else {
                        dword _closestEnemyDistance
                            = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::findNearestEnemyAndHeadTowardsIt,
                                this)(DAT_CurrentUnitSlotID::instance);
                        this->units[DAT_CurrentUnitSlotID::instance].closestEnemyMicroDistance = _closestEnemyDistance;
                        this->units[DAT_CurrentUnitSlotID::instance].assassinsMicroDistanceToEnemyUnk
                            = this->unitDistanceComputationResultUnk;
                    }
                }
                short* const _lookForEnemy = &this->units[DAT_CurrentUnitSlotID::instance].lookForEnemy;
                if (this->units[DAT_CurrentUnitSlotID::instance].lookForEnemy < 0) {
                    *_lookForEnemy = *_lookForEnemy + 1;
                } else {
                    *_lookForEnemy = 0;
                }
                short* const _movementCooldown = &this->units[DAT_CurrentUnitSlotID::instance].movementCooldown;
                if (this->units[DAT_CurrentUnitSlotID::instance].movementCooldown < 0) {
                    *_movementCooldown = *_movementCooldown + 1;
                }
                this->units[DAT_CurrentUnitSlotID::instance].SA = 0;
                if (DAT_TileMapState::instance.refreshRelatedOne != 0) {
                    byte _heightDiv10 = this->units[DAT_CurrentUnitSlotID::instance].heightDiv10;
                    if (_heightDiv10 != 0) {
                        this->units[DAT_CurrentUnitSlotID::instance].field_0x83
                            = this->units[DAT_CurrentUnitSlotID::instance].field_0x83
                            - (char)DAT_UnitPropertiesDefinedData::instance
                                  .field_0x11a24[DAT_UpdateUnitsTracker::instance - _heightDiv10];
                        if ((byte)this->units[DAT_CurrentUnitSlotID::instance].field_0x83 > 100) {
                            this->units[DAT_CurrentUnitSlotID::instance].field_0x83 = 0;
                        }
                        if ((int)DAT_UpdateUnitsTracker::instance
                            >= this->units[DAT_CurrentUnitSlotID::instance].heightDiv10 + 13) {
                            this->units[DAT_CurrentUnitSlotID::instance].heightDiv10 = 0;
                            this->units[DAT_CurrentUnitSlotID::instance].field_0x83 = 0;
                        }
                    }
                }
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::recountActiveFires, DAT_EntityState::ptr)();
            MACRO_CALL_MEMBER(
                OpenSHC::Map::Entities::EntityState_Func::flagUnitsWithActiveEntity, DAT_EntityState::ptr)();
            for (DAT_CurrentUnitSlotID::instance = 1; DAT_CurrentUnitSlotID::instance < this->maxUnitCount;
                DAT_CurrentUnitSlotID::instance = DAT_CurrentUnitSlotID::instance + 1) {
                switch (this->units[DAT_CurrentUnitSlotID::instance].logicalState) {
                case OpenSHC::Map::Units::ULS_INVISIBLE:
                    continue;
                case ((UnitLogicState)5):
                    this->units[DAT_CurrentUnitSlotID::instance].logicalState = ((UnitLogicState)1);
                    continue;
                case ((UnitLogicState)1):
                    this->units[DAT_CurrentUnitSlotID::instance].logicalState = OpenSHC::Map::Units::ULS_NORMAL;
                    break;
                case OpenSHC::Map::Units::ULS_REMOVE:
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::deleteUnit, this)(
                        DAT_CurrentUnitSlotID::instance);
                    continue;
                case OpenSHC::Map::Units::ULS_TRANSITIONING:
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::changeUnitType, this)(
                        DAT_CurrentUnitSlotID::instance);
                    break;
                }
                this->units[DAT_CurrentUnitSlotID::instance].animationTicker
                    = this->units[DAT_CurrentUnitSlotID::instance].animationTicker + 1;
                if (this->units[DAT_CurrentUnitSlotID::instance].animationTicker
                    > this->units[DAT_CurrentUnitSlotID::instance].animationSpeed
                        + this->units[DAT_CurrentUnitSlotID::instance].animationLeapTicksTotal) {
                    this->units[DAT_CurrentUnitSlotID::instance].animationLeapTicksTotal
                        = this->units[DAT_CurrentUnitSlotID::instance].animationTicker;
                    this->units[DAT_CurrentUnitSlotID::instance].animationCycleNumber
                        = this->units[DAT_CurrentUnitSlotID::instance].animationCycleNumber + 1;
                    this->units[DAT_CurrentUnitSlotID::instance].animationCycleNumberHasJustIncremented = TRUE;
                    if (this->units[DAT_CurrentUnitSlotID::instance].animationCycleNumber >= 1000) {
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                    }
                } else {
                    this->units[DAT_CurrentUnitSlotID::instance].animationCycleNumberHasJustIncremented = FALSE;
                }
                if (this->units[DAT_CurrentUnitSlotID::instance].field_0x58 != 0) {
                    this->units[DAT_CurrentUnitSlotID::instance].facingDirectionMapOrientationCorrected
                        = DAT_TileMapState::instance.screenSouthEastDirection
                        - DAT_TileMapState::instance.mapOrientation;
                } else if (this->units[DAT_CurrentUnitSlotID::instance].state.generic
                    == OpenSHC::Map::Units::States::US_MELEE_ATTACK) {
                    this->units[DAT_CurrentUnitSlotID::instance].facingDirectionMapOrientationCorrected
                        = this->units[DAT_CurrentUnitSlotID::instance].orientation
                        - DAT_TileMapState::instance.mapOrientation;
                } else {
                    this->units[DAT_CurrentUnitSlotID::instance].facingDirectionMapOrientationCorrected
                        = this->units[DAT_CurrentUnitSlotID::instance].facingDirection
                        - DAT_TileMapState::instance.mapOrientation;
                }
                if (this->units[DAT_CurrentUnitSlotID::instance].facingDirectionMapOrientationCorrected < 0) {
                    this->units[DAT_CurrentUnitSlotID::instance].facingDirectionMapOrientationCorrected
                        = this->units[DAT_CurrentUnitSlotID::instance].facingDirectionMapOrientationCorrected + 8;
                }
                int const _ownerID = this->units[DAT_CurrentUnitSlotID::instance].owner;
                DAT_GameState::instance.playerDataArray[_ownerID].countEntities
                    = DAT_GameState::instance.playerDataArray[_ownerID].countEntities + 1;
                if (DAT_UnitPropertiesDefinedData::instance
                        .COMPUTER_MANAGED[this->units[DAT_CurrentUnitSlotID::instance].unitType]
                    != 0) {
                    DAT_GameState::instance.playerDataArray[_ownerID].currentPopulation_2
                        = DAT_GameState::instance.playerDataArray[_ownerID].currentPopulation_2 + 1;
                }
                DAT_UnitHasBecomeIdle::instance = 0;
                if (this->units[DAT_CurrentUnitSlotID::instance].dying != 0
                    && this->units[DAT_CurrentUnitSlotID::instance].state.generic
                        != OpenSHC::Map::Units::States::US_DISAPPEAR) {
                    UnitTypeShort const _dyingType = this->units[DAT_CurrentUnitSlotID::instance].unitType;
                    if (_dyingType != OpenSHC::Map::Units::UT_BURNINGMAN
                        && _dyingType != OpenSHC::Map::Units::UT_BURNING_ANIMAL_BIG
                        && _dyingType != OpenSHC::Map::Units::UT_BURNING_ANIMAL_SMALL
                        && (this->units[DAT_CurrentUnitSlotID::instance].state.generic < 111
                            || 117 < this->units[DAT_CurrentUnitSlotID::instance].state.generic)) {
                        this->units[DAT_CurrentUnitSlotID::instance].state.generic
                            = OpenSHC::Map::Units::States::US_DEATH_01;
                        this->units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                    }
                }
                if (DAT_UnitPropertiesDefinedData::instance
                        .COMPUTER_CONTROLLED[this->units[DAT_CurrentUnitSlotID::instance].unitType]
                    != 0) {
                    int const _workplaceID
                        = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].workplaceBuildingID_1;
                    if (DAT_BuildingsState::instance.buildings[_workplaceID].uid
                        != this->units[DAT_CurrentUnitSlotID::instance].workplaceBuildingUID) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::Map::Units::UnitsState_Func::makeUnitStopWalkingByClearingPathProgressState, this)(
                            DAT_CurrentUnitSlotID::instance);
                        if (this->units[DAT_CurrentUnitSlotID::instance].movementRelated >= 8) {
                            this->units[DAT_CurrentUnitSlotID::instance].logicalState
                                = OpenSHC::Map::Units::ULS_TRANSITIONING;
                            this->units[DAT_CurrentUnitSlotID::instance].unitTypeToChangeInto
                                = OpenSHC::Map::Units::UT_PEASANT;
                            this->units[DAT_CurrentUnitSlotID::instance].state_2 = 0;
                            this->units[DAT_CurrentUnitSlotID::instance].workplaceBuildingID_1 = 0;
                            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::clearHiddenFlagAndUpdatePosition,
                                this)(DAT_CurrentUnitSlotID::instance);
                        }
                    } else if (DAT_BuildingsState::instance.buildings[_workplaceID].sleeping != false) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::Map::Units::UnitsState_Func::makeUnitStopWalkingByClearingPathProgressState, this)(
                            DAT_CurrentUnitSlotID::instance);
                        if (this->units[DAT_CurrentUnitSlotID::instance].movementRelated >= 8) {
                            this->units[DAT_CurrentUnitSlotID::instance].logicalState
                                = OpenSHC::Map::Units::ULS_TRANSITIONING;
                            this->units[DAT_CurrentUnitSlotID::instance].unitTypeToChangeInto
                                = OpenSHC::Map::Units::UT_PEASANT;
                            this->units[DAT_CurrentUnitSlotID::instance].state_2 = 0;
                            this->units[DAT_CurrentUnitSlotID::instance].workplaceBuildingID_1 = 0;
                            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::clearHiddenFlagAndUpdatePosition,
                                this)(DAT_CurrentUnitSlotID::instance);
                        }
                        this->units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown = 0;
                    }
                }
                this->units[DAT_CurrentUnitSlotID::instance].field_0x2ac = 0;
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::processMeleeInitiation, this)(
                    DAT_CurrentUnitSlotID::instance);
                this->units[DAT_CurrentUnitSlotID::instance].field_0x2c4
                    = this->units[DAT_CurrentUnitSlotID::instance].state.generic;
                if (this->units[DAT_CurrentUnitSlotID::instance].logicalState
                    != OpenSHC::Map::Units::ULS_TRANSITIONING) {
                    /*
                      Update unit state
                     */

                    (*DAT_UnitPropertiesDefinedData::instance
                            .UpdateUnitFunctions[this->units[DAT_CurrentUnitSlotID::instance].unitType])();
                }
                UnitStateShort const _previousState = this->units[DAT_CurrentUnitSlotID::instance].field_0x2c4;
                // a digger that just left one of its two digging states (0x7c has no name yet)
                if (_previousState != this->units[DAT_CurrentUnitSlotID::instance].state.generic
                    && (_previousState == (UnitState)124 || _previousState == OpenSHC::Map::Units::States::US_DIG)) {
                    int const _digTile = this->units[DAT_CurrentUnitSlotID::instance].digTileTarget;
                    if (DAT_TileMapState::instance.moats[_digTile].owner != 0) {
                        DAT_TileMapState::instance.moats[_digTile].someCountDown
                            = DAT_TileMapState::instance.moats[_digTile].someCountDown - 20;
                    }
                }
                this->units[DAT_CurrentUnitSlotID::instance].field_0x5c = 0;
                if (this->units[DAT_CurrentUnitSlotID::instance].usingTeleport != 0) {
                    /*
                      Climbing
                     */

                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::unitClimbing, this)(
                        DAT_CurrentUnitSlotID::instance);
                } else {
                    int* const _moveTicker = &this->units[DAT_CurrentUnitSlotID::instance].field_0x354;
                    /*
                      Not climbing
                     */

                    *_moveTicker = *_moveTicker + 1;
                    int const _moveTicks = this->units[DAT_CurrentUnitSlotID::instance].field_0x354;
                    if (_moveTicks - this->units[DAT_CurrentUnitSlotID::instance].field_0x350
                        > this->units[DAT_CurrentUnitSlotID::instance].calculatedMovementSpeed
                            + this->units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed
                            + this->units[DAT_CurrentUnitSlotID::instance].moveDelay) {
                        short* const _movementRunUpTime
                            = &this->units[DAT_CurrentUnitSlotID::instance].movementRunUpTime;
                        this->units[DAT_CurrentUnitSlotID::instance].field_0x350 = _moveTicks;
                        if (this->units[DAT_CurrentUnitSlotID::instance].movementRunUpTime > 0) {
                            *_movementRunUpTime = *_movementRunUpTime - 1;
                        } else {
                            *_movementRunUpTime = 0;
                        }
                        int const _moved = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::processUnitMove,
                            this)(DAT_CurrentUnitSlotID::instance,
                            this->units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed);
                        if (_moved != 0) {
                            if (this->units[DAT_CurrentUnitSlotID::instance].state.generic
                                    == OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION
                                && this->units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown != 0
                                && this->units[DAT_CurrentUnitSlotID::instance].fadeType == 0) {
                                this->units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown = 0;
                            }
                            this->units[DAT_CurrentUnitSlotID::instance].field_0x37e
                                = this->units[DAT_CurrentUnitSlotID::instance].field_0x37e + 1;
                            if (this->units[DAT_CurrentUnitSlotID::instance].field_0x37e >= 16) {
                                this->units[DAT_CurrentUnitSlotID::instance].field_0x37e = 0;
                            }
                            this->units[DAT_CurrentUnitSlotID::instance].field_0x37c
                                = this->units[DAT_CurrentUnitSlotID::instance].field_0x37c + 2;
                            if (this->units[DAT_CurrentUnitSlotID::instance].field_0x37c >= 14) {
                                this->units[DAT_CurrentUnitSlotID::instance].field_0x37c = 0;
                            }
                            this->units[DAT_CurrentUnitSlotID::instance].field_0x378
                                = this->units[DAT_CurrentUnitSlotID::instance].field_0x378 + 2;
                            if (this->units[DAT_CurrentUnitSlotID::instance].field_0x378 >= 16) {
                                this->units[DAT_CurrentUnitSlotID::instance].field_0x378 = 0;
                            }
                            this->units[DAT_CurrentUnitSlotID::instance].field_0x3c6
                                = this->units[DAT_CurrentUnitSlotID::instance].field_0x3c6 + 1;
                            if (this->units[DAT_CurrentUnitSlotID::instance].field_0x3c6 >= 18) {
                                this->units[DAT_CurrentUnitSlotID::instance].field_0x3c6 = 0;
                            }
                            this->units[DAT_CurrentUnitSlotID::instance].field_0x428
                                = this->units[DAT_CurrentUnitSlotID::instance].field_0x428 + 1;
                            if (this->units[DAT_CurrentUnitSlotID::instance].field_0x428 >= 24) {
                                this->units[DAT_CurrentUnitSlotID::instance].field_0x428 = 0;
                            }
                        }
                        this->units[DAT_CurrentUnitSlotID::instance].field_0x37a
                            = this->units[DAT_CurrentUnitSlotID::instance].field_0x37a + 1;
                        if (this->units[DAT_CurrentUnitSlotID::instance].field_0x37a >= 12) {
                            this->units[DAT_CurrentUnitSlotID::instance].field_0x37a = 0;
                        }
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::calculateUnitMovementSpeed, this)(
                            DAT_CurrentUnitSlotID::instance);
                    }
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::recomputeUnitStandingHeight, this)(
                    DAT_CurrentUnitSlotID::instance);
                switch (this->units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated) {
                case 16:
                    this->units[DAT_CurrentUnitSlotID::instance].gfxNumber
                        = this->units[DAT_CurrentUnitSlotID::instance].facingDirectionMapOrientationCorrected
                        + this->units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset;
                    this->units[DAT_CurrentUnitSlotID::instance].gfxNumber
                        = this->units[DAT_CurrentUnitSlotID::instance].gfxNumber
                        + this->units[DAT_CurrentUnitSlotID::instance].field_0x37e * 8;
                    if (this->units[DAT_CurrentUnitSlotID::instance].unitType == OpenSHC::Map::Units::UT_A_HARCHER) {
                        this->units[DAT_CurrentUnitSlotID::instance].imageIDUnk
                            = this->units[DAT_CurrentUnitSlotID::instance].gfxNumber;
                    }
                    if (this->units[DAT_CurrentUnitSlotID::instance].unitType == OpenSHC::Map::Units::UT_E_KNIGHT) {
                        this->units[DAT_CurrentUnitSlotID::instance].imageIDUnk
                            = this->units[DAT_CurrentUnitSlotID::instance].gfxNumber;
                        if ((DAT_CurrentUnitSlotID::instance & 1) != 0) {
                            this->units[DAT_CurrentUnitSlotID::instance].imageIDUnk
                                = this->units[DAT_CurrentUnitSlotID::instance].imageIDUnk + 624;
                        } else if (this->units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed != 0
                            && (this->units[DAT_CurrentUnitSlotID::instance].movementType_OR_targetUnitID != 0
                                || this->units[DAT_CurrentUnitSlotID::instance].targetingType
                                    == OpenSHC::Map::Units::UIT_UNIT_ATTACK_UNIT)
                            && this->units[DAT_CurrentUnitSlotID::instance].currentIndexInPathPlan
                                >= this->units[DAT_CurrentUnitSlotID::instance].totalSizeOfPathPlan - 16) {
                            /* a charging knight */
                            this->units[DAT_CurrentUnitSlotID::instance].imageIDUnk
                                = this->units[DAT_CurrentUnitSlotID::instance].imageIDUnk + 128;
                        }
                    }
                    break;
                case 14:
                    this->units[DAT_CurrentUnitSlotID::instance].gfxNumber
                        = this->units[DAT_CurrentUnitSlotID::instance].facingDirectionMapOrientationCorrected
                        + this->units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset;
                    this->units[DAT_CurrentUnitSlotID::instance].gfxNumber
                        = this->units[DAT_CurrentUnitSlotID::instance].gfxNumber
                        + this->units[DAT_CurrentUnitSlotID::instance].field_0x37c * 8;
                    break;
                case 18:
                    this->units[DAT_CurrentUnitSlotID::instance].gfxNumber
                        = this->units[DAT_CurrentUnitSlotID::instance].facingDirectionMapOrientationCorrected
                        + this->units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset;
                    this->units[DAT_CurrentUnitSlotID::instance].gfxNumber
                        = this->units[DAT_CurrentUnitSlotID::instance].gfxNumber
                        + this->units[DAT_CurrentUnitSlotID::instance].field_0x3c6 * 8;
                    break;
                case 24:
                    this->units[DAT_CurrentUnitSlotID::instance].gfxNumber
                        = this->units[DAT_CurrentUnitSlotID::instance].facingDirectionMapOrientationCorrected
                        + this->units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset;
                    this->units[DAT_CurrentUnitSlotID::instance].gfxNumber
                        = this->units[DAT_CurrentUnitSlotID::instance].gfxNumber
                        + this->units[DAT_CurrentUnitSlotID::instance].field_0x428 * 8;
                    break;
                case 8:
                    this->units[DAT_CurrentUnitSlotID::instance].gfxNumber
                        = this->units[DAT_CurrentUnitSlotID::instance].facingDirectionMapOrientationCorrected
                        + this->units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset;
                    this->units[DAT_CurrentUnitSlotID::instance].gfxNumber
                        = this->units[DAT_CurrentUnitSlotID::instance].gfxNumber
                        + this->units[DAT_CurrentUnitSlotID::instance].field_0x378 * 8;
                    if (this->units[DAT_CurrentUnitSlotID::instance].unitType == OpenSHC::Map::Units::UT_A_HARCHER
                        && this->units[DAT_CurrentUnitSlotID::instance].horseArcherShootingVariation != 4
                        && this->units[DAT_CurrentUnitSlotID::instance].horseArcherShootingVariation != 5
                        && this->units[DAT_CurrentUnitSlotID::instance].horseArcherShootingVariation != 6) {
                        this->units[DAT_CurrentUnitSlotID::instance].imageIDUnk
                            = this->units[DAT_CurrentUnitSlotID::instance].gfxNumber;
                    }
                    break;
                case 9:
                    this->units[DAT_CurrentUnitSlotID::instance].gfxNumber
                        = this->units[DAT_CurrentUnitSlotID::instance].facingDirectionMapOrientationCorrected
                        + this->units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset;
                    this->units[DAT_CurrentUnitSlotID::instance].gfxNumber
                        = this->units[DAT_CurrentUnitSlotID::instance].gfxNumber
                        + (this->units[DAT_CurrentUnitSlotID::instance].field_0x378 * 8) / 2;
                    break;
                case 17:
                    this->units[DAT_CurrentUnitSlotID::instance].gfxNumber
                        = this->units[DAT_CurrentUnitSlotID::instance].facingDirectionMapOrientationCorrected * 16
                        + this->units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset;
                    this->units[DAT_CurrentUnitSlotID::instance].gfxNumber
                        = this->units[DAT_CurrentUnitSlotID::instance].gfxNumber
                        + this->units[DAT_CurrentUnitSlotID::instance].field_0x37e;
                    break;
                case 12:
                    this->units[DAT_CurrentUnitSlotID::instance].gfxNumber
                        = this->units[DAT_CurrentUnitSlotID::instance].facingDirectionMapOrientationCorrected
                        + this->units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset;
                    this->units[DAT_CurrentUnitSlotID::instance].gfxNumber
                        = this->units[DAT_CurrentUnitSlotID::instance].gfxNumber
                        + this->units[DAT_CurrentUnitSlotID::instance].field_0x37a * 8;
                    break;
                case 21:
                    this->units[DAT_CurrentUnitSlotID::instance].gfxNumber
                        = this->units[DAT_CurrentUnitSlotID::instance].facingDirectionMapOrientationCorrected
                        + this->units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset;
                    this->units[DAT_CurrentUnitSlotID::instance].gfxNumber
                        = this->units[DAT_CurrentUnitSlotID::instance].gfxNumber
                        + this->units[DAT_CurrentUnitSlotID::instance].field_0x37e * 8;
                    this->units[DAT_CurrentUnitSlotID::instance].imageIDUnk
                        = this->units[DAT_CurrentUnitSlotID::instance].facingDirectionMapOrientationCorrected + 128
                        + this->units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset;
                    this->units[DAT_CurrentUnitSlotID::instance].imageIDUnk
                        = this->units[DAT_CurrentUnitSlotID::instance].imageIDUnk
                        + this->units[DAT_CurrentUnitSlotID::instance].field_0x37e * 8;
                    break;
                case 22: {
                    uint _correctedDirection
                        = (this->units[DAT_CurrentUnitSlotID::instance].facingDirectionMapOrientationCorrected + 4) % 8;
                    this->units[DAT_CurrentUnitSlotID::instance].gfxNumber = _correctedDirection + 337;
                    this->units[DAT_CurrentUnitSlotID::instance].gfxNumber
                        = this->units[DAT_CurrentUnitSlotID::instance].gfxNumber
                        + ((byte)this->units[DAT_CurrentUnitSlotID::instance].field_0x37e & 3) * 8;
                    _correctedDirection
                        = (this->units[DAT_CurrentUnitSlotID::instance].facingDirectionMapOrientationCorrected + 4) % 8;
                    this->units[DAT_CurrentUnitSlotID::instance].imageIDUnk = _correctedDirection + 465;
                    this->units[DAT_CurrentUnitSlotID::instance].imageIDUnk
                        = this->units[DAT_CurrentUnitSlotID::instance].imageIDUnk
                        + this->units[DAT_CurrentUnitSlotID::instance].field_0x37e * 8;
                    break;
                }
                case 19:
                    this->units[DAT_CurrentUnitSlotID::instance].imageIDUnk
                        = this->units[DAT_CurrentUnitSlotID::instance].facingDirectionMapOrientationCorrected
                        + this->units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset;
                    this->units[DAT_CurrentUnitSlotID::instance].imageIDUnk
                        = this->units[DAT_CurrentUnitSlotID::instance].imageIDUnk
                        + (this->units[DAT_CurrentUnitSlotID::instance].field_0x378 / 2) * 8;
                    break;
                case 99:
                    this->units[DAT_CurrentUnitSlotID::instance].imageID2
                        = this->units[DAT_CurrentUnitSlotID::instance].facingDirectionMapOrientationCorrected
                        + this->units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset;
                    this->units[DAT_CurrentUnitSlotID::instance].imageID2
                        = this->units[DAT_CurrentUnitSlotID::instance].imageID2
                        + (this->units[DAT_CurrentUnitSlotID::instance].field_0x378 / 2) * 8;
                    break;
                case 20:
                    this->units[DAT_CurrentUnitSlotID::instance].imageIDUnk
                        = this->units[DAT_CurrentUnitSlotID::instance].facingDirectionMapOrientationCorrected
                        + this->units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset;
                    this->units[DAT_CurrentUnitSlotID::instance].imageIDUnk
                        = this->units[DAT_CurrentUnitSlotID::instance].imageIDUnk
                        + (this->units[DAT_CurrentUnitSlotID::instance].field_0x378 / 2) * 8;
                    break;
                }
                short* const _speedMatching = &this->units[DAT_CurrentUnitSlotID::instance].unitSpeedMatchingRelatedUnk;
                if (this->units[DAT_CurrentUnitSlotID::instance].unitSpeedMatchingRelatedUnk != 0) {
                    *_speedMatching = *_speedMatching - 1;
                }
                byte const _fadeType = this->units[DAT_CurrentUnitSlotID::instance].fadeType;
                if (_fadeType != 0) {
                    if (_fadeType == 1) {
                        this->units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown
                            = DAT_UnitPropertiesDefinedData::instance
                                  .FadeAlpha_Values_1_2[(char)this->units[DAT_CurrentUnitSlotID::instance].fadeCounter];
                    } else {
                        byte _fadeAlpha;
                        if (_fadeType == 2) {
                            _fadeAlpha = DAT_UnitPropertiesDefinedData::instance.FadeAlpha_Values_1_2
                                             [(char)this->units[DAT_CurrentUnitSlotID::instance].fadeCounter];
                        } else {
                            byte const _fadeCounter = this->units[DAT_CurrentUnitSlotID::instance].fadeCounter;
                            if (_fadeType == 3) {
                                _fadeAlpha
                                    = DAT_UnitPropertiesDefinedData::instance.FadeAlpha_Values_3[(char)_fadeCounter];
                            } else {
                                _fadeAlpha
                                    = DAT_UnitPropertiesDefinedData::instance.FadeAlpha_Values_4[(char)_fadeCounter];
                            }
                        }
                        this->units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown = _fadeAlpha;
                    }
                    this->units[DAT_CurrentUnitSlotID::instance].fadeCounter
                        = this->units[DAT_CurrentUnitSlotID::instance].fadeCounter + 1;
                    if ((char)this->units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown <= 0) {
                        this->units[DAT_CurrentUnitSlotID::instance].fadeType = 0;
                        this->units[DAT_CurrentUnitSlotID::instance].fadeCounter = 0;
                    }
                }
            }
            if (DAT_TileMapState::instance.refreshRelatedOne == 0) {
                DAT_UpdateUnitsTracker::instance = 0;
                return;
            }
            DAT_UpdateUnitsTracker::instance = DAT_UpdateUnitsTracker::instance + 1;
        }

    }
}
}
