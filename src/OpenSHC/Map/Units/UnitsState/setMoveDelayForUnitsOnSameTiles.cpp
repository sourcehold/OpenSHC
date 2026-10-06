#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0052F260
        void UnitsState::setMoveDelayForUnitsOnSameTiles(int unitID, int unitIDCurrentTilePosition)
        {
            short _unitIDArray[2010];
            int _lowestMovementSpeed = 0x14;
            this->units[unitID].unitOrderWhenOnSameTile = 0;
            if (this->units[unitID].unknownTestAgainst0_2 != 0) {
                return;
            }
            this->units[unitID].field40_0x5a = 0;
            /* if current tile position is not occupied */
            if (DAT_TileMapState::instance.UnitLayer[unitIDCurrentTilePosition] == 0) {
                DAT_TileMapState::instance.UnitLayer[unitIDCurrentTilePosition] = (ushort)unitID;
                this->units[unitID].nextUnitOnTheSameTile = 0;
                return;
            }
            /* if current tile position is occupied */
            int _isInserted = 0;
            int _unitIDOfAUnitOnSameTile = (short)DAT_TileMapState::instance.UnitLayer[unitIDCurrentTilePosition];
            int _index = 0;
            do {
                if (unitID < _unitIDOfAUnitOnSameTile && _isInserted == 0) {
                    _unitIDArray[_index] = (short)unitID;
                    _index++;
                    _isInserted = 1;
                }
                _unitIDArray[_index] = (short)_unitIDOfAUnitOnSameTile;
                _unitIDOfAUnitOnSameTile = (short)this->units[_unitIDOfAUnitOnSameTile].nextUnitOnTheSameTile;
                if (_unitIDOfAUnitOnSameTile <= 0) {
                    break;
                }
                _index++;
            } while (_index < 2000);
            _index++;
            if (_isInserted == 0) {
                _unitIDArray[_index] = (short)unitID;
                _index++;
            }
            _unitIDArray[_index] = 0;
            int _previousUnitID = _unitIDArray[0];
            DAT_TileMapState::instance.UnitLayer[unitIDCurrentTilePosition] = (ushort)_previousUnitID;
            this->units[_previousUnitID].unitOrderWhenOnSameTile = 0;
            for (int _order = 1; _order < 2001; ++_order) {
                int _nextUnitID = _unitIDArray[_order];
                this->units[_previousUnitID].nextUnitOnTheSameTile = (short)_nextUnitID;
                _previousUnitID = _nextUnitID;
                if (_nextUnitID <= 0) {
                    break;
                }
                this->units[_nextUnitID].unitOrderWhenOnSameTile = (short)_order;
            }
            int _speedIndex = 0;
            do {
                int _sameTileUnitID = _unitIDArray[_speedIndex];
                if (_sameTileUnitID <= 0) {
                    break;
                }
                if (this->units[_sameTileUnitID].tunnelerFinishedDigging == 2
                    && this->units[_sameTileUnitID].movementSpeed < _lowestMovementSpeed) {
                    _lowestMovementSpeed = this->units[_sameTileUnitID].movementSpeed;
                }
                _speedIndex++;
            } while (_speedIndex < 2000);
            int _delayIndex = 0;
            do {
                int _sameTileUnitID = _unitIDArray[_delayIndex];
                if (_sameTileUnitID <= 0) {
                    break;
                }
                if (this->units[_sameTileUnitID].tunnelerFinishedDigging == 2
                    && this->units[_sameTileUnitID].moveDelay == 0) {
                    if (this->units[_sameTileUnitID].movementSpeed > _lowestMovementSpeed) {
                        this->units[_sameTileUnitID].moveDelay
                            = this->units[_sameTileUnitID].unitOrderWhenOnSameTile / 2 + 1;
                    } else {
                        _lowestMovementSpeed = 0;
                    }
                }
                _delayIndex++;
            } while (_delayIndex < 2000);
        }

    }
}
}
