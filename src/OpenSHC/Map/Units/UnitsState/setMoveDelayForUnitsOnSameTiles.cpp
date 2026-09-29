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
            bool _isInserted = false;
            int _unitIDOfAUnitOnSameTile = (short)DAT_TileMapState::instance.UnitLayer[unitIDCurrentTilePosition];
            int _index = 0;
            int _writeIndex = 0;
            while (true) {
                _writeIndex = _index;
                if (unitID < _unitIDOfAUnitOnSameTile && !_isInserted) {
                    _unitIDArray[_index] = (short)unitID;
                    _writeIndex = _index + 1;
                    _isInserted = true;
                }
                _unitIDArray[_writeIndex] = (short)_unitIDOfAUnitOnSameTile;
                _unitIDOfAUnitOnSameTile = (short)this->units[_unitIDOfAUnitOnSameTile].nextUnitOnTheSameTile;
                if (_unitIDOfAUnitOnSameTile < 1) {
                    break;
                }
                _index = _writeIndex + 1;
                _writeIndex = _index;
                if (_index >= 2000) {
                    break;
                }
            }
            _writeIndex = _writeIndex + 1;
            if (!_isInserted) {
                _unitIDArray[_writeIndex] = (short)unitID;
                _writeIndex = _writeIndex + 2;
            }
            _unitIDArray[_writeIndex] = 0;
            DAT_TileMapState::instance.UnitLayer[unitIDCurrentTilePosition] = (ushort)_unitIDArray[0];
            this->units[_unitIDArray[0]].unitOrderWhenOnSameTile = 0;
            int _previousUnitID = _unitIDArray[0];
            for (int _order = 1; _order < 2001; ++_order) {
                this->units[_previousUnitID].nextUnitOnTheSameTile = _unitIDArray[_order];
                if (_unitIDArray[_order] < 1) {
                    break;
                }
                this->units[_unitIDArray[_order]].unitOrderWhenOnSameTile = (short)_order;
                _previousUnitID = _unitIDArray[_order];
            }
            for (int i = 0; i < 2000; ++i) {
                if (_unitIDArray[i] < 1) {
                    break;
                }
                if (this->units[_unitIDArray[i]].tunnelerFinishedDigging == 2
                    && this->units[_unitIDArray[i]].movementSpeed < _lowestMovementSpeed) {
                    _lowestMovementSpeed = this->units[_unitIDArray[i]].movementSpeed;
                }
            }
            for (int i = 0; i < 2000; ++i) {
                if (_unitIDArray[i] < 1) {
                    break;
                }
                if (this->units[_unitIDArray[i]].tunnelerFinishedDigging == 2
                    && this->units[_unitIDArray[i]].moveDelay == 0) {
                    if (_lowestMovementSpeed < this->units[_unitIDArray[i]].movementSpeed) {
                        this->units[_unitIDArray[i]].moveDelay
                            = this->units[_unitIDArray[i]].unitOrderWhenOnSameTile / 2 + 1;
                    } else {
                        _lowestMovementSpeed = 0;
                    }
                }
            }
        }

    }
}
}
