#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
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
            UnitTypeShort UVar4;
            short sVar5;
            int _unitTotalHeight;
            int _rangeSquared;
            BOOLEnum BVar6;
            int iVar7;
            short sVar9;
            int _xDifferenceToTarget;
            int _0x04_yDifference;
            int _yDifferenceToTarget;
            int _entityType;
            int local_30;
            int local_2c;
            int _validTargetID;
            int local_10;
            int local_c;
            int local_8;
            int _unitPlayerID = (int)this->units[unitID].owner;
            int _microXUnit = (int)this->units[unitID].microXPosition;
            int _microYUnit = (int)this->units[unitID].microYPosition;
            _unitTotalHeight = (int)this->units[unitID].buildingHeight + (int)this->units[unitID].terrainOrClimbHeight;
            _validTargetID = 0;
            local_30 = 100000;
            local_8 = 0;
            local_2c = 100000;
            local_10 = 0;
            local_c = 0;
            /*
              switch based on unit type
             */

            switch (this->units[unitID].unitType) {
            case OpenSHC::Map::Units::UT_E_XBOW:
                /*
                  crossbow
                 */

                _entityType = 7;
                break;
            default:
                /*
                  default:
                 */

                _entityType = 1;
                break;
            case OpenSHC::Map::Units::UT_S_CATAPULT:
                /*
                  catapult
                 */

                _entityType = 2;
                if ((this->units[unitID].stoneAmmunition <= 0)
                    && (this->units[unitID].targetingType != OpenSHC::Map::Units::UIT_THROW_COW)) {
                    this->units[unitID].targetingType = OpenSHC::Map::Units::UIT_NO_INSTRUCTION_OR_MOVEUnk;
                    return FALSE;
                }
                break;
            case OpenSHC::Map::Units::UT_S_TREBUCHET:
                /*
                  trebuchet
                 */

                _entityType = 3;
                if ((this->units[unitID].stoneAmmunition <= 0)
                    && (this->units[unitID].targetingType != OpenSHC::Map::Units::UIT_THROW_COW)) {
                    this->units[unitID].targetingType = OpenSHC::Map::Units::UIT_NO_INSTRUCTION_OR_MOVEUnk;
                    return FALSE;
                }
                break;
            case OpenSHC::Map::Units::UT_S_MANGONEL:
                /*
                  mangonel
                 */

                _entityType = 4;
                break;
            case OpenSHC::Map::Units::UT_S_BALLISTA:
                /*
                  ballista
                 */

                _entityType = 0x14;
                break;
            case OpenSHC::Map::Units::UT_A_SLINGER:
                /*
                  slinger
                 */

                _entityType = 0x21;
                break;
            case OpenSHC::Map::Units::UT_A_FIRETHROWER:
                /*
                  fire thrower
                 */

                _entityType = 0x22;
                break;
            case OpenSHC::Map::Units::UT_S_FBALLISTA:
                /*
                  fire ballista
                 */

                _entityType = 0x25;
            }
            _rangeSquared = DAT_EntityDefinedData::instance.EntityTypeArrayForProjectileRange[_entityType]
                * DAT_EntityDefinedData::instance.EntityTypeArrayForProjectileRange[_entityType];
            /*
              fetch attacking explicitness
             */

            if (this->units[unitID].targetingType == OpenSHC::Map::Units::UIT_UNIT_ATTACK_UNIT) {
                /*
                  if explicitness = 4 (user selected attack)...
                   fetch the targetedUnitID
                 */

                sVar9 = this->units[unitID].targetedUnitID__OR__engineerMannedSiegeEngineRef;
                int _0x04_targetUnitID = (int)sVar9;
                if (((((this->units[_0x04_targetUnitID].uid
                           == this->units[unitID]
                               .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID)
                          && (this->units[_0x04_targetUnitID].dying == 0))
                         && (this->units[_0x04_targetUnitID].logicalState == OpenSHC::Map::Units::ULS_NORMAL))
                        && ((BVar6 = MACRO_CALL_MEMBER(
                                 OpenSHC::Map::Units::UnitsState_Func::checkIfCitizenUnitIsAliveBasedOnState, this)(
                                 _0x04_targetUnitID),
                            BVar6 == FALSE
                                && (this->units[_0x04_targetUnitID].state.generic
                                    != (OpenSHC::Map::Units::States::US_STONE_DEATH_03
                                        | OpenSHC::Map::Units::States::US_IDLEUnk)))))
                    && (DAT_GameState::instance.mapAndTime.playerTeams[this->units[_0x04_targetUnitID].owner]
                        != DAT_GameState::instance.mapAndTime.playerTeams[_unitPlayerID])) {
                    _0x04_yDifference = ((int)(_microYUnit + (_microYUnit >> 0x1f & 7U)) >> 3)
                        - ((int)((int)this->units[_0x04_targetUnitID].microYPosition
                               + ((int)this->units[_0x04_targetUnitID].microYPosition >> 0x1f & 7U))
                            >> 3);
                    _xDifferenceToTarget = ((int)(_microXUnit + (_microXUnit >> 0x1f & 7U)) >> 3)
                        - ((int)((int)this->units[_0x04_targetUnitID].microXPosition
                               + ((int)this->units[_0x04_targetUnitID].microXPosition >> 0x1f & 7U))
                            >> 3);
                    if (_xDifferenceToTarget * _xDifferenceToTarget + _0x04_yDifference * _0x04_yDifference
                        <= _rangeSquared) {
                        int _shootDistanceScore
                            = MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::arrowShootingRelated,
                                DAT_EntityState::ptr)(_microXUnit, _microYUnit, _unitTotalHeight + 0x1e,
                                (int)((int)(this->units[_0x04_targetUnitID].microXPosition)),
                                (int)((int)(this->units[_0x04_targetUnitID].microYPosition)),
                                (int)((int)(this->units[_0x04_targetUnitID].buildingHeight + 0x1a
                                    + this->units[_0x04_targetUnitID].terrainOrClimbHeight)));
                        if (((_shootDistanceScore <= 0)
                                || (UVar4 = this->units[unitID].unitType, UVar4 == OpenSHC::Map::Units::UT_S_MANGONEL))
                            || (UVar4 == OpenSHC::Map::Units::UT_S_BALLISTA)) {
                            if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_HUNTER) {
                                return FALSE;
                            }
                            this->units[unitID].shootTargetedUnit = -2;
                            this->units[unitID].shootTargetMicroX = this->units[_0x04_targetUnitID].microXPosition;
                            this->units[unitID].shootTargetMicroY = this->units[_0x04_targetUnitID].microYPosition;
                            this->units[unitID].shootTargetZ = this->units[_0x04_targetUnitID].terrainOrClimbHeight;
                            return TRUE;
                        }
                        this->units[unitID].shootTargetedUnit = sVar9;
                        this->units[unitID].targetUID = this->units[_0x04_targetUnitID].uid;
                        this->units[unitID].distanceToEnemyUnitLadders = (short)_shootDistanceScore;
                        this->units[unitID].shootTargetMicroX = this->units[_0x04_targetUnitID].microXPosition;
                        this->units[unitID].shootTargetMicroY = this->units[_0x04_targetUnitID].microYPosition;
                        this->units[unitID].shootTargetZ = this->units[_0x04_targetUnitID].terrainOrClimbHeight;
                        if (100 < _shootDistanceScore) {
                            this->units[unitID].jugglerCount = 0;
                            this->units[_0x04_targetUnitID].field233_0x39a = 1;
                            return TRUE;
                        }
                        int _targetTotalHeight = (int)this->units[_0x04_targetUnitID].terrainOrClimbHeight
                            + (int)this->units[_0x04_targetUnitID].buildingHeight;
                        _unitPlayerID
                            = (int)this->units[unitID].buildingHeight + (int)this->units[unitID].terrainOrClimbHeight;
                        if (_targetTotalHeight + 0x46 < _unitPlayerID) {
                            this->units[unitID].jugglerCount = 1;
                            this->units[_0x04_targetUnitID].field233_0x39a = 1;
                            return TRUE;
                        }
                        this->units[unitID].jugglerCount = (_targetTotalHeight + -0x46 <= _unitPlayerID) - 1;
                        this->units[_0x04_targetUnitID].field233_0x39a = 1;
                        return TRUE;
                    }
                    if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[this->units[unitID].owner] != -1) {
                        return FALSE;
                    }
                }
                /*
                  fixme
                 */

                sVar9 = this->units[unitID]._someX_2;
                /*
                  fixmefixme
                 */

                this->units[unitID].targetedUnitID__OR__engineerMannedSiegeEngineRef = 0;
                this->units[unitID].shootTargetedUnit = 0;
                this->units[unitID].targetingType = OpenSHC::Map::Units::UIT_NO_INSTRUCTION_OR_MOVEUnk;
                if (sVar9 != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, this)(
                        unitID, (uint)((int)((int)sVar9)), (uint)((int)((int)this->units[unitID]._someY_2)), 0);
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

                sVar9 = this->units[unitID].targetID_OR_targetBuildingID;
                int _brazierEntityID;
                if ((DAT_TileMapState::instance.pitchDitches[sVar9].uid
                        == this->units[unitID]
                            .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID)
                    && (_brazierEntityID = MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::isBrazierNearby,
                            DAT_EntityState::ptr)((int)this->units[unitID].x, (int)((int)(this->units[unitID].y)),
                            (int)((
                                int)(this->units[unitID].buildingHeight + this->units[unitID].terrainOrClimbHeight))),
                        _brazierEntityID != 0)) {
                    this->units[unitID].shootTargetMicroX = DAT_TileMapState::instance.pitchDitches[sVar9].x * 8 + 4;
                    this->units[unitID].shootTargetMicroY = DAT_TileMapState::instance.pitchDitches[sVar9].y * 8 + 4;
                    this->units[unitID].shootTargetZ
                        = (ushort)DAT_TileMapState::instance
                              .HeightLayer[DAT_TileMapState::instance.pitchDitches[sVar9].tile];
                    this->units[unitID].shootTargetedUnit = -1;
                    return TRUE;
                }
            } else if (this->units[unitID].targetingType == OpenSHC::Map::Units::UIT_ATTACK_BUILDING) {
                sVar9 = this->units[unitID].targetID_OR_targetBuildingID;
                if (DAT_BuildingsState::instance.buildings[sVar9].uid
                    == this->units[unitID]
                        .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID) {
                    this->units[unitID].shootTargetMicroX = DAT_BuildingsState::instance.buildings[sVar9].x * 8
                        + (short)((int)(DAT_BuildingsState::instance.buildings[sVar9].widthOrHeight * 8) / 2);
                    this->units[unitID].shootTargetMicroY = DAT_BuildingsState::instance.buildings[sVar9].y * 8
                        + (short)((int)(DAT_BuildingsState::instance.buildings[sVar9].widthOrHeight * 8) / 2);
                    this->units[unitID].shootTargetZ = DAT_BuildingsState::instance.buildings[sVar9].terrainHeightUnk;
                    this->units[unitID].shootTargetedUnit = -1;
                    return TRUE;
                }
            } else if (this->units[unitID].targetingType == OpenSHC::Map::Units::UIT_ATTACK_WALL) {
                int _0x17_y = (int)this->units[unitID].attackAtTileY;
                int _0x17_x = (int)this->units[unitID].attackAtTileX;
                int _0x17_tile = DAT_ViewportRenderState::instance.translationMatrix[_0x17_y].addXgetTile + _0x17_x;
                BVar6 = MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                    DAT_ViewportRenderState::ptr)(_0x17_x, (uint)((int)(_0x17_y)));
                if ((BVar6 != FALSE) && ((DAT_TileMapState::instance.LogicLayer[_0x17_tile] & 0x100U) != 0)) {
                    this->units[unitID].shootTargetMicroX = this->units[unitID].attackAtTileX * 8;
                    this->units[unitID].shootTargetMicroY = this->units[unitID].attackAtTileY * 8;
                    this->units[unitID].shootTargetZ
                        = (short)((int)((uint)DAT_TileMapState::instance.HeightLayer[_0x17_tile]
                                      - (uint)DAT_TileMapState::instance.DefaultHeightLayer[_0x17_tile])
                              / 2)
                        + (ushort)DAT_TileMapState::instance.DefaultHeightLayer[_0x17_tile];
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
                    for (int local_24 = 0; local_24 < DAT_GameState::instance.playerDataArray[_unitPlayerID].enemies;
                        local_24 = local_24 + 1) {
                        int _enemy = DAT_GameState::instance.playerDataArray[_unitPlayerID].enemyIDArray[local_24];
                        if ((this->units[_enemy].dying != 0)
                            || (this->units[_enemy].uid
                                != DAT_GameState::instance.mapAndTime
                                    .playerEnemenyUnitUIDShortList[_unitPlayerID][local_24]))
                            continue;
                        switch (this->units[_enemy].unitType) {
                        case OpenSHC::Map::Units::UT_ANTELOPESHDEER:
                            if (this->units[unitID].unitType != OpenSHC::Map::Units::UT_HUNTER)
                                continue;
                            break;
                        case OpenSHC::Map::Units::UT_LIONSHWOLF:
                            sVar9 = this->units[_enemy].tribeID;
                            if ((DAT_TribesState::instance.tribes[sVar9].unknownBool02 != 0)
                                || ((DAT_TribesState::instance.tribes[sVar9].unknownBool01 == 0
                                    && ((this->units[_enemy].state.generic != 0xcf
                                        || (this->units[this->units[_enemy]
                                                            .targetedUnitID__OR__engineerMannedSiegeEngineRef]
                                                .isStalked
                                            != 0))))))
                                continue;
                            break;
                        case OpenSHC::Map::Units::UT_RABBIT:
                            _xDifferenceToTarget = (int)this->units[unitID].tribeID;
                            if (((this->units[unitID].unitType == OpenSHC::Map::Units::UT_HUNTER)
                                    || (_xDifferenceToTarget <= 0))
                                || (DAT_TribesState::instance.tribes[_xDifferenceToTarget].field71_0x212 == 0))
                                continue;
                            break;
                        case OpenSHC::Map::Units::UT_CAGEDOG:
                            if (DAT_GameState::instance.mapAndTime.playerTeams[this->units[_enemy].displayColorPlayerID]
                                == DAT_GameState::instance.mapAndTime.playerTeams[this->units[unitID].owner])
                                continue;
                            break;
                        case OpenSHC::Map::Units::UT_A_ASSASSIN:
                            if (160 < this->units[_enemy].assassinsMicroDistanceToEnemyUnk)
                                continue;
                        }
                        _xDifferenceToTarget = (int)this->units[_enemy].microYPosition;
                        iVar7 = (int)this->units[_enemy].microXPosition;
                        _yDifferenceToTarget = ((int)(_microYUnit + (_microYUnit >> 0x1f & 7U)) >> 3)
                            - ((int)(_xDifferenceToTarget + (_xDifferenceToTarget >> 0x1f & 7U)) >> 3);
                        _xDifferenceToTarget = ((int)(_microXUnit + (_microXUnit >> 0x1f & 7U)) >> 3)
                            - ((int)(iVar7 + (iVar7 >> 0x1f & 7U)) >> 3);
                        if (_rangeSquared
                            < _xDifferenceToTarget * _xDifferenceToTarget + _yDifferenceToTarget * _yDifferenceToTarget)
                            continue;
                        _xDifferenceToTarget = (int)this->units[_enemy].microXPosition;
                        if (_xDifferenceToTarget < _microXUnit) {
                            _xDifferenceToTarget = _microXUnit - _xDifferenceToTarget;
                        } else {
                            _xDifferenceToTarget = _xDifferenceToTarget - _microXUnit;
                        }
                        iVar7 = (int)this->units[_enemy].microYPosition;
                        if (iVar7 < _microYUnit) {
                            _yDifferenceToTarget = _microYUnit - iVar7;
                        } else {
                            _yDifferenceToTarget = iVar7 - _microYUnit;
                        }
                        if (_xDifferenceToTarget < _yDifferenceToTarget) {
                            _xDifferenceToTarget = _yDifferenceToTarget;
                        }
                        _xDifferenceToTarget = _xDifferenceToTarget + this->units[_enemy].field265_0x3dc * 0x32;
                        bool _scoreNeedsValidityCheck;
                        if (_entityType == 4) {
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
                                    != -1)
                                    continue;
                                if (this->units[_enemy].isSelectable_OR_matchTime == 0) {
                                    _xDifferenceToTarget = (_xDifferenceToTarget * 5 + 0x32) * 2;
                                } else {
                                    _xDifferenceToTarget = _xDifferenceToTarget * 3 + 100;
                                }
                            }
                            _scoreNeedsValidityCheck = true;
                        } else if (_entityType == 0x14) {
                            switch (this->units[_enemy].unitType) {
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
                                _xDifferenceToTarget = _xDifferenceToTarget * 5 + 200;
                                break;
                            case OpenSHC::Map::Units::UT_E_PIKE:
                            case OpenSHC::Map::Units::UT_E_SWORD:
                            case OpenSHC::Map::Units::UT_E_KNIGHT:
                            case OpenSHC::Map::Units::UT_A_SWORDSMAN:
                                break;
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
                                _xDifferenceToTarget = _xDifferenceToTarget * 2 + 100;
                                break;
                            default:
                                _xDifferenceToTarget = (_xDifferenceToTarget * 5 + 200) * 2;
                            }
                            _scoreNeedsValidityCheck = false;
                        } else if (_entityType != 0x25) {
                            if ((this->units[_enemy].field289_0x3ff != 0)
                                && (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[this->units[_enemy].owner]
                                    == -1)) {
                                _xDifferenceToTarget = _xDifferenceToTarget / 3;
                            }
                            switch (this->units[_enemy].unitType) {
                            case OpenSHC::Map::Units::UT_E_ARCHER:
                            case OpenSHC::Map::Units::UT_E_XBOW:
                            case OpenSHC::Map::Units::UT_A_ARCHER:
                            case OpenSHC::Map::Units::UT_A_HARCHER:
                                _xDifferenceToTarget = _xDifferenceToTarget + 0x4b;
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
                                _xDifferenceToTarget = _xDifferenceToTarget * 5 + 200;
                                break;
                            case OpenSHC::Map::Units::UT_E_LADDER:
                                _xDifferenceToTarget = _xDifferenceToTarget * 7 + 300;
                                break;
                            case OpenSHC::Map::Units::UT_E_ENGINEER:
                            case OpenSHC::Map::Units::UT_S_CATAPULT:
                            case OpenSHC::Map::Units::UT_S_TREBUCHET:
                            case OpenSHC::Map::Units::UT_LORD:
                                _xDifferenceToTarget = _xDifferenceToTarget * 2 + 100;
                                break;
                            default:
                                _xDifferenceToTarget = (_xDifferenceToTarget * 5 + 200) * 2;
                                break;
                            case OpenSHC::Map::Units::UT_S_MANGONEL:
                            case OpenSHC::Map::Units::UT_S_BALLISTA:
                            case OpenSHC::Map::Units::UT_A_FIRETHROWER:
                            case OpenSHC::Map::Units::UT_S_FBALLISTA:
                                break;
                            }
                            _scoreNeedsValidityCheck = false;
                        } else {
                            switch (this->units[_enemy].unitType) {
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
                                _xDifferenceToTarget = _xDifferenceToTarget * 5 + 200;
                                break;
                            case OpenSHC::Map::Units::UT_E_PIKE:
                            case OpenSHC::Map::Units::UT_E_SWORD:
                            case OpenSHC::Map::Units::UT_E_KNIGHT:
                            case OpenSHC::Map::Units::UT_A_SWORDSMAN:
                                break;
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
                                _xDifferenceToTarget = _xDifferenceToTarget * 2 + 100;
                                break;
                            default:
                                continue;
                            case OpenSHC::Map::Units::UT_LORD:
                                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[_unitPlayerID] != -1)
                                    _xDifferenceToTarget = _xDifferenceToTarget * 5 + 200;
                                break;
                            }
                            _scoreNeedsValidityCheck = true;
                        }
                        if (!_scoreNeedsValidityCheck || _xDifferenceToTarget != -1) {
                            if (((_xDifferenceToTarget < local_30) || (_xDifferenceToTarget < local_2c))
                                && (iVar7
                                    = MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::arrowShootingRelated,
                                        DAT_EntityState::ptr)(_microXUnit, _microYUnit, _unitTotalHeight + 0x1e,
                                        (int)((int)(this->units[_enemy].microXPosition)), iVar7,
                                        (int)((int)(this->units[_enemy].buildingHeight + 0x1a
                                            + this->units[_enemy].terrainOrClimbHeight))),
                                    0 < iVar7)) {
                                if (_xDifferenceToTarget < local_30) {
                                    local_30 = _xDifferenceToTarget;
                                    _validTargetID = _enemy;
                                    local_8 = iVar7;
                                }
                                if ((this->units[_enemy].field233_0x39a == 0) && (_xDifferenceToTarget < local_2c)) {
                                    local_2c = _xDifferenceToTarget;
                                    local_10 = _enemy;
                                    local_c = iVar7;
                                }
                            }
                        }
                    }
                    if (_validTargetID == 0) {
                        return FALSE;
                    }
                    if ((local_10 != 0) && (local_2c < (local_30 * 3) / 2)) {
                        _validTargetID = local_10;
                        local_8 = local_c;
                    }
                    if (_entityType == 4) {
                        this->units[unitID].shootTargetedUnit = -2;
                        this->units[unitID].shootTargetMicroX = this->units[_validTargetID].microXPosition;
                        this->units[unitID].shootTargetMicroY = this->units[_validTargetID].microYPosition;
                        this->units[unitID].shootTargetZ = this->units[_validTargetID].terrainOrClimbHeight;
                        return TRUE;
                    }
                    sVar9 = (short)_validTargetID;
                    if ((_entityType == 0x25) || (_entityType == 0x14)) {
                        this->units[unitID].shootTargetedUnit = sVar9;
                        this->units[unitID].targetUID = this->units[_validTargetID].uid;
                        this->units[unitID].distanceToEnemyUnitLadders = (short)local_8;
                        this->units[unitID].shootTargetMicroX = this->units[_validTargetID].microXPosition;
                        this->units[unitID].shootTargetMicroY = this->units[_validTargetID].microYPosition;
                        this->units[unitID].shootTargetZ = this->units[_validTargetID].terrainOrClimbHeight;
                        return TRUE;
                    }
                    this->units[_validTargetID].field265_0x3dc = this->units[_validTargetID].field265_0x3dc + 1;
                    this->units[unitID].shootTargetedUnit = sVar9;
                    this->units[unitID].field266_0x3de = sVar9;
                    this->units[unitID].targetUID = this->units[_validTargetID].uid;
                    this->units[unitID].distanceToEnemyUnitLadders = (short)local_8;
                    if (100 < local_8) {
                        this->units[unitID].jugglerCount = 0;
                        this->units[_validTargetID].field233_0x39a = 1;
                        return TRUE;
                    }
                    _unitPlayerID = (int)this->units[_validTargetID].terrainOrClimbHeight
                        + (int)this->units[_validTargetID].buildingHeight;
                    _microXUnit
                        = (int)this->units[unitID].buildingHeight + (int)this->units[unitID].terrainOrClimbHeight;
                    if (_unitPlayerID + 0x46 < _microXUnit) {
                        this->units[unitID].jugglerCount = 1;
                        this->units[_validTargetID].field233_0x39a = 1;
                        return TRUE;
                    }
                    this->units[unitID].jugglerCount = (_unitPlayerID + -0x46 <= _microXUnit) - 1;
                    this->units[_validTargetID].field233_0x39a = 1;
                    return TRUE;
                }
                sVar9 = this->units[unitID].attackAtTileY;
                sVar5 = this->units[unitID].attackAtTileX;
                this->units[unitID].jugglerCount = -1;
                BVar6 = MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                    DAT_ViewportRenderState::ptr)((int)sVar5, (uint)((int)((int)sVar9)));
                if (BVar6 != FALSE) {
                    sVar5 = this->units[unitID].attackAtTileX;
                    this->units[unitID].shootTargetMicroX = sVar5 * 8;
                    this->units[unitID].shootTargetedUnit = -1;
                    this->units[unitID].shootTargetMicroY = sVar9 * 8;
                    this->units[unitID].shootTargetZ
                        = (ushort)DAT_TileMapState::instance
                              .HeightLayer[DAT_ViewportRenderState::instance.translationMatrix[sVar9].addXgetTile
                                  + (int)sVar5];
                    return TRUE;
                }
            }
            this->units[unitID].targetingType = OpenSHC::Map::Units::UIT_NO_INSTRUCTION_OR_MOVEUnk;
            return FALSE;
        }

    }
}
}
