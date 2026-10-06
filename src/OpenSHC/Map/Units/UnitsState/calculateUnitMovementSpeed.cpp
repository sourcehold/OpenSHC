#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitLogicState;
        using OpenSHC::Map::Units::UnitType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0052F7E0
        void UnitsState::calculateUnitMovementSpeed(int unitID)
        {
            this->units[unitID].field322_0x440 = this->units[unitID].field322_0x440 + 1;
            ushort _tick = this->units[unitID].field322_0x440;
            int _tile = this->units[unitID].tile;
            int _buildingID = (short)DAT_TileMapState::instance.BuildingLayer[_tile];
            uint _logicFlags = DAT_TileMapState::instance.LogicLayer[_tile];
            if (this->units[unitID].unknownCountdown_0x402 == 0) {
                if (_buildingID == 0 && (_logicFlags & 0x10000500) == 0) {
                    if ((_tick + unitID & 7) != 0) {
                        return;
                    }
                } else if ((_tick + unitID & 3) != 0) {
                    return;
                }
            }
            this->units[unitID].isMatchingSpeed = false;
            int _organismID = (short)DAT_TileMapState::instance.OrganismLayer[_tile];
            uint _isOnRoad = _logicFlags & 0x800000;
            uint _isInMoat = _logicFlags & 0x20000000;
            uint _isFord = _logicFlags & 0x200000;
            int _tileHeight = DAT_TileMapState::instance.HeightLayer[_tile];
            if (_organismID != 0 && _organismID < 2000) {
                DAT_LandscapeState::instance.trees[_organismID].state = 3;
            }
            if (_isInMoat != 0 && (DAT_TileMapState::instance.MacroLayer[_tile] & 0x3f) == 1) {
                _isInMoat = 0;
            }
            if ((DAT_TileMapState::instance.LogicLayer[_tile] & 0x40000000) != 0) {
                _isInMoat = 1;
            }
            if (_isOnRoad != 0) {
                this->units[unitID].calculatedMovementSpeed = this->units[unitID].movementSpeed;
            } else {
                short _unitHeight = this->units[unitID].terrainOrClimbHeight;
                if (_tileHeight > _unitHeight) {
                    int _heightDifference = _tileHeight - _unitHeight;
                    if (_heightDifference > 16) {
                        this->units[unitID].terrainOrClimbHeight = (short)_tileHeight;
                        this->units[unitID].calculatedMovementSpeed = this->units[unitID].movementSpeed;
                    } else if (_heightDifference >= 12) {
                        this->units[unitID].terrainOrClimbHeight = _unitHeight + 4;
                        this->units[unitID].calculatedMovementSpeed = this->units[unitID].movementSpeed + 5;
                        this->units[unitID].movementRunUpTime = 12;
                    } else if (_heightDifference >= 8) {
                        this->units[unitID].terrainOrClimbHeight = _unitHeight + 4;
                        this->units[unitID].calculatedMovementSpeed = this->units[unitID].movementSpeed + 4;
                        this->units[unitID].movementRunUpTime = 8;
                    } else if (_heightDifference >= 4) {
                        this->units[unitID].terrainOrClimbHeight = _unitHeight + 3;
                        this->units[unitID].calculatedMovementSpeed = this->units[unitID].movementSpeed + 3;
                    } else if (_heightDifference >= 2) {
                        this->units[unitID].terrainOrClimbHeight = _unitHeight + 2;
                        this->units[unitID].calculatedMovementSpeed = this->units[unitID].movementSpeed + 1;
                    } else {
                        this->units[unitID].terrainOrClimbHeight = _unitHeight + 1;
                        this->units[unitID].calculatedMovementSpeed = this->units[unitID].movementSpeed;
                    }
                } else if (_tileHeight < _unitHeight) {
                    int _heightDifference = _unitHeight - _tileHeight;
                    if (_heightDifference > 16) {
                        this->units[unitID].terrainOrClimbHeight = (short)_tileHeight;
                        this->units[unitID].calculatedMovementSpeed = this->units[unitID].movementSpeed;
                    } else if (_heightDifference >= 12) {
                        this->units[unitID].terrainOrClimbHeight = _unitHeight - 4;
                        this->units[unitID].calculatedMovementSpeed = this->units[unitID].movementSpeed;
                    } else if (_heightDifference >= 8) {
                        this->units[unitID].terrainOrClimbHeight = _unitHeight - 3;
                        this->units[unitID].calculatedMovementSpeed = this->units[unitID].movementSpeed;
                    } else if (_heightDifference >= 4) {
                        this->units[unitID].terrainOrClimbHeight = _unitHeight - 2;
                        this->units[unitID].calculatedMovementSpeed = this->units[unitID].movementSpeed;
                    } else {
                        this->units[unitID].terrainOrClimbHeight = _unitHeight - 1;
                    }
                } else if (this->units[unitID].isSelectable_OR_matchTime == 0) {
                    this->units[unitID].calculatedMovementSpeed = this->units[unitID].movementSpeed;
                } else {
                    int _tribeID = this->units[unitID].tribeID;
                    this->units[unitID].calculatedMovementSpeed = this->units[unitID].movementSpeed;
                    /* The original stores the own speed again in every branch that does not match the tribe. */
                    if (_tribeID <= 0) {
                        this->units[unitID].calculatedMovementSpeed = this->units[unitID].movementSpeed;
                    } else if (DAT_TribesState::instance.tribes[_tribeID].unitType != (UnitType)0) {
                        this->units[unitID].calculatedMovementSpeed = this->units[unitID].movementSpeed;
                    } else if (DAT_TribesState::instance.tribes[_tribeID].freeUnitSpeeds != 0) {
                        this->units[unitID].calculatedMovementSpeed = this->units[unitID].movementSpeed;
                    } else {
                        this->units[unitID].calculatedMovementSpeed
                            = DAT_TribesState::instance.tribes[_tribeID].movementSpeed;
                        if (this->units[unitID].calculatedMovementSpeed < this->units[unitID].movementSpeed) {
                            this->units[unitID].calculatedMovementSpeed = this->units[unitID].movementSpeed;
                        }
                        this->units[unitID].isMatchingSpeed = true;
                    }
                }
            }
            if (_isInMoat != 0) {
                if ((char)this->units[unitID].negativeHeight < 0x18) {
                    this->units[unitID].negativeHeight = this->units[unitID].negativeHeight + 4;
                }
                if ((char)this->units[unitID].negativeHeight < 5) {
                    this->units[unitID].calculatedMovementSpeed = this->units[unitID].calculatedMovementSpeed + 3;
                } else if ((char)this->units[unitID].negativeHeight < 10) {
                    this->units[unitID].calculatedMovementSpeed = this->units[unitID].calculatedMovementSpeed + 4;
                } else {
                    this->units[unitID].calculatedMovementSpeed = this->units[unitID].calculatedMovementSpeed + 6;
                }
            } else if (_isFord != 0) {
                if ((char)this->units[unitID].negativeHeight < 0x10) {
                    this->units[unitID].negativeHeight = this->units[unitID].negativeHeight + 4;
                }
                this->units[unitID].calculatedMovementSpeed = this->units[unitID].calculatedMovementSpeed + 2;
            } else if (this->units[unitID].negativeHeight != 0) {
                this->units[unitID].negativeHeight = this->units[unitID].negativeHeight - 8;
                if ((char)this->units[unitID].negativeHeight < 0) {
                    this->units[unitID].negativeHeight = 0;
                }
                this->units[unitID].calculatedMovementSpeed = this->units[unitID].calculatedMovementSpeed + 3;
            }
            this->units[unitID].field289_0x3ff = 0;
            if ((DAT_TileMapState::instance.LogicLayer[_tile] & 8) != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TroopValueState_Func::registerSpottedEnemyTile,
                    DAT_TroopValueState::ptr)(_tile);
            }
            if (_buildingID == 0) {
                return;
            }
            if (DAT_BuildingsState::instance.buildings[_buildingID].buildingType < 0x29) {
                return;
            }
            if (DAT_BuildingsState::instance.buildings[_buildingID].buildingType > 0x2c) {
                return;
            }
            int _owner = this->units[unitID].owner;
            this->units[unitID].field289_0x3ff = 1;
            if (DAT_BuildingsState::instance.buildings[_buildingID].owner == _owner) {
                return;
            }
            if (this->units[unitID].dying != 0) {
                return;
            }
            if (this->units[unitID].logicalState != OpenSHC::Map::Units::ULS_NORMAL) {
                return;
            }
            if (_owner == 0) {
                return;
            }
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[_owner] != -1) {
                return;
            }
            DAT_TroopValueState::instance.attackInfo.field128058_0x469dc
                = DAT_TroopValueState::instance.attackInfo.field128058_0x469dc + 1;
        }

    }
}
}
