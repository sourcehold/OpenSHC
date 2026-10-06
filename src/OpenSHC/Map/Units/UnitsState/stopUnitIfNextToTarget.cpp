#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00534240
        int UnitsState::stopUnitIfNextToTarget(int unitID)
        {
            uint _targetTile = this->units[unitID].targetedBuildingTile;
            int _isNear = 0;
            if (_targetTile == 0) {
                return 0;
            }
            if (this->units[unitID].field64_0x90 == 0) {
                return 0;
            }
            int _unitTile = this->units[unitID].tile;
            uint _tile;
            bool _isAdjacent = false;
            for (int direction = 0; direction < 8; ++direction) {
                _tile = DAT_TileMapState::instance.directionTranslationMatrix[this->units[unitID].y][direction]
                    + _unitTile;
                if (_tile == _targetTile) {
                    _isAdjacent = true;
                    break;
                }
            }
            if (!_isAdjacent) {
                /* The original does not leave this loop once it has found the target two tiles away, so the tile
                   tested below is always the one in the last direction. */
                int _y = this->units[unitID].y;
                for (int direction = 0; direction < 8; ++direction) {
                    _tile = DAT_TileMapState::instance.directionTranslationMatrix[_y][direction] + _unitTile;
                    for (int secondDirection = 0; secondDirection < 8; ++secondDirection) {
                        if (DAT_TileMapState::instance
                                    .directionTranslationMatrix[DAT_TerrainDefinedData::instance
                                                                    .clockwiseCardinalTranslationMatrix[direction]
                                                                    .int_.yOffset
                                        + _y][secondDirection]
                                + _tile
                            == _targetTile) {
                            _isNear = 1;
                            break;
                        }
                    }
                }
                if (_isNear == 0) {
                    return 0;
                }
            }
            if ((DAT_TileMapState::instance.LogicLayer[_tile] & 0x100U) != 0
                || DAT_TileMapState::instance.BuildingLayer[_tile] != 0) {
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::makeUnitStopWalkingByClearingPathProgressState, this)(unitID);
                return this->units[unitID].movementRelated >= 8;
            }
            return -1;
        }

    }
}
}
