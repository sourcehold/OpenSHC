#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
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
            int* piVar1;
            short* psVar4;
            UnitTypeShort UVar6;
            uint _unitIDBased8value;
            uint uVar9;
            int _troopValue;
            byte bVar13;
            uint _rngNumber8;
            uint _unitID;
            uint _currentUnitID;
            UnitTypeShort _unitType;
            short _buildingID;
            BuildingTypeShort _buildingType;

            _rngNumber8 = (int)SEC_RNG::instance.currentNumber2 & 0x8000000f;
            if ((int)_rngNumber8 < 0) {
                _rngNumber8 = (_rngNumber8 - 1 | 0xfffffff0) + 1;
            }
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
            DAT_CurrentUnitSlotID::instance = 1;
            do {
                _currentUnitID = DAT_CurrentUnitSlotID::instance;
                if (this->units[DAT_CurrentUnitSlotID::instance].logicalState != OpenSHC::Map::Units::ULS_INVISIBLE) {
                    this->maxUnitCount = DAT_CurrentUnitSlotID::instance + 1;
                    this->units[DAT_CurrentUnitSlotID::instance].field233_0x39a = 0;
                    this->units[DAT_CurrentUnitSlotID::instance].attackedBy = 0;
                    this->units[DAT_CurrentUnitSlotID::instance].huntedBy = 0;
                    this->units[DAT_CurrentUnitSlotID::instance].field265_0x3dc = 0;
                    this->units[DAT_CurrentUnitSlotID::instance].field43_0x64 = 0;
                    /*
                      This literally does nothing, this variable is not used elsewhere, what the
                       hell?
                     */

                    psVar4 = &this->units[DAT_CurrentUnitSlotID::instance].targetShootRelated;
                    if (this->units[DAT_CurrentUnitSlotID::instance].targetShootRelated != 0) {
                        *psVar4 = *psVar4 + -1;
                    }
                    uVar9 = DAT_CurrentUnitSlotID::instance;
                    if ((this->units[DAT_CurrentUnitSlotID::instance].state.generic
                            == OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk)
                        && (_troopValue
                            = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::isUnitRegisteredOnItsOwnTile,
                                this)(DAT_CurrentUnitSlotID::instance),
                            _troopValue == 0)) {
                        this->lostChimps = this->lostChimps + 1;
                        this->units[DAT_CurrentUnitSlotID::instance].logicalState = OpenSHC::Map::Units::ULS_REMOVE;
                        uVar9 = DAT_CurrentUnitSlotID::instance;
                    }
                    _buildingID = this->units[uVar9].owner;
                    if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[_buildingID] == -1) {
                        this->units[uVar9].siegeTargetPlayerID
                            = (short)DAT_GameState::instance.playerDataArray[_buildingID].attackedPlayerID;
                    } else {
                        this->units[uVar9].siegeTargetPlayerID = 0;
                    }
                    if (this->units[DAT_CurrentUnitSlotID::instance].blessedAmount != 0) {
                        this->units[DAT_CurrentUnitSlotID::instance].blessedAmount
                            = this->units[DAT_CurrentUnitSlotID::instance].blessedAmount + -1;
                        DAT_GameState::instance.playerDataArray[_buildingID].blessedPeopleCountUnk
                            = DAT_GameState::instance.playerDataArray[_buildingID].blessedPeopleCountUnk + 1;
                    } else if (DAT_UnitPropertiesDefinedData::instance
                                   .NotBlessableUnits[(short)this->units[DAT_CurrentUnitSlotID::instance].unitType]
                        == 0) {
                        DAT_GameState::instance.playerDataArray[_buildingID].unblessedPeopleCountUnk
                            = DAT_GameState::instance.playerDataArray[_buildingID].unblessedPeopleCountUnk + 1;
                    }
                    _currentUnitID = DAT_CurrentUnitSlotID::instance;
                    _unitIDBased8value = _currentUnitID & 0x8000000f;
                    if ((int)_unitIDBased8value < 0) {
                        _unitIDBased8value = (_unitIDBased8value - 1 | 0xfffffff0) + 1;
                    }
                    if (_unitIDBased8value == _rngNumber8) {
                        int _unitTile = this->units[_currentUnitID].tile;
                        if (DAT_TileMapState::instance.PathConnectionLayer[_unitTile] == 0
                            && (DAT_TileMapState::instance.LogicLayer[_unitTile] & 0x40000000U) == 0
                            && this->units[_currentUnitID].moveRelatedFlag != 1) {
                            _buildingID = DAT_TileMapState::instance.BuildingLayer[_unitTile];
                            if ((_buildingID == 0
                                    || (DAT_BuildingsState::instance.buildings[_buildingID].logicalState
                                            == OpenSHC::Map::Buildings::BLS_NORMAL
                                        && (_buildingType
                                            = DAT_BuildingsState::instance.buildings[_buildingID].buildingType,
                                            DAT_BuildingDefinedData::instance
                                                    .BuildingIsGateHouseArray[(short)_buildingType]
                                                == 0)
                                        && _buildingType != OpenSHC::Map::Buildings::BT_DRAWBRIDGE))
                                && this->units[_currentUnitID].state.generic
                                    != OpenSHC::Map::Units::States::US_DISAPPEAR) {
                                if (this->units[_currentUnitID].unitType == OpenSHC::Map::Units::UT_CHICKEN) {
                                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation,
                                        DAT_SFXState::ptr)((int)this->units[_currentUnitID].x,
                                        (int)(this->units[_currentUnitID].y), OpenSHC::DE::SHCDE::FX_CHICKEN_FLAP);
                                    _currentUnitID = DAT_CurrentUnitSlotID::instance;
                                }
                                if ((999 < (int)(DAT_GameCore::instance.mapTimeInTicks
                                         - this->units[_currentUnitID].time))
                                    && (_unitType = this->units[_currentUnitID].unitType,
                                        _unitType != OpenSHC::Map::Units::UT_S_TOWER)) {
                                    if (_unitType == OpenSHC::Map::Units::UT_LORD) {
                                        uint uVar12 = (uint)this->units[_currentUnitID].targetY_2;
                                        uVar9 = (uint)this->units[_currentUnitID].targetX_2;
                                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setPositionOfUnit,
                                            this)(_currentUnitID, uVar9, uVar12,
                                            (undefined4)((int)(DAT_TileMapState::instance
                                                    .HeightLayer[DAT_ViewportRenderState::instance
                                                                     .translationMatrix[uVar12]
                                                                     .addXgetTile
                                                        + uVar9])));
                                        this->units[DAT_CurrentUnitSlotID::instance].state.generic
                                            = OpenSHC::Map::Units::States::US_IDLEUnk;
                                        this->units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                                            = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET;
                                        _currentUnitID = DAT_CurrentUnitSlotID::instance;
                                    } else {
                                        this->units[_currentUnitID].state.generic
                                            = OpenSHC::Map::Units::States::US_DISAPPEAR;
                                        this->units[DAT_CurrentUnitSlotID::instance].updateTickTracker = 0;
                                        _currentUnitID = DAT_CurrentUnitSlotID::instance;
                                    }
                                }
                            }
                        }
                        UVar6 = this->units[_currentUnitID].unitType;
                        if (((UVar6 == OpenSHC::Map::Units::UT_S_CATAPULT)
                                || (UVar6 == OpenSHC::Map::Units::UT_S_FBALLISTA))
                            && ((DAT_TileMapState::instance.LogicLayer[this->units[_currentUnitID].tile] & 0x50000000U)
                                != 0)) {
                            this->units[_currentUnitID].state.generic = OpenSHC::Map::Units::States::US_DISAPPEAR;
                            this->units[DAT_CurrentUnitSlotID::instance].updateTickTracker = 0;
                            _currentUnitID = DAT_CurrentUnitSlotID::instance;
                        }
                    }
                    if ((this->units[_currentUnitID].logicalState == OpenSHC::Map::Units::ULS_NORMAL)
                        && (((this->units[_currentUnitID].x == 0 || (this->units[_currentUnitID].y == 0))
                            || (this->units[_currentUnitID].tile < 0)))) {
                        this->units[_currentUnitID].state.generic = OpenSHC::Map::Units::States::US_DISAPPEAR;
                        this->units[DAT_CurrentUnitSlotID::instance].updateTickTracker = 0;
                        _currentUnitID = DAT_CurrentUnitSlotID::instance;
                    }
                }
                DAT_CurrentUnitSlotID::instance = _currentUnitID + 1;
            } while ((int)DAT_CurrentUnitSlotID::instance < 2500);
            DAT_CurrentUnitSlotID::instance = 1;
            if (1 < (int)this->maxUnitCount) {
                do {
                    if (this->units[DAT_CurrentUnitSlotID::instance].logicalState
                        != OpenSHC::Map::Units::ULS_INVISIBLE) {
                        if (this->units[DAT_CurrentUnitSlotID::instance].state.generic
                            == OpenSHC::Map::Units::States::US_MELEE_ATTACK) {
                            _buildingID = this->units[DAT_CurrentUnitSlotID::instance].attackedUnitID;
                            psVar4 = &this->units[_buildingID].attackedBy;
                            *psVar4 = *psVar4 + 1;
                            if ((int)this->units[_buildingID].attackedUnitID != DAT_CurrentUnitSlotID::instance) {
                                psVar4 = &this->units[DAT_CurrentUnitSlotID::instance].attackedBy;
                                *psVar4 = *psVar4 + 1;
                            }
                            if ((this->units[_buildingID].attackedBy == 1)
                                && (this->units[_buildingID].isStalked == 0)) {
                                DAT_GameCore::instance.cowPoisonTrackerUnk
                                    = DAT_GameCore::instance.cowPoisonTrackerUnk + 1;
                            }
                        }
                        _buildingID = this->units[DAT_CurrentUnitSlotID::instance].movementType_OR_targetUnitID;
                        if (_buildingID != 0) {
                            psVar4 = &this->units[_buildingID].huntedBy;
                            *psVar4 = *psVar4 + 1;
                        }
                        _buildingID = this->units[DAT_CurrentUnitSlotID::instance].field266_0x3de;
                        if (_buildingID != 0) {
                            psVar4 = &this->units[_buildingID].field265_0x3dc;
                            *psVar4 = *psVar4 + 1;
                        }
                        psVar4 = &this->units[DAT_CurrentUnitSlotID::instance].field97_0xd0;
                        if (0 < this->units[DAT_CurrentUnitSlotID::instance].field97_0xd0) {
                            *psVar4 = *psVar4 + -1;
                        }
                    }
                    DAT_CurrentUnitSlotID::instance = DAT_CurrentUnitSlotID::instance + 1;
                } while ((int)DAT_CurrentUnitSlotID::instance < (int)this->maxUnitCount);
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
                DAT_GameState::instance.playerDataArray[_playerID].field852_0x2b58 = 0;
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
            DAT_CurrentUnitSlotID::instance = 1;
            if (1 < (int)this->maxUnitCount) {
                do {
                    if (this->units[DAT_CurrentUnitSlotID::instance].logicalState
                        != OpenSHC::Map::Units::ULS_INVISIBLE) {
                        this->unitCount = this->unitCount + 1;
                        if (this->units[DAT_CurrentUnitSlotID::instance].field64_0x90 != 0) {
                            MACRO_CALL_MEMBER(
                                OpenSHC::Map::Units::UnitsState_Func::stampOccupancyFlagOnSurroundingTiles, this)(
                                DAT_CurrentUnitSlotID::instance);
                        }
                        uVar9 = DAT_CurrentUnitSlotID::instance;
                        DAT_TileMapState::instance.OccupancyLayer[this->units[DAT_CurrentUnitSlotID::instance].tile]
                            = DAT_TileMapState::instance
                                  .OccupancyLayer[this->units[DAT_CurrentUnitSlotID::instance].tile]
                            | this->units[DAT_CurrentUnitSlotID::instance].occupancyOrFlag;
                        if (this->units[uVar9].isSelectable_OR_matchTime != 0) {
                            _buildingID = this->units[uVar9].owner;
                            if ((DAT_GameCore::instance.mapTimeInTicks & 0x3f) == 0) {
                                piVar1 = &DAT_GameState::instance.playerDataArray[_buildingID].totalTroopValue;
                                _troopValue
                                    = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TroopValueState_Func::getValueOfTroopType,
                                        DAT_TroopValueState::ptr)((UnitType)(short)this->units[uVar9].unitType);
                                *piVar1 = *piVar1 + _troopValue;
                                uVar9 = DAT_CurrentUnitSlotID::instance;
                                if ((char)this->units[DAT_CurrentUnitSlotID::instance].firstNameIndex < '\x01') {
                                    /*
                                      Every 0x3f ticks, assign names to citizen units
                                     */

                                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::assignNameToUnit, this)(
                                        DAT_CurrentUnitSlotID::instance);
                                    uVar9 = DAT_CurrentUnitSlotID::instance;
                                }
                            }
                            UVar6 = this->units[uVar9].unitType;
                            if (UVar6 == OpenSHC::Map::Units::UT_A_HARCHER) {
                                DAT_TileMapState::instance.SEC_TileMap1104[this->units[uVar9].tile] = '\x06';
                            } else if (UVar6 == OpenSHC::Map::Units::UT_A_FIRETHROWER) {
                                MACRO_CALL_MEMBER(
                                    OpenSHC::Map::Units::UnitsState_Func::writeSixToTileMap1104InAllDirections, this)(
                                    uVar9, 6);
                                uVar9 = DAT_CurrentUnitSlotID::instance;
                            }
                            UVar6 = this->units[uVar9].unitType;
                            if (UVar6 != OpenSHC::Map::Units::UT_LORD) {
                                short sVar7 = this->units[uVar9].aiUnitBehaviourType;
                                if (sVar7 == 10) {
                                    piVar1 = &DAT_GameState::instance.playerDataArray[_buildingID]
                                                  .totalAttackingEngineerTroops;
                                    *piVar1 = *piVar1 + 1;
                                    piVar1 = &DAT_GameState::instance.playerDataArray[_buildingID].totalAttackTroops;
                                    *piVar1 = *piVar1 + 1;
                                } else if (UVar6 != OpenSHC::Map::Units::UT_E_ENGINEER) {
                                    /*
                                      fixme: TODO, review this bit, cannot be true!
                                     */

                                    switch (sVar7) {
                                    case 0:
                                        piVar1 = &DAT_GameState::instance.playerDataArray[_buildingID].totalTroopsType0;
                                        *piVar1 = *piVar1 + 1;
                                        break;
                                    case 1:
                                    case 4:
                                        piVar1 = &DAT_GameState::instance.playerDataArray[_buildingID]
                                                      .totalDefensiveTroopsUnk;
                                        *piVar1 = *piVar1 + 1;
                                        break;
                                    case 2:
                                        piVar1 = &DAT_GameState::instance.playerDataArray[_buildingID]
                                                      .totalRaidingTroopsUnk;
                                        *piVar1 = *piVar1 + 1;
                                        break;
                                    default:
                                        break;
                                    case 6:
                                        piVar1 = &DAT_GameState::instance.playerDataArray[_buildingID].totalTroopsType6;
                                        *piVar1 = *piVar1 + 1;
                                        break;
                                    case 7:
                                        piVar1 = &DAT_GameState::instance.playerDataArray[_buildingID].totalTroopsType7;
                                        *piVar1 = *piVar1 + 1;
                                        break;
                                    case 0xb:
                                        piVar1 = &DAT_GameState::instance.playerDataArray[_buildingID]
                                                      .totalDiggingUnitTroops;
                                        *piVar1 = *piVar1 + 1;
                                        piVar1
                                            = &DAT_GameState::instance.playerDataArray[_buildingID].totalAttackTroops;
                                        *piVar1 = *piVar1 + 1;
                                        break;
                                    case 0xc:
                                        piVar1
                                            = &DAT_GameState::instance.playerDataArray[_buildingID].totalAssassinTroops;
                                        *piVar1 = *piVar1 + 1;
                                        piVar1
                                            = &DAT_GameState::instance.playerDataArray[_buildingID].totalAttackTroops;
                                        *piVar1 = *piVar1 + 1;
                                        break;
                                    case 0xd:
                                        piVar1 = &DAT_GameState::instance.playerDataArray[_buildingID].totalUnit2Troops;
                                        *piVar1 = *piVar1 + 1;
                                        piVar1
                                            = &DAT_GameState::instance.playerDataArray[_buildingID].totalAttackTroops;
                                        *piVar1 = *piVar1 + 1;
                                        break;
                                    case 0xe:
                                        piVar1 = &DAT_GameState::instance.playerDataArray[_buildingID]
                                                      .totalLaddermenTroops;
                                        *piVar1 = *piVar1 + 1;
                                        piVar1
                                            = &DAT_GameState::instance.playerDataArray[_buildingID].totalAttackTroops;
                                        *piVar1 = *piVar1 + 1;
                                        break;
                                    case 0xf:
                                        piVar1
                                            = &DAT_GameState::instance.playerDataArray[_buildingID].totalTunnelerTroops;
                                        *piVar1 = *piVar1 + 1;
                                        piVar1
                                            = &DAT_GameState::instance.playerDataArray[_buildingID].totalAttackTroops;
                                        *piVar1 = *piVar1 + 1;
                                        break;
                                    case 0x10:
                                        piVar1 = &DAT_GameState::instance.playerDataArray[_buildingID]
                                                      .totalUnitPatrolTroops;
                                        *piVar1 = *piVar1 + 1;
                                        piVar1
                                            = &DAT_GameState::instance.playerDataArray[_buildingID].totalAttackTroops;
                                        *piVar1 = *piVar1 + 1;
                                        break;
                                    case 0x11:
                                        piVar1 = &DAT_GameState::instance.playerDataArray[_buildingID]
                                                      .totalUnitBackupTroops;
                                        *piVar1 = *piVar1 + 1;
                                        piVar1
                                            = &DAT_GameState::instance.playerDataArray[_buildingID].totalAttackTroops;
                                        *piVar1 = *piVar1 + 1;
                                        break;
                                    case 0x12:
                                        piVar1 = &DAT_GameState::instance.playerDataArray[_buildingID]
                                                      .totalUnitEngageTroops;
                                        *piVar1 = *piVar1 + 1;
                                        piVar1
                                            = &DAT_GameState::instance.playerDataArray[_buildingID].totalAttackTroops;
                                        *piVar1 = *piVar1 + 1;
                                        break;
                                    case 0x13:
                                        piVar1 = &DAT_GameState::instance.playerDataArray[_buildingID]
                                                      .totalUnitSiegeDefTroops;
                                        *piVar1 = *piVar1 + 1;
                                        piVar1
                                            = &DAT_GameState::instance.playerDataArray[_buildingID].totalAttackTroops;
                                        *piVar1 = *piVar1 + 1;
                                        break;
                                    case 0x14:
                                        piVar1 = &DAT_GameState::instance.playerDataArray[_buildingID]
                                                      .totalMaxDefaultTroops;
                                        *piVar1 = *piVar1 + 1;
                                        piVar1
                                            = &DAT_GameState::instance.playerDataArray[_buildingID].totalAttackTroops;
                                        *piVar1 = *piVar1 + 1;
                                        break;
                                    case 0x15:
                                        piVar1 = &DAT_GameState::instance.playerDataArray[_buildingID]
                                                      .harassingSiegeEnginesCountUnk;
                                        *piVar1 = *piVar1 + 1;
                                    }
                                }
                            }
                        }
                        _buildingID = this->units[uVar9].unitType;
                        if ((((_buildingID == OpenSHC::Map::Units::UT_E_ARCHER)
                                 || (_buildingID == OpenSHC::Map::Units::UT_A_ARCHER))
                                && ((_buildingID = this->units[uVar9].state.generic,
                                    _buildingID == OpenSHC::Map::Units::States::US_AIM_WEAPONUnk
                                        || (_buildingID == OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk))))
                            && ((_troopValue = this->units[uVar9].shootTargetedUnit,
                                0 < _troopValue && (this->units[_troopValue].uid == this->units[uVar9].targetUID)))) {
                            this->units[_troopValue].field233_0x39a = 1;
                            uVar9 = DAT_CurrentUnitSlotID::instance;
                        }
                        if ((this->units[uVar9].enemyNoticeFrequencyUnk != 0)
                            && ((DAT_GameState::instance.mapAndTime.totalGameTicksUnk
                                    & this->units[uVar9].enemyNoticeFrequencyUnk)
                                == (this->units[uVar9].fixedRng & this->units[uVar9].enemyNoticeFrequencyUnk))) {
                            if (this->units[uVar9].owner == 0) {
                                _troopValue = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::
                                                                    computeDistanceToNearestEnemyForLegacyMissions,
                                    this)(uVar9);
                                this->units[uVar9].closestEnemyMicroDistance = (short)_troopValue;
                                uVar9 = DAT_CurrentUnitSlotID::instance;
                            } else {
                                dword dVar10 = MACRO_CALL_MEMBER(
                                    OpenSHC::Map::Units::UnitsState_Func::findNearestEnemyAndHeadTowardsIt, this)(
                                    uVar9);
                                this->units[DAT_CurrentUnitSlotID::instance].closestEnemyMicroDistance = (short)dVar10;
                                this->units[DAT_CurrentUnitSlotID::instance].assassinsMicroDistanceToEnemyUnk
                                    = this->unitDistanceComputationResultUnk;
                                uVar9 = DAT_CurrentUnitSlotID::instance;
                            }
                        }
                        psVar4 = &this->units[uVar9].lookForEnemy;
                        if (this->units[uVar9].lookForEnemy < 0) {
                            *psVar4 = *psVar4 + 1;
                        } else {
                            *psVar4 = 0;
                        }
                        psVar4 = &this->units[DAT_CurrentUnitSlotID::instance].unknownMovementRelated_0x2d2;
                        if (this->units[DAT_CurrentUnitSlotID::instance].unknownMovementRelated_0x2d2 < 0) {
                            *psVar4 = *psVar4 + 1;
                        }
                        this->units[DAT_CurrentUnitSlotID::instance].SA = 0;
                        if (DAT_TileMapState::instance.refreshRelatedOne != 0) {
                            bVar13 = this->units[DAT_CurrentUnitSlotID::instance].heightDiv10;
                            if (bVar13 != 0) {
                                undefined1* puVar2 = &this->units[DAT_CurrentUnitSlotID::instance].padding_0x83[0];
                                *puVar2 = *puVar2
                                    - *(char*)((int)DAT_UnitPropertiesDefinedData::ptr
                                        + (DAT_UpdateUnitsTracker::instance - (uint)bVar13) * 4 + 0x11a24);
                                if (100 < (byte)this->units[DAT_CurrentUnitSlotID::instance].padding_0x83[0]) {
                                    this->units[DAT_CurrentUnitSlotID::instance].padding_0x83[0] = 0;
                                }
                                if ((int)((byte)this->units[DAT_CurrentUnitSlotID::instance].heightDiv10 + 0xd)
                                    <= DAT_UpdateUnitsTracker::instance) {
                                    this->units[DAT_CurrentUnitSlotID::instance].heightDiv10 = 0;
                                    this->units[DAT_CurrentUnitSlotID::instance].padding_0x83[0] = 0;
                                }
                            }
                        }
                    }
                    DAT_CurrentUnitSlotID::instance = DAT_CurrentUnitSlotID::instance + 1;
                } while ((int)DAT_CurrentUnitSlotID::instance < (int)this->maxUnitCount);
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::recountActiveFires, DAT_EntityState::ptr)();
            MACRO_CALL_MEMBER(
                OpenSHC::Map::Entities::EntityState_Func::flagUnitsWithActiveEntity, DAT_EntityState::ptr)();
            DAT_CurrentUnitSlotID::instance = 1;
            if (1 < (int)this->maxUnitCount) {
                do {
                    switch (this->units[DAT_CurrentUnitSlotID::instance].logicalState) {
                    case OpenSHC::Map::Units::ULS_INVISIBLE:
                        break;
                    case OpenSHC::Map::Units::ULS_REMOVE:
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::deleteUnit, this)(
                            DAT_CurrentUnitSlotID::instance);
                        break;
                    case ((UnitLogicState)5):
                        this->units[DAT_CurrentUnitSlotID::instance].logicalState = ((UnitLogicState)1);
                        break;
                    default:
                        if (this->units[DAT_CurrentUnitSlotID::instance].logicalState
                            == OpenSHC::Map::Units::ULS_TRANSITIONING) {
                            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::changeUnitType, this)(
                                DAT_CurrentUnitSlotID::instance);
                        } else if (this->units[DAT_CurrentUnitSlotID::instance].logicalState == ((UnitLogicState)1)) {
                            this->units[DAT_CurrentUnitSlotID::instance].logicalState = OpenSHC::Map::Units::ULS_NORMAL;
                        }
                        int* _ptr_animationTicker = &this->units[DAT_CurrentUnitSlotID::instance].animationTicker;
                        *_ptr_animationTicker = *_ptr_animationTicker + 1;
                        int _animationTicker = this->units[DAT_CurrentUnitSlotID::instance].animationTicker;
                        if (this->units[DAT_CurrentUnitSlotID::instance].animationSpeed
                                + this->units[DAT_CurrentUnitSlotID::instance].animationLeapTicksTotal
                            < _animationTicker) {
                            this->units[DAT_CurrentUnitSlotID::instance].animationLeapTicksTotal = _animationTicker;
                            piVar1 = &this->units[DAT_CurrentUnitSlotID::instance].animationCycleNumber;
                            *piVar1 = *piVar1 + 1;
                            this->units[DAT_CurrentUnitSlotID::instance].animationCycleNumberHasJustIncremented = TRUE;
                            uVar9 = DAT_CurrentUnitSlotID::instance;
                            if (999 < this->units[DAT_CurrentUnitSlotID::instance].animationCycleNumber) {
                                this->units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                            }
                        } else {
                            this->units[DAT_CurrentUnitSlotID::instance].animationCycleNumberHasJustIncremented = FALSE;
                            uVar9 = DAT_CurrentUnitSlotID::instance;
                        }
                        _buildingID = (short)DAT_TileMapState::instance.mapOrientation;
                        if (this->units[uVar9].field39_0x58 == 0) {
                            if (this->units[uVar9].state.generic != OpenSHC::Map::Units::States::US_MELEE_ATTACK) {
                                this->units[uVar9].facingDirectionMapOrientationCorrected
                                    = this->units[uVar9].facingDirection - _buildingID;
                            } else {
                                this->units[uVar9].facingDirectionMapOrientationCorrected
                                    = this->units[uVar9].orientation - _buildingID;
                            }
                        } else {
                            this->units[uVar9].facingDirectionMapOrientationCorrected
                                = (short)DAT_TileMapState::instance.field84_0x5548a4 - _buildingID;
                        }
                        psVar4 = &this->units[DAT_CurrentUnitSlotID::instance].facingDirectionMapOrientationCorrected;
                        if (this->units[DAT_CurrentUnitSlotID::instance].facingDirectionMapOrientationCorrected < 0) {
                            *psVar4 = *psVar4 + 8;
                        }
                        uVar9 = DAT_CurrentUnitSlotID::instance;
                        _buildingID = this->units[DAT_CurrentUnitSlotID::instance].owner;
                        piVar1 = &DAT_GameState::instance.playerDataArray[_buildingID].countEntities;
                        *piVar1 = *piVar1 + 1;
                        if (DAT_UnitPropertiesDefinedData::instance.COMPUTER_MANAGED[(short)this->units[uVar9].unitType]
                            != 0) {
                            piVar1 = &DAT_GameState::instance.playerDataArray[_buildingID].currentPopulation_2;
                            *piVar1 = *piVar1 + 1;
                        }
                        DAT_UnitHasBecomeIdle::instance = 0;
                        if (this->units[uVar9].dying != 0
                            && this->units[uVar9].state.generic != OpenSHC::Map::Units::States::US_DISAPPEAR) {
                            UVar6 = this->units[uVar9].unitType;
                            if (UVar6 != OpenSHC::Map::Units::UT_BURNINGMAN
                                && UVar6 != OpenSHC::Map::Units::UT_BURNING_ANIMAL_BIG
                                && UVar6 != OpenSHC::Map::Units::UT_BURNING_ANIMAL_SMALL
                                && ((short)this->units[uVar9].state.generic < 0x6f
                                    || 0x75 < (short)this->units[uVar9].state.generic)) {
                                this->units[uVar9].state.generic = OpenSHC::Map::Units::States::US_DEATH_01;
                                this->units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                                uVar9 = DAT_CurrentUnitSlotID::instance;
                            }
                        }
                        if (DAT_UnitPropertiesDefinedData::instance
                                .COMPUTER_CONTROLLED[(short)this->units[uVar9].unitType]
                            != 0) {
                            _buildingID = this->units[uVar9].workplaceBuildingID_1;
                            if (DAT_BuildingsState::instance.buildings[_buildingID].uid
                                == this->units[uVar9].workplaceBuildingUID) {
                                if (DAT_BuildingsState::instance.buildings[_buildingID].sleeping != false) {
                                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::
                                                          makeUnitStopWalkingByClearingPathProgressState,
                                        this)(uVar9);
                                    if (7 < this->units[DAT_CurrentUnitSlotID::instance].movementRelated) {
                                        this->units[DAT_CurrentUnitSlotID::instance].logicalState
                                            = OpenSHC::Map::Units::ULS_TRANSITIONING;
                                        this->units[DAT_CurrentUnitSlotID::instance].unitTypeToChangeInto
                                            = OpenSHC::Map::Units::UT_PEASANT;
                                        this->units[DAT_CurrentUnitSlotID::instance].state_2 = 0;
                                        this->units[DAT_CurrentUnitSlotID::instance].workplaceBuildingID_1 = 0;
                                        MACRO_CALL_MEMBER(
                                            OpenSHC::Map::Units::UnitsState_Func::clearHiddenFlagAndUpdatePosition,
                                            this)(DAT_CurrentUnitSlotID::instance);
                                    }
                                    this->units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown = 0;
                                    uVar9 = DAT_CurrentUnitSlotID::instance;
                                }
                            } else {
                                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::
                                                      makeUnitStopWalkingByClearingPathProgressState,
                                    this)(uVar9);
                                uVar9 = DAT_CurrentUnitSlotID::instance;
                                if (7 < this->units[DAT_CurrentUnitSlotID::instance].movementRelated) {
                                    this->units[DAT_CurrentUnitSlotID::instance].logicalState
                                        = OpenSHC::Map::Units::ULS_TRANSITIONING;
                                    this->units[DAT_CurrentUnitSlotID::instance].unitTypeToChangeInto
                                        = OpenSHC::Map::Units::UT_PEASANT;
                                    this->units[DAT_CurrentUnitSlotID::instance].state_2 = 0;
                                    this->units[DAT_CurrentUnitSlotID::instance].workplaceBuildingID_1 = 0;
                                    MACRO_CALL_MEMBER(
                                        OpenSHC::Map::Units::UnitsState_Func::clearHiddenFlagAndUpdatePosition, this)(
                                        DAT_CurrentUnitSlotID::instance);
                                    uVar9 = DAT_CurrentUnitSlotID::instance;
                                }
                            }
                        }
                        this->units[uVar9].field131_0x2ac = 0;
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::processMeleeInitiation, this)(
                            DAT_CurrentUnitSlotID::instance);
                        this->units[DAT_CurrentUnitSlotID::instance].field143_0x2c4
                            = this->units[DAT_CurrentUnitSlotID::instance].state.generic;
                        if (this->units[DAT_CurrentUnitSlotID::instance].logicalState
                            != OpenSHC::Map::Units::ULS_TRANSITIONING) {
                            /*
                              Update unit state
                             */

                            (*DAT_UnitPropertiesDefinedData::instance.UpdateUnitFunctions
                                    [(short)this->units[DAT_CurrentUnitSlotID::instance].unitType])();
                        }
                        uVar9 = DAT_CurrentUnitSlotID::instance;
                        UnitStateShort UVar8 = this->units[DAT_CurrentUnitSlotID::instance].field143_0x2c4;
                        if (((UVar8 != this->units[DAT_CurrentUnitSlotID::instance].state.generic)
                                && ((UVar8
                                        == (OpenSHC::Map::Units::States::US_DEATH_02
                                            | OpenSHC::Map::Units::States::US_STAND_UPUnk
                                            | OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk)
                                    || (UVar8 == OpenSHC::Map::Units::States::US_DIG))))
                            && (_troopValue = this->units[DAT_CurrentUnitSlotID::instance].digTileTarget,
                                DAT_TileMapState::instance.moats[_troopValue].owner != '\0')) {
                            char* pcVar3 = &DAT_TileMapState::instance.moats[_troopValue].someCountDown;
                            *pcVar3 = *pcVar3 + -0x14;
                        }
                        this->units[uVar9].field41_0x5c = 0;
                        if (this->units[DAT_CurrentUnitSlotID::instance].usingTeleport == 0) {
                            piVar1 = &this->units[DAT_CurrentUnitSlotID::instance].field200_0x354;
                            /*
                              Not climbing
                             */

                            *piVar1 = *piVar1 + 1;
                            _troopValue = this->units[DAT_CurrentUnitSlotID::instance].field200_0x354;
                            if ((int)this->units[DAT_CurrentUnitSlotID::instance].calculatedMovementSpeed
                                    + (int)this->units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed
                                    + (int)this->units[DAT_CurrentUnitSlotID::instance].moveDelay
                                < _troopValue - this->units[DAT_CurrentUnitSlotID::instance].field199_0x350) {
                                this->units[DAT_CurrentUnitSlotID::instance].field199_0x350 = _troopValue;
                                psVar4 = &this->units[DAT_CurrentUnitSlotID::instance].movementRunUpTime;
                                if (this->units[DAT_CurrentUnitSlotID::instance].movementRunUpTime <= 0) {
                                    *psVar4 = 0;
                                } else {
                                    *psVar4 = *psVar4 + -1;
                                }
                                _troopValue = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::processUnitMove,
                                    this)(DAT_CurrentUnitSlotID::instance,
                                    (int)(this->units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed));
                                if (_troopValue != 0) {
                                    if (((this->units[DAT_CurrentUnitSlotID::instance].state.generic
                                             == OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION)
                                            && (this->units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown
                                                != 0))
                                        && (this->units[DAT_CurrentUnitSlotID::instance].fadeType == 0)) {
                                        this->units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown = 0;
                                    }
                                    psVar4 = &this->units[DAT_CurrentUnitSlotID::instance].field218_0x37e;
                                    *psVar4 = *psVar4 + 1;
                                    if (0xf < this->units[DAT_CurrentUnitSlotID::instance].field218_0x37e) {
                                        this->units[DAT_CurrentUnitSlotID::instance].field218_0x37e = 0;
                                    }
                                    psVar4 = &this->units[DAT_CurrentUnitSlotID::instance].field217_0x37c;
                                    *psVar4 = *psVar4 + 2;
                                    if (0xd < this->units[DAT_CurrentUnitSlotID::instance].field217_0x37c) {
                                        this->units[DAT_CurrentUnitSlotID::instance].field217_0x37c = 0;
                                    }
                                    psVar4 = &this->units[DAT_CurrentUnitSlotID::instance].field215_0x378;
                                    *psVar4 = *psVar4 + 2;
                                    if (0xf < this->units[DAT_CurrentUnitSlotID::instance].field215_0x378) {
                                        this->units[DAT_CurrentUnitSlotID::instance].field215_0x378 = 0;
                                    }
                                    psVar4 = &this->units[DAT_CurrentUnitSlotID::instance].field254_0x3c6;
                                    *psVar4 = *psVar4 + 1;
                                    if (0x11 < this->units[DAT_CurrentUnitSlotID::instance].field254_0x3c6) {
                                        this->units[DAT_CurrentUnitSlotID::instance].field254_0x3c6 = 0;
                                    }
                                    psVar4 = &this->units[DAT_CurrentUnitSlotID::instance].field312_0x428;
                                    *psVar4 = *psVar4 + 1;
                                    if (0x17 < this->units[DAT_CurrentUnitSlotID::instance].field312_0x428) {
                                        this->units[DAT_CurrentUnitSlotID::instance].field312_0x428 = 0;
                                    }
                                }
                                psVar4 = &this->units[DAT_CurrentUnitSlotID::instance].field216_0x37a;
                                *psVar4 = *psVar4 + 1;
                                if (0xb < this->units[DAT_CurrentUnitSlotID::instance].field216_0x37a) {
                                    this->units[DAT_CurrentUnitSlotID::instance].field216_0x37a = 0;
                                }
                                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::calculateUnitMovementSpeed,
                                    this)(DAT_CurrentUnitSlotID::instance);
                            }
                        } else {
                            /*
                              Climbing
                             */

                            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::unitClimbing, this)(
                                DAT_CurrentUnitSlotID::instance);
                        }
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::recomputeUnitStandingHeight, this)(
                            DAT_CurrentUnitSlotID::instance);
                        switch (this->units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated) {
                        case 8:
                            this->units[DAT_CurrentUnitSlotID::instance].gfxNumber
                                = (int)this->units[DAT_CurrentUnitSlotID::instance]
                                      .facingDirectionMapOrientationCorrected
                                + this->units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset;
                            piVar1 = &this->units[DAT_CurrentUnitSlotID::instance].gfxNumber;
                            *piVar1 = *piVar1 + this->units[DAT_CurrentUnitSlotID::instance].field215_0x378 * 8;
                            if (((this->units[DAT_CurrentUnitSlotID::instance].unitType
                                     == OpenSHC::Map::Units::UT_A_HARCHER)
                                    && (_buildingID
                                        = this->units[DAT_CurrentUnitSlotID::instance].horseArcherShootingVariation,
                                        _buildingID != 4))
                                && ((_buildingID != 5 && (_buildingID != 6)))) {
                                this->units[DAT_CurrentUnitSlotID::instance].imageIDUnk
                                    = this->units[DAT_CurrentUnitSlotID::instance].gfxNumber;
                            }
                            break;
                        case 9:
                            this->units[DAT_CurrentUnitSlotID::instance].gfxNumber
                                = (int)this->units[DAT_CurrentUnitSlotID::instance]
                                      .facingDirectionMapOrientationCorrected
                                + this->units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset;
                            piVar1 = &this->units[DAT_CurrentUnitSlotID::instance].gfxNumber;
                            *piVar1 = *piVar1 + (this->units[DAT_CurrentUnitSlotID::instance].field215_0x378 * 8) / 2;
                            break;
                        case 0xc:
                            this->units[DAT_CurrentUnitSlotID::instance].gfxNumber
                                = (int)this->units[DAT_CurrentUnitSlotID::instance]
                                      .facingDirectionMapOrientationCorrected
                                + this->units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset;
                            piVar1 = &this->units[DAT_CurrentUnitSlotID::instance].gfxNumber;
                            *piVar1 = *piVar1 + this->units[DAT_CurrentUnitSlotID::instance].field216_0x37a * 8;
                            break;
                        case 0xe:
                            this->units[DAT_CurrentUnitSlotID::instance].gfxNumber
                                = (int)this->units[DAT_CurrentUnitSlotID::instance]
                                      .facingDirectionMapOrientationCorrected
                                + this->units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset;
                            piVar1 = &this->units[DAT_CurrentUnitSlotID::instance].gfxNumber;
                            *piVar1 = *piVar1 + this->units[DAT_CurrentUnitSlotID::instance].field217_0x37c * 8;
                            break;
                        case 0x10:
                            this->units[DAT_CurrentUnitSlotID::instance].gfxNumber
                                = (int)this->units[DAT_CurrentUnitSlotID::instance]
                                      .facingDirectionMapOrientationCorrected
                                + this->units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset;
                            piVar1 = &this->units[DAT_CurrentUnitSlotID::instance].gfxNumber;
                            *piVar1 = *piVar1 + this->units[DAT_CurrentUnitSlotID::instance].field218_0x37e * 8;
                            if (this->units[DAT_CurrentUnitSlotID::instance].unitType
                                == OpenSHC::Map::Units::UT_A_HARCHER) {
                                this->units[DAT_CurrentUnitSlotID::instance].imageIDUnk
                                    = this->units[DAT_CurrentUnitSlotID::instance].gfxNumber;
                            }
                            if (this->units[DAT_CurrentUnitSlotID::instance].unitType
                                == OpenSHC::Map::Units::UT_E_KNIGHT) {
                                this->units[DAT_CurrentUnitSlotID::instance].imageIDUnk
                                    = this->units[DAT_CurrentUnitSlotID::instance].gfxNumber;
                                if ((DAT_CurrentUnitSlotID::instance & 1) == 0) {
                                    if (((this->units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed != 0)
                                            && ((this->units[DAT_CurrentUnitSlotID::instance]
                                                        .movementType_OR_targetUnitID
                                                    != 0
                                                || (this->units[DAT_CurrentUnitSlotID::instance].targetingType
                                                    == OpenSHC::Map::Units::UIT_UNIT_ATTACK_UNIT))))
                                        && (this->units[DAT_CurrentUnitSlotID::instance].totalSizeOfPathPlan + -0x10
                                            <= (int)this->units[DAT_CurrentUnitSlotID::instance]
                                                .currentIndexInPathPlan)) {
                                        piVar1 = &this->units[DAT_CurrentUnitSlotID::instance].imageIDUnk;
                                        *piVar1 = *piVar1 + 0x80;
                                    }
                                } else {
                                    piVar1 = &this->units[DAT_CurrentUnitSlotID::instance].imageIDUnk;
                                    *piVar1 = *piVar1 + 0x270;
                                }
                            }
                            break;
                        case 0x11:
                            this->units[DAT_CurrentUnitSlotID::instance].gfxNumber
                                = this->units[DAT_CurrentUnitSlotID::instance].facingDirectionMapOrientationCorrected
                                    * 0x10
                                + this->units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset;
                            piVar1 = &this->units[DAT_CurrentUnitSlotID::instance].gfxNumber;
                            *piVar1 = *piVar1 + (int)this->units[DAT_CurrentUnitSlotID::instance].field218_0x37e;
                            break;
                        case 0x12:
                            this->units[DAT_CurrentUnitSlotID::instance].gfxNumber
                                = (int)this->units[DAT_CurrentUnitSlotID::instance]
                                      .facingDirectionMapOrientationCorrected
                                + this->units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset;
                            piVar1 = &this->units[DAT_CurrentUnitSlotID::instance].gfxNumber;
                            *piVar1 = *piVar1 + this->units[DAT_CurrentUnitSlotID::instance].field254_0x3c6 * 8;
                            break;
                        case 0x13:
                        case 0x14:
                            this->units[DAT_CurrentUnitSlotID::instance].imageIDUnk
                                = (int)this->units[DAT_CurrentUnitSlotID::instance]
                                      .facingDirectionMapOrientationCorrected
                                + this->units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset;
                            piVar1 = &this->units[DAT_CurrentUnitSlotID::instance].imageIDUnk;
                            *piVar1
                                = *piVar1 + ((int)this->units[DAT_CurrentUnitSlotID::instance].field215_0x378 / 2) * 8;
                            break;
                        case 0x15:
                            this->units[DAT_CurrentUnitSlotID::instance].gfxNumber
                                = (int)this->units[DAT_CurrentUnitSlotID::instance]
                                      .facingDirectionMapOrientationCorrected
                                + this->units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset;
                            piVar1 = &this->units[DAT_CurrentUnitSlotID::instance].gfxNumber;
                            *piVar1 = *piVar1 + this->units[DAT_CurrentUnitSlotID::instance].field218_0x37e * 8;
                            _troopValue
                                = this->units[DAT_CurrentUnitSlotID::instance].facingDirectionMapOrientationCorrected
                                + 0x80 + this->units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset;
                            this->units[DAT_CurrentUnitSlotID::instance].imageIDUnk = _troopValue;
                            piVar1 = &this->units[DAT_CurrentUnitSlotID::instance].imageIDUnk;
                            *piVar1 = *piVar1 + this->units[DAT_CurrentUnitSlotID::instance].field218_0x37e * 8;
                            break;
                        case 0x16:
                            uVar9 = (int)this->units[DAT_CurrentUnitSlotID::instance]
                                        .facingDirectionMapOrientationCorrected
                                    + 4U
                                & 0x80000007;
                            if ((int)uVar9 < 0) {
                                uVar9 = (uVar9 - 1 | 0xfffffff8) + 1;
                            }
                            this->units[DAT_CurrentUnitSlotID::instance].gfxNumber = uVar9 + 0x151;
                            piVar1 = &this->units[DAT_CurrentUnitSlotID::instance].gfxNumber;
                            *piVar1
                                = *piVar1 + ((byte)this->units[DAT_CurrentUnitSlotID::instance].field218_0x37e & 3) * 8;
                            uVar9 = (int)this->units[DAT_CurrentUnitSlotID::instance]
                                        .facingDirectionMapOrientationCorrected
                                    + 4U
                                & 0x80000007;
                            if ((int)uVar9 < 0) {
                                uVar9 = (uVar9 - 1 | 0xfffffff8) + 1;
                            }
                            _troopValue = uVar9 + 0x1d1;
                            this->units[DAT_CurrentUnitSlotID::instance].imageIDUnk = _troopValue;
                            piVar1 = &this->units[DAT_CurrentUnitSlotID::instance].imageIDUnk;
                            *piVar1 = *piVar1 + this->units[DAT_CurrentUnitSlotID::instance].field218_0x37e * 8;
                            break;
                        case 0x18:
                            this->units[DAT_CurrentUnitSlotID::instance].gfxNumber
                                = (int)this->units[DAT_CurrentUnitSlotID::instance]
                                      .facingDirectionMapOrientationCorrected
                                + this->units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset;
                            piVar1 = &this->units[DAT_CurrentUnitSlotID::instance].gfxNumber;
                            *piVar1 = *piVar1 + this->units[DAT_CurrentUnitSlotID::instance].field312_0x428 * 8;
                            break;
                        case 99:
                            this->units[DAT_CurrentUnitSlotID::instance].imageID2
                                = (int)this->units[DAT_CurrentUnitSlotID::instance]
                                      .facingDirectionMapOrientationCorrected
                                + this->units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset;
                            piVar1 = &this->units[DAT_CurrentUnitSlotID::instance].imageID2;
                            *piVar1
                                = *piVar1 + ((int)this->units[DAT_CurrentUnitSlotID::instance].field215_0x378 / 2) * 8;
                        }
                        psVar4 = &this->units[DAT_CurrentUnitSlotID::instance].unitSpeedMatchingRelatedUnk;
                        if (this->units[DAT_CurrentUnitSlotID::instance].unitSpeedMatchingRelatedUnk != 0) {
                            *psVar4 = *psVar4 + -1;
                        }
                        bVar13 = this->units[DAT_CurrentUnitSlotID::instance].fadeType;
                        if (bVar13 != 0) {
                            if (bVar13 == 1) {
                                this->units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown
                                    = (byte)DAT_UnitPropertiesDefinedData::instance.FadeAlpha_Values_1_2
                                          [(char)this->units[DAT_CurrentUnitSlotID::instance].fadeCounter];
                            } else {
                                if (bVar13 == 2) {
                                    bVar13 = (byte)DAT_UnitPropertiesDefinedData::instance.FadeAlpha_Values_1_2
                                                 [(char)this->units[DAT_CurrentUnitSlotID::instance].fadeCounter];
                                } else {
                                    byte bVar5 = this->units[DAT_CurrentUnitSlotID::instance].fadeCounter;
                                    if (bVar13 == 3) {
                                        bVar13 = (byte)DAT_UnitPropertiesDefinedData::instance
                                                     .FadeAlpha_Values_3[(char)bVar5];
                                    } else {
                                        bVar13 = (byte)DAT_UnitPropertiesDefinedData::instance
                                                     .FadeAlpha_Values_4[(char)bVar5];
                                    }
                                }
                                this->units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown = bVar13;
                            }
                            byte* pbVar11 = &this->units[DAT_CurrentUnitSlotID::instance].fadeCounter;
                            *pbVar11 = *pbVar11 + 1;
                            if ((char)this->units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown
                                < '\x01') {
                                this->units[DAT_CurrentUnitSlotID::instance].fadeType = 0;
                                this->units[DAT_CurrentUnitSlotID::instance].fadeCounter = 0;
                            }
                        }
                    }
                    DAT_CurrentUnitSlotID::instance = DAT_CurrentUnitSlotID::instance + 1;
                } while ((int)DAT_CurrentUnitSlotID::instance < (int)this->maxUnitCount);
            }
            if (DAT_TileMapState::instance.refreshRelatedOne == 0) {
                DAT_UpdateUnitsTracker::instance = 0;
                return;
            }
            DAT_UpdateUnitsTracker::instance = DAT_UpdateUnitsTracker::instance + 1;
            return;
        }

    }
}
}
