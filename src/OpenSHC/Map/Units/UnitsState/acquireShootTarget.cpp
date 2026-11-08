#include "../UnitsState.func.hpp"

#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_EntityDefinedData.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitInstructionType;
        using OpenSHC::Map::Units::UnitLogicState;
        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::Map::Units::States::UnitState;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0054B0D0
        BOOLEnum UnitsState::acquireShootTarget(int unitID)

        {
            int _entityType;
            int _unitPlayerID = this->units[unitID].owner;
            int _microXUnit = this->units[unitID].microXPosition;
            int _microYUnit = this->units[unitID].microYPosition;
            int _unitTotalHeight = this->units[unitID].buildingHeight + this->units[unitID].terrainOrClimbHeight;
            int _validTargetID = 0;
            int _bestScore = 100000;
            int _shotDistance = 0;
            int _bestUntargetedScore = 100000;
            int _untargetedTargetID = 0;
            int _untargetedShotDistance = 0;
            switch (this->units[unitID].unitType) {
            case OpenSHC::Map::Units::UT_E_XBOW:
                _entityType = 7;
                break;
            case OpenSHC::Map::Units::UT_A_SLINGER:
                _entityType = 33;
                break;
            case OpenSHC::Map::Units::UT_A_FIRETHROWER:
                _entityType = 34;
                break;
            case OpenSHC::Map::Units::UT_S_CATAPULT:
                _entityType = 2;
                if ((this->units[unitID].stoneAmmunition <= 0)
                    && (this->units[unitID].targetingType != OpenSHC::Map::Units::UIT_THROW_COW)) {
                    this->units[unitID].targetingType = OpenSHC::Map::Units::UIT_NO_INSTRUCTION_OR_MOVEUnk;
                    return FALSE;
                }
                break;
            case OpenSHC::Map::Units::UT_S_TREBUCHET:
                _entityType = 3;
                if ((this->units[unitID].stoneAmmunition <= 0)
                    && (this->units[unitID].targetingType != OpenSHC::Map::Units::UIT_THROW_COW)) {
                    this->units[unitID].targetingType = OpenSHC::Map::Units::UIT_NO_INSTRUCTION_OR_MOVEUnk;
                    return FALSE;
                }
                break;
            case OpenSHC::Map::Units::UT_S_MANGONEL:
                _entityType = 4;
                break;
            case OpenSHC::Map::Units::UT_S_BALLISTA:
                _entityType = 20;
                break;
            case OpenSHC::Map::Units::UT_S_FBALLISTA:
                _entityType = 37;
                break;
            default:
                _entityType = 1;
            }
            int _rangeSquared = DAT_EntityDefinedData::instance.EntityTypeArrayForProjectileRange[_entityType]
                * DAT_EntityDefinedData::instance.EntityTypeArrayForProjectileRange[_entityType];
            /*
              fetch attacking explicitness
             */

            if (this->units[unitID].targetingType == OpenSHC::Map::Units::UIT_UNIT_ATTACK_UNIT) {
                /*
                  if explicitness = 4 (user selected attack)...
                   fetch the targetedUnitID
                 */

                int const _targetID = this->units[unitID].targetedUnitID__OR__engineerMannedSiegeEngineRef;
                if (this->units[_targetID].uid
                        == this->units[unitID]
                            .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID
                    && this->units[_targetID].dying == 0
                    && this->units[_targetID].logicalState == OpenSHC::Map::Units::ULS_NORMAL
                    && MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::checkIfCitizenUnitIsAliveBasedOnState,
                           DAT_UnitsState::ptr)(_targetID)
                        == FALSE
                    && DAT_UnitsState::instance.units[_targetID].state.generic != (UnitState)117
                    && DAT_GameState::instance.mapAndTime.playerTeams[this->units[_targetID].owner]
                        != DAT_GameState::instance.mapAndTime.playerTeams[_unitPlayerID]) {
                    int const _yDifference = _microYUnit / 8 - this->units[_targetID].microYPosition / 8;
                    int const _xDifference = _microXUnit / 8 - this->units[_targetID].microXPosition / 8;
                    if (_xDifference * _xDifference + _yDifference * _yDifference > _rangeSquared) {
                        if (DAT_GameSynchronyState::instance
                                .currentPlayerFullIDArray[DAT_UnitsState::instance.units[unitID].owner]
                            != -1) {
                            return FALSE;
                        }
                    } else {
                        int const _shootDistanceScore = MACRO_CALL_MEMBER(
                            OpenSHC::Map::Entities::EntityState_Func::arrowShootingRelated, DAT_EntityState::ptr)(
                            _microXUnit, _microYUnit, _unitTotalHeight + 30, this->units[_targetID].microXPosition,
                            this->units[_targetID].microYPosition,
                            this->units[_targetID].buildingHeight + this->units[_targetID].terrainOrClimbHeight + 26);
                        if (_shootDistanceScore > 0
                            && this->units[unitID].unitType != OpenSHC::Map::Units::UT_S_MANGONEL
                            && this->units[unitID].unitType != OpenSHC::Map::Units::UT_S_BALLISTA) {
                            this->units[unitID].shootTargetedUnit = _targetID;
                            this->units[unitID].targetUID = this->units[_targetID].uid;
                            this->units[unitID].distanceToEnemyUnitLadders = _shootDistanceScore;
                            this->units[unitID].shootTargetMicroX = this->units[_targetID].microXPosition;
                            this->units[unitID].shootTargetMicroY = this->units[_targetID].microYPosition;
                            this->units[unitID].shootTargetZ = this->units[_targetID].terrainOrClimbHeight;
                            if (_shootDistanceScore > 100) {
                                this->units[unitID].jugglerCount = 0;
                                this->units[_targetID].field_0x39a = 1;
                                return TRUE;
                            }
                            int const _targetTotalHeight
                                = this->units[_targetID].terrainOrClimbHeight + this->units[_targetID].buildingHeight;
                            int const _shooterTotalHeight
                                = this->units[unitID].buildingHeight + this->units[unitID].terrainOrClimbHeight;
                            if (_shooterTotalHeight > _targetTotalHeight + 70) {
                                this->units[unitID].jugglerCount = 1;
                                this->units[_targetID].field_0x39a = 1;
                                return TRUE;
                            }
                            /* -1 when shooting up at the target, 0 when level with it */
                            this->units[unitID].jugglerCount = (_shooterTotalHeight >= _targetTotalHeight - 70) - 1;
                            this->units[_targetID].field_0x39a = 1;
                            return TRUE;
                        }
                        if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_HUNTER) {
                            return FALSE;
                        }
                        /* no clear shot: aim at where the target stands */
                        this->units[unitID].shootTargetedUnit = -2;
                        this->units[unitID].shootTargetMicroX = this->units[_targetID].microXPosition;
                        this->units[unitID].shootTargetMicroY = this->units[_targetID].microYPosition;
                        this->units[unitID].shootTargetZ = this->units[_targetID].terrainOrClimbHeight;
                        return TRUE;
                    }
                }
                int const _savedDestinationX = this->units[unitID]._someX_2;
                this->units[unitID].targetedUnitID__OR__engineerMannedSiegeEngineRef = 0;
                this->units[unitID].shootTargetedUnit = 0;
                this->units[unitID].targetingType = OpenSHC::Map::Units::UIT_NO_INSTRUCTION_OR_MOVEUnk;
                if (_savedDestinationX != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, this)(
                        unitID, _savedDestinationX, this->units[unitID]._someY_2, 0);
                    this->units[unitID]._someX_2 = 0;
                    this->units[unitID]._someY_2 = 0;
                    this->units[unitID].moveDelay = 0;
                    this->units[unitID].targetedBuildingTile = 0;
                    this->units[unitID].state.generic = OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION;
                    return TRUE;
                }
            }
            if (this->units[unitID].targetingType == OpenSHC::Map::Units::UIT_LIGHT_PITCH) {
                /*
                  get the workplace building id
                 */

                int _ditchID = this->units[unitID].targetID_OR_targetBuildingID;
                int _brazierEntityID;
                if (DAT_TileMapState::instance.pitchDitches[_ditchID].uid
                        == this->units[unitID]
                            .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID
                    && (_brazierEntityID = MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::isBrazierNearby,
                            DAT_EntityState::ptr)(this->units[unitID].x, this->units[unitID].y,
                            (int)(DAT_UnitsState::instance.units[unitID].buildingHeight
                                + this->units[unitID].terrainOrClimbHeight)),
                        _brazierEntityID != 0)) {
                    this->units[unitID].shootTargetMicroX = DAT_TileMapState::instance.pitchDitches[_ditchID].x * 8 + 4;
                    this->units[unitID].shootTargetMicroY = DAT_TileMapState::instance.pitchDitches[_ditchID].y * 8 + 4;
                    this->units[unitID].shootTargetZ
                        = (ushort)DAT_TileMapState::instance
                              .HeightLayer[DAT_TileMapState::instance.pitchDitches[_ditchID].tile];
                    this->units[unitID].shootTargetedUnit = -1;
                    return TRUE;
                }
            } else if (this->units[unitID].targetingType == OpenSHC::Map::Units::UIT_ATTACK_BUILDING) {
                int _buildingID = this->units[unitID].targetID_OR_targetBuildingID;
                if (DAT_BuildingsState::instance.buildings[_buildingID].uid
                    == this->units[unitID]
                        .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID) {
                    this->units[unitID].shootTargetMicroX = DAT_BuildingsState::instance.buildings[_buildingID].x * 8
                        + (short)((int)(DAT_BuildingsState::instance.buildings[_buildingID].widthOrHeight * 8) / 2);
                    this->units[unitID].shootTargetMicroY = DAT_BuildingsState::instance.buildings[_buildingID].y * 8
                        + (short)((int)(DAT_BuildingsState::instance.buildings[_buildingID].widthOrHeight * 8) / 2);
                    this->units[unitID].shootTargetZ
                        = DAT_BuildingsState::instance.buildings[_buildingID].terrainHeightUnk;
                    this->units[unitID].shootTargetedUnit = -1;
                    return TRUE;
                }
            } else if (this->units[unitID].targetingType == OpenSHC::Map::Units::UIT_ATTACK_WALL) {
                int _wallY = this->units[unitID].attackAtTileY;
                int _wallX = this->units[unitID].attackAtTileX;
                int _wallTile = DAT_ViewportRenderState::instance.translationMatrix[_wallY].addXgetTile + _wallX;
                BOOLEnum _tileIsValid = MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                    DAT_ViewportRenderState::ptr)(_wallX, (uint)(_wallY));
                if (_tileIsValid != FALSE && (DAT_TileMapState::instance.LogicLayer[_wallTile] & 0x100U) != 0) {
                    this->units[unitID].shootTargetMicroX = this->units[unitID].attackAtTileX * 8;
                    this->units[unitID].shootTargetMicroY = this->units[unitID].attackAtTileY * 8;
                    this->units[unitID].shootTargetZ
                        = (short)((int)((uint)DAT_TileMapState::instance.HeightLayer[_wallTile]
                                      - (uint)DAT_TileMapState::instance.DefaultHeightLayer[_wallTile])
                              / 2)
                        + (ushort)DAT_TileMapState::instance.DefaultHeightLayer[_wallTile];
                    this->units[unitID].shootTargetedUnit = -1;
                    return TRUE;
                }
            } else {
                if ((this->units[unitID].targetingType != OpenSHC::Map::Units::UIT_ATTACK_LAND)
                    && (this->units[unitID].targetingType != OpenSHC::Map::Units::UIT_THROW_COW)) {
                    if (_entityType == 2) {
                        return FALSE;
                    }
                    if (_entityType == 3) {
                        return FALSE;
                    }
                    for (int _enemyIndex = 0;
                        _enemyIndex < DAT_GameState::instance.playerDataArray[_unitPlayerID].enemies;
                        _enemyIndex = _enemyIndex + 1) {
                        int const _enemy
                            = DAT_GameState::instance.playerDataArray[_unitPlayerID].enemyIDArray[_enemyIndex];
                        if (this->units[_enemy].dying != 0) {
                            continue;
                        }
                        if (this->units[_enemy].uid
                            != DAT_GameState::instance.mapAndTime
                                .playerEnemenyUnitUIDShortList[_unitPlayerID][_enemyIndex]) {
                            continue;
                        }
                        switch (this->units[_enemy].unitType) {
                        case OpenSHC::Map::Units::UT_ANTELOPESHDEER:
                            /* only hunters shoot deer */
                            if (this->units[unitID].unitType != OpenSHC::Map::Units::UT_HUNTER) {
                                continue;
                            }
                            break;
                        case OpenSHC::Map::Units::UT_RABBIT: {
                            if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_HUNTER) {
                                continue;
                            }
                            int const _tribeID = this->units[unitID].tribeID;
                            if (_tribeID <= 0) {
                                continue;
                            }
                            if (DAT_TribesState::instance.tribes[_tribeID].containsRabbit == 0) {
                                continue;
                            }
                            break;
                        }
                        case OpenSHC::Map::Units::UT_LIONSHWOLF: {
                            int const _enemyTribeID = this->units[_enemy].tribeID;
                            if (DAT_TribesState::instance.tribes[_enemyTribeID].unknownBool02 != 0) {
                                continue;
                            }
                            if (DAT_TribesState::instance.tribes[_enemyTribeID].unknownBool01 == 0) {
                                if (this->units[_enemy].state.generic != 207) {
                                    continue;
                                }
                                if (this->units[this->units[_enemy].targetedUnitID__OR__engineerMannedSiegeEngineRef]
                                        .isStalked
                                    != 0) {
                                    continue;
                                }
                            }
                            break;
                        }
                        case OpenSHC::Map::Units::UT_CAGEDOG:
                            if (DAT_GameState::instance.mapAndTime.playerTeams[this->units[_enemy].displayColorPlayerID]
                                == DAT_GameState::instance.mapAndTime.playerTeams[this->units[unitID].owner]) {
                                continue;
                            }
                            break;
                        case OpenSHC::Map::Units::UT_A_ASSASSIN:
                            if (DAT_UnitsState::instance.units[_enemy].assassinsMicroDistanceToEnemyUnk > 160) {
                                continue;
                            }
                            break;
                        }
                        int const _yTileDifference = _microYUnit / 8 - this->units[_enemy].microYPosition / 8;
                        int const _xTileDifference = _microXUnit / 8 - this->units[_enemy].microXPosition / 8;
                        if (_xTileDifference * _xTileDifference + _yTileDifference * _yTileDifference > _rangeSquared) {
                            continue;
                        }
                        int const _enemyMicroX = this->units[_enemy].microXPosition;
                        int _score;
                        if (_microXUnit > _enemyMicroX) {
                            _score = _microXUnit - _enemyMicroX;
                        } else {
                            _score = _enemyMicroX - _microXUnit;
                        }
                        int const _enemyMicroY = this->units[_enemy].microYPosition;
                        int _yDistance;
                        if (_microYUnit > _enemyMicroY) {
                            _yDistance = _microYUnit - _enemyMicroY;
                        } else {
                            _yDistance = _enemyMicroY - _microYUnit;
                        }
                        if (_score < _yDistance) {
                            _score = _yDistance;
                        }
                        /* targets that others already aim at score worse */
                        _score = _score + this->units[_enemy].field_0x3dc * 50;
                        if (_entityType == 4) {
                            /* mangonels prefer siege engines, other targets only for a human player */
                            switch (this->units[_enemy].unitType) {
                            case OpenSHC::Map::Units::UT_E_ENGINEER:
                            case OpenSHC::Map::Units::UT_S_CATAPULT:
                            case OpenSHC::Map::Units::UT_S_TREBUCHET:
                            case OpenSHC::Map::Units::UT_S_MANGONEL:
                            case OpenSHC::Map::Units::UT_S_TOWER:
                            case OpenSHC::Map::Units::UT_S_BATTERINGRAM:
                            case OpenSHC::Map::Units::UT_S_SHIELD:
                            case OpenSHC::Map::Units::UT_S_BALLISTA:
                            case OpenSHC::Map::Units::UT_S_FBALLISTA:
                                break;
                            default:
                                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[this->units[unitID].owner]
                                    != -1) {
                                    continue;
                                }
                                if (this->units[_enemy].isSelectable_OR_matchTime != 0) {
                                    _score = _score * 3 + 100;
                                } else {
                                    _score = (_score * 5 + 50) * 2;
                                }
                            }
                            if (_score == -1) {
                                continue;
                            }
                        } else if (_entityType == 20) {
                            switch (this->units[_enemy].unitType) {
                            case OpenSHC::Map::Units::UT_E_ENGINEER:
                            case OpenSHC::Map::Units::UT_S_CATAPULT:
                            case OpenSHC::Map::Units::UT_S_TREBUCHET:
                            case OpenSHC::Map::Units::UT_S_MANGONEL:
                            case OpenSHC::Map::Units::UT_LORD:
                            case OpenSHC::Map::Units::UT_S_TOWER:
                            case OpenSHC::Map::Units::UT_S_BATTERINGRAM:
                            case OpenSHC::Map::Units::UT_S_SHIELD:
                            case OpenSHC::Map::Units::UT_S_BALLISTA:
                            case OpenSHC::Map::Units::UT_A_FIRETHROWER:
                            case OpenSHC::Map::Units::UT_S_FBALLISTA:
                                _score = _score * 2 + 100;
                                break;
                            case OpenSHC::Map::Units::UT_E_ARCHER:
                            case OpenSHC::Map::Units::UT_E_XBOW:
                            case OpenSHC::Map::Units::UT_E_SPEAR:
                            case OpenSHC::Map::Units::UT_E_MACE:
                            case OpenSHC::Map::Units::UT_E_LADDER:
                            case OpenSHC::Map::Units::UT_A_ARCHER:
                            case OpenSHC::Map::Units::UT_A_SLAVE:
                            case OpenSHC::Map::Units::UT_A_SLINGER:
                            case OpenSHC::Map::Units::UT_A_ASSASSIN:
                            case OpenSHC::Map::Units::UT_A_HARCHER:
                                _score = _score * 5 + 200;
                                break;
                            case OpenSHC::Map::Units::UT_E_PIKE:
                            case OpenSHC::Map::Units::UT_E_SWORD:
                            case OpenSHC::Map::Units::UT_E_KNIGHT:
                            case OpenSHC::Map::Units::UT_A_SWORDSMAN:
                                break;
                            default:
                                _score = (_score * 5 + 200) * 2;
                            }
                        } else if (_entityType == 37) {
                            switch (this->units[_enemy].unitType) {
                            case OpenSHC::Map::Units::UT_E_ENGINEER:
                            case OpenSHC::Map::Units::UT_S_CATAPULT:
                            case OpenSHC::Map::Units::UT_S_TREBUCHET:
                            case OpenSHC::Map::Units::UT_S_MANGONEL:
                            case OpenSHC::Map::Units::UT_S_TOWER:
                            case OpenSHC::Map::Units::UT_S_BATTERINGRAM:
                            case OpenSHC::Map::Units::UT_S_SHIELD:
                            case OpenSHC::Map::Units::UT_S_BALLISTA:
                            case OpenSHC::Map::Units::UT_A_FIRETHROWER:
                            case OpenSHC::Map::Units::UT_S_FBALLISTA:
                                _score = _score * 2 + 100;
                                break;
                            case OpenSHC::Map::Units::UT_LORD:
                                /* a human player's fire ballista leaves the lord alone */
                                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[_unitPlayerID] == -1) {
                                    continue;
                                }
                                _score = _score * 5 + 200;
                                break;
                            case OpenSHC::Map::Units::UT_E_ARCHER:
                            case OpenSHC::Map::Units::UT_E_XBOW:
                            case OpenSHC::Map::Units::UT_E_SPEAR:
                            case OpenSHC::Map::Units::UT_E_MACE:
                            case OpenSHC::Map::Units::UT_E_LADDER:
                            case OpenSHC::Map::Units::UT_A_ARCHER:
                            case OpenSHC::Map::Units::UT_A_SLAVE:
                            case OpenSHC::Map::Units::UT_A_SLINGER:
                            case OpenSHC::Map::Units::UT_A_ASSASSIN:
                            case OpenSHC::Map::Units::UT_A_HARCHER:
                                _score = _score * 5 + 200;
                                break;
                            case OpenSHC::Map::Units::UT_E_PIKE:
                            case OpenSHC::Map::Units::UT_E_SWORD:
                            case OpenSHC::Map::Units::UT_E_KNIGHT:
                            case OpenSHC::Map::Units::UT_A_SWORDSMAN:
                                break;
                            default:
                                continue;
                            }
                            if (_score == -1) {
                                continue;
                            }
                        } else {
                            if (this->units[_enemy].field_0x3ff != 0
                                && DAT_GameSynchronyState::instance.currentPlayerFullIDArray[this->units[_enemy].owner]
                                    == -1) {
                                _score = _score / 3;
                            }
                            switch (this->units[_enemy].unitType) {
                            case OpenSHC::Map::Units::UT_E_ENGINEER:
                            case OpenSHC::Map::Units::UT_S_CATAPULT:
                            case OpenSHC::Map::Units::UT_S_TREBUCHET:
                            case OpenSHC::Map::Units::UT_LORD:
                                _score = _score * 2 + 100;
                                break;
                            case OpenSHC::Map::Units::UT_E_ARCHER:
                            case OpenSHC::Map::Units::UT_E_XBOW:
                            case OpenSHC::Map::Units::UT_A_ARCHER:
                            case OpenSHC::Map::Units::UT_A_HARCHER:
                                _score = _score + 75;
                                break;
                            case OpenSHC::Map::Units::UT_E_SPEAR:
                            case OpenSHC::Map::Units::UT_E_PIKE:
                            case OpenSHC::Map::Units::UT_E_MACE:
                            case OpenSHC::Map::Units::UT_E_SWORD:
                            case OpenSHC::Map::Units::UT_E_KNIGHT:
                            case OpenSHC::Map::Units::UT_A_SLAVE:
                            case OpenSHC::Map::Units::UT_A_SLINGER:
                            case OpenSHC::Map::Units::UT_A_ASSASSIN:
                            case OpenSHC::Map::Units::UT_A_SWORDSMAN:
                                _score = _score * 5 + 200;
                                break;
                            case OpenSHC::Map::Units::UT_E_LADDER:
                                _score = _score * 7 + 300;
                                break;
                            case OpenSHC::Map::Units::UT_S_MANGONEL:
                            case OpenSHC::Map::Units::UT_S_BALLISTA:
                            case OpenSHC::Map::Units::UT_A_FIRETHROWER:
                            case OpenSHC::Map::Units::UT_S_FBALLISTA:
                                break;
                            default:
                                _score = (_score * 5 + 200) * 2;
                                break;
                            }
                        }
                        if (_score < _bestScore || _score < _bestUntargetedScore) {
                            int const _shotFlightDistance
                                = MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::arrowShootingRelated,
                                    DAT_EntityState::ptr)(_microXUnit, _microYUnit, _unitTotalHeight + 30,
                                    this->units[_enemy].microXPosition, _enemyMicroY,
                                    this->units[_enemy].terrainOrClimbHeight + this->units[_enemy].buildingHeight + 26);
                            if (_shotFlightDistance > 0) {
                                if (_score < _bestScore) {
                                    _bestScore = _score;
                                    _shotDistance = _shotFlightDistance;
                                    _validTargetID = _enemy;
                                }
                                if (this->units[_enemy].field_0x39a == 0 && _score < _bestUntargetedScore) {
                                    _bestUntargetedScore = _score;
                                    _untargetedShotDistance = _shotFlightDistance;
                                    _untargetedTargetID = _enemy;
                                }
                            }
                        }
                    }
                    if (_validTargetID == 0) {
                        return FALSE;
                    }
                    if (_untargetedTargetID != 0 && _bestUntargetedScore < (_bestScore * 3) / 2) {
                        _validTargetID = _untargetedTargetID;
                        _shotDistance = _untargetedShotDistance;
                    }
                    if (_entityType == 4) {
                        this->units[unitID].shootTargetedUnit = -2;
                        this->units[unitID].shootTargetMicroX = this->units[_validTargetID].microXPosition;
                        this->units[unitID].shootTargetMicroY = this->units[_validTargetID].microYPosition;
                        this->units[unitID].shootTargetZ = this->units[_validTargetID].terrainOrClimbHeight;
                        return TRUE;
                    }
                    if (_entityType == 37 || _entityType == 20) {
                        this->units[unitID].shootTargetedUnit = _validTargetID;
                        this->units[unitID].targetUID = this->units[_validTargetID].uid;
                        this->units[unitID].distanceToEnemyUnitLadders = _shotDistance;
                        this->units[unitID].shootTargetMicroX = this->units[_validTargetID].microXPosition;
                        this->units[unitID].shootTargetMicroY = this->units[_validTargetID].microYPosition;
                        this->units[unitID].shootTargetZ = this->units[_validTargetID].terrainOrClimbHeight;
                        return TRUE;
                    }
                    this->units[_validTargetID].field_0x3dc = this->units[_validTargetID].field_0x3dc + 1;
                    this->units[unitID].shootTargetedUnit = _validTargetID;
                    this->units[unitID].field_0x3de = _validTargetID;
                    this->units[unitID].targetUID = this->units[_validTargetID].uid;
                    this->units[unitID].distanceToEnemyUnitLadders = _shotDistance;
                    if (_shotDistance > 100) {
                        this->units[unitID].jugglerCount = 0;
                        this->units[_validTargetID].field_0x39a = 1;
                        return TRUE;
                    }
                    int const _targetTotalHeight
                        = this->units[_validTargetID].terrainOrClimbHeight + this->units[_validTargetID].buildingHeight;
                    int const _shooterTotalHeight
                        = this->units[unitID].buildingHeight + this->units[unitID].terrainOrClimbHeight;
                    if (_shooterTotalHeight > _targetTotalHeight + 70) {
                        this->units[unitID].jugglerCount = 1;
                        this->units[_validTargetID].field_0x39a = 1;
                        return TRUE;
                    }
                    /* -1 when shooting up at the target, 0 when level with it */
                    this->units[unitID].jugglerCount = (_shooterTotalHeight >= _targetTotalHeight - 70) - 1;
                    this->units[_validTargetID].field_0x39a = 1;
                    return TRUE;
                }
                int _attackTileY = this->units[unitID].attackAtTileY;
                int _attackTileX = this->units[unitID].attackAtTileX;
                this->units[unitID].jugglerCount = -1;
                BOOLEnum _tileIsValid = MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                    DAT_ViewportRenderState::ptr)(_attackTileX, (uint)(_attackTileY));
                if (_tileIsValid != FALSE) {
                    _attackTileX = this->units[unitID].attackAtTileX;
                    this->units[unitID].shootTargetMicroX = _attackTileX * 8;
                    this->units[unitID].shootTargetedUnit = -1;
                    this->units[unitID].shootTargetMicroY = _attackTileY * 8;
                    this->units[unitID].shootTargetZ
                        = (ushort)DAT_TileMapState::instance
                              .HeightLayer[DAT_ViewportRenderState::instance.translationMatrix[_attackTileY].addXgetTile
                                  + _attackTileX];
                    return TRUE;
                }
            }
            this->units[unitID].targetingType = OpenSHC::Map::Units::UIT_NO_INSTRUCTION_OR_MOVEUnk;
            return FALSE;
        }

    }
}
}
