#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00534240
        int UnitsState::stopUnitIfNextToTarget(int unitID)
        {
            if (this->units[unitID].targetedBuildingTile == 0) {
                return 0;
            }
            if (this->units[unitID].field64_0x90 == 0) {
                return 0;
            }
            uint _tile = 0;
            bool _isNear = false;
            for (int direction = 0; direction < 8; ++direction) {
                _tile = DAT_TileMapState::instance.directionTranslationMatrix[this->units[unitID].y][direction]
                    + this->units[unitID].tile;
                if (_tile == this->units[unitID].targetedBuildingTile) {
                    _isNear = true;
                    break;
                }
            }
            if (!_isNear) {
                for (int direction = 0; direction < 8 && !_isNear; ++direction) {
                    uint _neighbourTile
                        = DAT_TileMapState::instance.directionTranslationMatrix[this->units[unitID].y][direction]
                        + this->units[unitID].tile;
                    for (int secondDirection = 0; secondDirection < 8; ++secondDirection) {
                        if (DAT_TileMapState::instance.directionTranslationMatrix[this->units[unitID].y
                                + DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[direction]
                                    .int_.yOffset][secondDirection]
                                + _neighbourTile
                            == this->units[unitID].targetedBuildingTile) {
                            _tile = _neighbourTile;
                            _isNear = true;
                            break;
                        }
                    }
                }
            }
            if (!_isNear) {
                return 0;
            }
            if ((DAT_TileMapState::instance.LogicLayer[_tile] & 0x100U) == 0
                && DAT_TileMapState::instance.BuildingLayer[_tile] == 0) {
                return -1;
            }
            MACRO_CALL_MEMBER(
                OpenSHC::Map::Units::UnitsState_Func::makeUnitStopWalkingByClearingPathProgressState, this)(unitID);
            return (uint)(this->units[unitID].movementRelated > 7);
        }

    }
}
}
