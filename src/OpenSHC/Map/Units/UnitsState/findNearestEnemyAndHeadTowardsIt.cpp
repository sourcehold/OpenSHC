#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitInstructionType;
        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::Map::Units::Behavior::UnitStanceEnum;
        using OpenSHC::Map::Units::States::UnitState;

        // FUNCTION: STRONGHOLDCRUSADER 0x0054A7B0
        dword UnitsState::findNearestEnemyAndHeadTowardsIt(int unitID)
        {
            int _microX = this->units[unitID].microXPosition;
            int _microY = this->units[unitID].microYPosition;
            int _playerID = this->units[unitID].owner;
            dword _area = (short)DAT_TileMapState::instance.PathConnectionLayer[this->units[unitID].tile];
            this->unitDistanceComputationResultUnk = 100000;
            int _minDistance = 100000;
            int _chosenRawDistance = 0;
            int _bestScore = 100000;
            int _foundEnemyID = 0;
            int _visionDivisor = 1;
            int _skipStanceSearch = 0;
            int _stanceBasedRange = 0;
            short _isRallying = 0;
            if ((this->units[unitID].SA != 0
                    || (this->units[unitID].movementType_OR_targetUnitID != 0
                        && this->units[unitID].state.generic == OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION))
                && this->units[unitID].tribeID != 0) {
                _isRallying = DAT_TribesState::instance.tribes[this->units[unitID].tribeID].isRallyingUnk;
                if (DAT_TribesState::instance.tribes[this->units[unitID].tribeID].unitStance
                    == OpenSHC::Map::Units::Behavior::USE_DEFENSIVE) {
                    _stanceBasedRange = 40;
                } else if (DAT_TribesState::instance.tribes[this->units[unitID].tribeID].unitStance
                    == OpenSHC::Map::Units::Behavior::USE_AGGRESSIVE) {
                    _stanceBasedRange = 200;
                }
            }
            if (this->units[unitID].targetingType == OpenSHC::Map::Units::UIT_UNIT_ATTACK_UNIT) {
                _skipStanceSearch = 1;
                switch (this->units[unitID].unitType) {
                case OpenSHC::Map::Units::UT_TUNNELER:
                case OpenSHC::Map::Units::UT_E_SPEAR:
                case OpenSHC::Map::Units::UT_E_PIKE:
                case OpenSHC::Map::Units::UT_E_MACE:
                case OpenSHC::Map::Units::UT_E_SWORD:
                case OpenSHC::Map::Units::UT_E_KNIGHT:
                case OpenSHC::Map::Units::UT_E_MONK:
                case OpenSHC::Map::Units::UT_LORD:
                case OpenSHC::Map::Units::UT_A_SLAVE:
                case OpenSHC::Map::Units::UT_A_ASSASSIN:
                case OpenSHC::Map::Units::UT_A_SWORDSMAN:
                    _skipStanceSearch = 0;
                    if (this->units[unitID].tribeID != 0) {
                        int _tribeUnitID = DAT_TribesState::instance.tribes[this->units[unitID].tribeID].someUnitID;
                        if (_tribeUnitID != 0
                            && this->units[_tribeUnitID].uid
                                == DAT_TribesState::instance.tribes[this->units[unitID].tribeID].someUnitUID) {
                            _skipStanceSearch = 1;
                            break;
                        }
                    }
                    this->units[unitID].targetingType = OpenSHC::Map::Units::UIT_NO_INSTRUCTION_OR_MOVEUnk;
                }
            } else if (this->units[unitID].targetingType == OpenSHC::Map::Units::UIT_ATTACK_LAND) {
                switch (this->units[unitID].unitType) {
                case OpenSHC::Map::Units::UT_E_SPEAR:
                case OpenSHC::Map::Units::UT_E_PIKE:
                case OpenSHC::Map::Units::UT_E_MACE:
                case OpenSHC::Map::Units::UT_E_SWORD:
                case OpenSHC::Map::Units::UT_E_KNIGHT:
                case OpenSHC::Map::Units::UT_E_MONK:
                case OpenSHC::Map::Units::UT_A_SLAVE:
                case OpenSHC::Map::Units::UT_A_ASSASSIN:
                case OpenSHC::Map::Units::UT_A_SWORDSMAN:
                    if (this->units[unitID].lookForEnemy >= 0
                        && this->units[unitID].state.generic != OpenSHC::Map::Units::States::US_MELEE_ATTACK) {
                        if (this->units[unitID].attackAtTileX == this->units[unitID].x
                            && this->units[unitID].attackAtTileY == this->units[unitID].y) {
                            this->units[unitID].targetingType = (UnitInstructionType)0;
                            break;
                        }
                        this->units[unitID].plannedDestinationY = this->units[unitID].attackAtTileY;
                        this->units[unitID].plannedDestinationX = this->units[unitID].attackAtTileX;
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, this)(
                            unitID, this->units[unitID].attackAtTileX, this->units[unitID].attackAtTileY, 0);
                        int _lookAhead = -(this->units[unitID].totalSizeOfPathPlan / 2);
                        this->units[unitID].state.generic = OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION;
                        if (_lookAhead > -0x33) {
                            _lookAhead = -0x32;
                        }
                        this->units[unitID].lookForEnemy = (short)_lookAhead;
                    }
                    _skipStanceSearch = 1;
                }
            }
            if (this->units[unitID].isSelectable_OR_matchTime == 0) {
                _skipStanceSearch = 1;
            }
            if (DAT_GameState::instance.playerDataArray[_playerID].enemies < 5) {
                _visionDivisor = 5;
            } else if (DAT_GameState::instance.playerDataArray[_playerID].enemies < 15) {
                _visionDivisor = 2;
            }
            for (int _enemyIndex = 0; _enemyIndex < DAT_GameState::instance.playerDataArray[_playerID].enemies;
                ++_enemyIndex) {
                int _enemyUnitID = DAT_GameState::instance.playerDataArray[_playerID].enemyIDArray[_enemyIndex];
                int _distanceX;
                if (this->units[_enemyUnitID].microXPosition < _microX) {
                    _distanceX = _microX - this->units[_enemyUnitID].microXPosition;
                } else {
                    _distanceX = this->units[_enemyUnitID].microXPosition - _microX;
                }
                int _distanceY;
                if (this->units[_enemyUnitID].microYPosition < _microY) {
                    _distanceY = _microY - this->units[_enemyUnitID].microYPosition;
                } else {
                    _distanceY = this->units[_enemyUnitID].microYPosition - _microY;
                }
                int _approximateDistance;
                if (_distanceX < _distanceY) {
                    /* pythagorean approximation */
                    _approximateDistance = (((_distanceX * 2) / 5) * _distanceX) / _distanceY + _distanceY;
                } else if (_distanceX == 0) {
                    /* fixme: bug: I think this needs to be set not to 0 but to _distanceY */
                    _approximateDistance = 0;
                } else {
                    _approximateDistance = (((_distanceY * 2) / 5) * _distanceY) / _distanceX + _distanceX;
                }
                if (_approximateDistance < _minDistance) {
                    _minDistance = _approximateDistance;
                }
                if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_A_ASSASSIN
                    && this->units[_enemyUnitID].isSelectable_OR_matchTime != 0
                    && _approximateDistance < (int)this->unitDistanceComputationResultUnk) {
                    this->unitDistanceComputationResultUnk = _approximateDistance;
                }
                if (_skipStanceSearch || _stanceBasedRange == 0 || this->units[unitID].lookForEnemy < 0) {
                    continue;
                }
                int _score = _approximateDistance;
                if (this->units[unitID]._someX_2 != 0 && _isRallying == 0 && _stanceBasedRange == 40) {
                    int _savedDistanceX;
                    if (this->units[unitID]._someX_2 * 8 < this->units[_enemyUnitID].microXPosition) {
                        _savedDistanceX = this->units[_enemyUnitID].microXPosition + this->units[unitID]._someX_2 * -8;
                    } else {
                        _savedDistanceX = this->units[unitID]._someX_2 * 8 - this->units[_enemyUnitID].microXPosition;
                    }
                    if (this->units[unitID]._someY_2 * 8 < this->units[_enemyUnitID].microYPosition) {
                        _score = this->units[_enemyUnitID].microYPosition + this->units[unitID]._someY_2 * -8;
                    } else {
                        _score = this->units[unitID]._someY_2 * 8 - this->units[_enemyUnitID].microYPosition;
                    }
                    if (_score <= _savedDistanceX) {
                        _score = _savedDistanceX;
                    }
                }
                int _rawDistance = _score;
                if (_score > _stanceBasedRange) {
                    continue;
                }
                if (this->units[_enemyUnitID].uid
                    != DAT_GameState::instance.mapAndTime.playerEnemenyUnitUIDShortList[_playerID][_enemyIndex]) {
                    continue;
                }
                _score = _score
                    + DAT_UnitPropertiesDefinedData::instance
                            .UnitVisionBonus[(this->units[unitID].fixedRng + _enemyUnitID) % 10]
                        / _visionDivisor;
                if (this->units[_enemyUnitID].state.generic == OpenSHC::Map::Units::States::US_MELEE_ATTACK) {
                    _score = (this->units[_enemyUnitID].attackedBy * 50 + _score) * 2;
                    if (this->units[_enemyUnitID].attackedBy >= 3) {
                        continue;
                    }
                }
                if (this->units[_enemyUnitID].huntedBy >= 2) {
                    _score = _score + this->units[_enemyUnitID].huntedBy * 0x32;
                    if (this->units[_enemyUnitID].huntedBy >= 3
                        && this->units[unitID].movementType_OR_targetUnitID != _enemyUnitID) {
                        continue;
                    }
                }
                if (this->units[_enemyUnitID].isStalked != 0
                    && this->units[_enemyUnitID].unitType != OpenSHC::Map::Units::UT_LIONSHWOLF
                    && this->units[_enemyUnitID].unitType != OpenSHC::Map::Units::UT_CAGEDOG) {
                    continue;
                }
                switch (this->units[_enemyUnitID].unitType) {
                case OpenSHC::Map::Units::UT_PEASANT:
                    _score = _score * 8 + 200;
                    break;
                case OpenSHC::Map::Units::UT_E_ARCHER:
                case OpenSHC::Map::Units::UT_E_XBOW:
                case OpenSHC::Map::Units::UT_A_ARCHER:
                case OpenSHC::Map::Units::UT_A_HARCHER:
                case OpenSHC::Map::Units::UT_A_FIRETHROWER:
                    break;
                case OpenSHC::Map::Units::UT_E_SPEAR:
                case OpenSHC::Map::Units::UT_E_PIKE:
                case OpenSHC::Map::Units::UT_E_MACE:
                case OpenSHC::Map::Units::UT_E_SWORD:
                case OpenSHC::Map::Units::UT_E_KNIGHT:
                case OpenSHC::Map::Units::UT_E_LADDER:
                case OpenSHC::Map::Units::UT_E_MONK:
                case OpenSHC::Map::Units::UT_A_SLAVE:
                case OpenSHC::Map::Units::UT_A_SLINGER:
                case OpenSHC::Map::Units::UT_A_ASSASSIN:
                case OpenSHC::Map::Units::UT_A_SWORDSMAN:
                    _score = _score * 2 + 100;
                    break;
                case OpenSHC::Map::Units::UT_E_ENGINEER:
                case OpenSHC::Map::Units::UT_S_CATAPULT:
                case OpenSHC::Map::Units::UT_S_TREBUCHET:
                case OpenSHC::Map::Units::UT_S_MANGONEL:
                case OpenSHC::Map::Units::UT_S_TOWER:
                case OpenSHC::Map::Units::UT_S_BATTERINGRAM:
                case OpenSHC::Map::Units::UT_S_SHIELD:
                case OpenSHC::Map::Units::UT_S_BALLISTA:
                case OpenSHC::Map::Units::UT_S_FBALLISTA:
                    _score = _score + 0x19;
                    break;
                case OpenSHC::Map::Units::UT_LORD:
                    _score = _score / 4;
                    break;
                default:
                    _score = _score * 4 + 200;
                }
                if (this->units[unitID].movementType_OR_targetUnitID == _enemyUnitID) {
                    _score = _score / 2;
                }
                if (_score >= _bestScore) {
                    continue;
                }
                int _enemyTotalHeight
                    = this->units[_enemyUnitID].buildingHeight + this->units[_enemyUnitID].terrainOrClimbHeight;
                int _bestApproachDirection = -1;
                int _bestApproachDistance = 10000;
                for (int _direction = 0; _direction < 8; ++_direction) {
                    int _approachTile = DAT_TileMapState::instance.directionTranslationMatrix[this->units[_enemyUnitID]
                                                .y][DAT_UnitPropertiesDefinedData::instance.field84_0x11cb4[_direction]]
                        + this->units[_enemyUnitID].tile;
                    if (DAT_TileMapState::instance.UnitLayer[_approachTile] != 0) {
                        continue;
                    }
                    uint _tileHeight = MACRO_CALL_MEMBER(
                        OpenSHC::Map::TileMapState_Func::getTotalHeightAtTile, DAT_TileMapState::ptr)(_approachTile);
                    if (_enemyTotalHeight >= (int)(_tileHeight + 0x10)) {
                        continue;
                    }
                    if ((int)(_tileHeight - 0x10) >= _enemyTotalHeight) {
                        continue;
                    }
                    int _approachY = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[_approachTile];
                    int _approachX
                        = _approachTile - DAT_ViewportRenderState::instance.translationMatrix[_approachY].addXgetTile;
                    int _approachDistanceX;
                    if (_approachX * 8 < _microX) {
                        _approachDistanceX = _microX + _approachX * -8;
                    } else {
                        _approachDistanceX = _approachX * 8 - _microX;
                    }
                    int _approachDistance;
                    if (_approachY * 8 < _microY) {
                        _approachDistance = _microY + _approachY * -8;
                    } else {
                        _approachDistance = _approachY * 8 - _microY;
                    }
                    if (_approachDistance <= _approachDistanceX) {
                        _approachDistance = _approachDistanceX;
                    }
                    if (_approachDistance < _bestApproachDistance) {
                        _bestApproachDistance = _approachDistance;
                        _bestApproachDirection = _direction;
                    }
                }
                if (_bestApproachDirection >= 0) {
                    _bestScore = _score;
                    _chosenRawDistance = _rawDistance;
                    _foundEnemyID = _enemyUnitID;
                }
            }
            int _restoreSavedDestination = 0;
            if (_stanceBasedRange == 0) {
                if (this->units[unitID].lookForEnemy == 0) {
                    this->units[unitID].movementType_OR_targetUnitID = 0;
                    if (this->units[unitID].state.generic == OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION) {
                        _restoreSavedDestination = 1;
                    }
                }
            } else if (this->units[unitID].lookForEnemy >= 0) {
                if (_skipStanceSearch) {
                    if (this->units[unitID].lookForEnemy == 0) {
                        this->units[unitID].movementType_OR_targetUnitID = 0;
                        if (this->units[unitID].state.generic == OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION) {
                            _restoreSavedDestination = 1;
                        }
                    }
                } else {
                    int _headedToEnemy = 0;
                    if (_foundEnemyID != 0
                        && MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                                 calculateCanPlayerUnitsNavigateToAreaFromArea,
                               DAT_PathFindingState::ptr)(this->units[unitID].owner, (short)_area,
                               (short)DAT_TileMapState::instance.PathConnectionLayer[this->units[_foundEnemyID].tile],
                               this->units[unitID].unitCanClimb)
                            != 0) {
                        this->units[unitID].state.generic = OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION;
                        this->units[unitID].animationCycleNumber = 0;
                        if (this->units[unitID]._someX_2 == 0) {
                            this->units[unitID]._someX_2 = this->units[unitID].destinationX_2Unk;
                            this->units[unitID]._someY_2 = this->units[unitID].destinationY_2Unk;
                        }
                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::findNearestValidDigTileNearTarget,
                            DAT_TileMapState::ptr)(this->units[unitID].x, this->units[unitID].y,
                            this->units[_foundEnemyID].x, this->units[_foundEnemyID].y);
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, this)(unitID,
                            DAT_TileMapState::instance.field155_0x5549a8, DAT_TileMapState::instance.field156_0x5549ac,
                            0);
                        int _lookAhead = -0x1e - _chosenRawDistance;
                        this->units[unitID].moveDelay = 0;
                        if (_lookAhead > -0x33) {
                            _lookAhead = -0x32;
                        }
                        this->units[unitID].lookForEnemy = (short)_lookAhead;
                        if (this->units[unitID].movementType_OR_targetUnitID != _foundEnemyID) {
                            this->units[unitID].movementType_OR_targetUnitID = (short)_foundEnemyID;
                            this->units[_foundEnemyID].huntedBy = this->units[_foundEnemyID].huntedBy + 1;
                        }
                        _headedToEnemy = 1;
                    }
                    if (!_headedToEnemy) {
                        this->units[unitID].lookForEnemy = -8;
                        this->units[unitID].movementType_OR_targetUnitID = 0;
                        _restoreSavedDestination = 1;
                    }
                }
            }
            if (_restoreSavedDestination && this->units[unitID]._someX_2 != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, this)(
                    unitID, this->units[unitID]._someX_2, this->units[unitID]._someY_2, 0);
                this->units[unitID].moveDelay = 0;
                this->units[unitID]._someY_2 = 0;
                this->units[unitID]._someX_2 = 0;
                this->units[unitID].state.generic = OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION;
            }
            if (_minDistance > 32000) {
                _minDistance = 32000;
            }
            return _minDistance;
        }

    }
}
}
