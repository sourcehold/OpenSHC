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
            int _tile = this->units[unitID].tile;
            int _buildingID = DAT_TileMapState::instance.BuildingLayer[_tile];
            uint _logicFlags = DAT_TileMapState::instance.LogicLayer[_tile];
            if (this->units[unitID].unknownCountdown_0x402 == 0) {
                if (_buildingID == 0 && (_logicFlags & 0x10000500) == 0) {
                    if ((this->units[unitID].field322_0x440 + unitID & 7) != 0) {
                        return;
                    }
                } else if ((this->units[unitID].field322_0x440 + unitID & 3) != 0) {
                    return;
                }
            }
            this->units[unitID].isMatchingSpeed = false;
            uint _isInMoat = _logicFlags & 0x20000000;
            byte _tileHeight = DAT_TileMapState::instance.HeightLayer[_tile];
            if (DAT_TileMapState::instance.OrganismLayer[_tile] != 0
                && DAT_TileMapState::instance.OrganismLayer[_tile] < 2000) {
                DAT_LandscapeState::instance.trees[DAT_TileMapState::instance.OrganismLayer[_tile]].state = 3;
            }
            if (_isInMoat != 0 && (DAT_TileMapState::instance.MacroLayer[_tile] & 0x3f) == 1) {
                _isInMoat = 0;
            }
            if ((_logicFlags & 0x40000000) != 0) {
                _isInMoat = 1;
            }
            if ((_logicFlags & 0x800000) != 0) {
                this->units[unitID].calculatedMovementSpeed = this->units[unitID].movementSpeed;
            } else if (this->units[unitID].terrainOrClimbHeight < _tileHeight) {
                int _heightDifference = _tileHeight - this->units[unitID].terrainOrClimbHeight;
                /* the climb bands are split by halving, not as a flat ladder */
                if (_heightDifference < 0x11) {
                    if (_heightDifference < 0xc) {
                        if (_heightDifference < 8) {
                            if (_heightDifference < 4) {
                                if (_heightDifference < 2) {
                                    this->units[unitID].terrainOrClimbHeight
                                        = this->units[unitID].terrainOrClimbHeight + 1;
                                    this->units[unitID].calculatedMovementSpeed = this->units[unitID].movementSpeed;
                                } else {
                                    this->units[unitID].terrainOrClimbHeight
                                        = this->units[unitID].terrainOrClimbHeight + 2;
                                    this->units[unitID].calculatedMovementSpeed = this->units[unitID].movementSpeed + 1;
                                }
                            } else {
                                this->units[unitID].terrainOrClimbHeight = this->units[unitID].terrainOrClimbHeight + 3;
                                this->units[unitID].calculatedMovementSpeed = this->units[unitID].movementSpeed + 3;
                            }
                        } else {
                            this->units[unitID].terrainOrClimbHeight = this->units[unitID].terrainOrClimbHeight + 4;
                            this->units[unitID].calculatedMovementSpeed = this->units[unitID].movementSpeed + 4;
                            this->units[unitID].movementRunUpTime = 8;
                        }
                    } else {
                        this->units[unitID].terrainOrClimbHeight = this->units[unitID].terrainOrClimbHeight + 4;
                        this->units[unitID].calculatedMovementSpeed = this->units[unitID].movementSpeed + 5;
                        this->units[unitID].movementRunUpTime = 0xc;
                    }
                } else {
                    this->units[unitID].terrainOrClimbHeight = _tileHeight;
                    this->units[unitID].calculatedMovementSpeed = this->units[unitID].movementSpeed;
                }
            } else if (_tileHeight < this->units[unitID].terrainOrClimbHeight) {
                int _heightDifference = this->units[unitID].terrainOrClimbHeight - _tileHeight;
                if (_heightDifference > 0x10) {
                    this->units[unitID].terrainOrClimbHeight = _tileHeight;
                    this->units[unitID].calculatedMovementSpeed = this->units[unitID].movementSpeed;
                } else if (_heightDifference < 0xc) {
                    if (_heightDifference < 8) {
                        if (_heightDifference > 3) {
                            this->units[unitID].terrainOrClimbHeight = this->units[unitID].terrainOrClimbHeight + -2;
                            this->units[unitID].calculatedMovementSpeed = this->units[unitID].movementSpeed;
                        } else {
                            this->units[unitID].terrainOrClimbHeight = this->units[unitID].terrainOrClimbHeight + -1;
                        }
                    } else {
                        this->units[unitID].terrainOrClimbHeight = this->units[unitID].terrainOrClimbHeight + -3;
                        this->units[unitID].calculatedMovementSpeed = this->units[unitID].movementSpeed;
                    }
                } else {
                    this->units[unitID].terrainOrClimbHeight = this->units[unitID].terrainOrClimbHeight + -4;
                    this->units[unitID].calculatedMovementSpeed = this->units[unitID].movementSpeed;
                }
            } else if (this->units[unitID].isSelectable_OR_matchTime == 0) {
                this->units[unitID].calculatedMovementSpeed = this->units[unitID].movementSpeed;
            } else {
                this->units[unitID].calculatedMovementSpeed = this->units[unitID].movementSpeed;
                if (this->units[unitID].tribeID > 0
                    && DAT_TribesState::instance.tribes[this->units[unitID].tribeID].unitType == (UnitType)0
                    && DAT_TribesState::instance.tribes[this->units[unitID].tribeID].freeUnitSpeeds == 0) {
                    this->units[unitID].calculatedMovementSpeed
                        = DAT_TribesState::instance.tribes[this->units[unitID].tribeID].movementSpeed;
                    if (this->units[unitID].calculatedMovementSpeed < this->units[unitID].movementSpeed) {
                        this->units[unitID].calculatedMovementSpeed = this->units[unitID].movementSpeed;
                    }
                    this->units[unitID].isMatchingSpeed = true;
                }
            }
            if (_isInMoat == 0) {
                if ((_logicFlags & 0x200000) != 0) {
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
            } else {
                if ((char)this->units[unitID].negativeHeight < 0x18) {
                    this->units[unitID].negativeHeight = this->units[unitID].negativeHeight + 4;
                }
                if ((char)this->units[unitID].negativeHeight <= 4) {
                    this->units[unitID].calculatedMovementSpeed = this->units[unitID].calculatedMovementSpeed + 3;
                } else if ((char)this->units[unitID].negativeHeight < 10) {
                    this->units[unitID].calculatedMovementSpeed = this->units[unitID].calculatedMovementSpeed + 4;
                } else {
                    this->units[unitID].calculatedMovementSpeed = this->units[unitID].calculatedMovementSpeed + 6;
                }
            }
            this->units[unitID].field289_0x3ff = 0;
            if ((_logicFlags & 8) != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TroopValueState_Func::registerSpottedEnemyTile,
                    DAT_TroopValueState::ptr)(_tile);
            }
            if (_buildingID == 0) {
                return;
            }
            if ((short)DAT_BuildingsState::instance.buildings[_buildingID].buildingType <= 0x28) {
                return;
            }
            if ((short)DAT_BuildingsState::instance.buildings[_buildingID].buildingType >= 0x2d) {
                return;
            }
            this->units[unitID].field289_0x3ff = 1;
            if (DAT_BuildingsState::instance.buildings[_buildingID].owner == this->units[unitID].owner) {
                return;
            }
            if (this->units[unitID].dying != 0) {
                return;
            }
            if (this->units[unitID].logicalState != OpenSHC::Map::Units::ULS_NORMAL) {
                return;
            }
            if (this->units[unitID].owner == 0) {
                return;
            }
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[this->units[unitID].owner] != -1) {
                return;
            }
            DAT_TroopValueState::instance.attackInfo.field128058_0x469dc
                = DAT_TroopValueState::instance.attackInfo.field128058_0x469dc + 1;
        }

    }
}
}
