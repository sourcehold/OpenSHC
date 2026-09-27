#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00534490
        void UnitsState::stampOccupancyFlagOnSurroundingTiles(int unitID)
        {
            DAT_TileMapState::instance.OccupancyLayer[this->units[unitID].tile + 1]
                |= this->units[unitID].occupancyOrFlag;
            DAT_TileMapState::instance.OccupancyLayer[this->units[unitID].tile - 1]
                |= this->units[unitID].occupancyOrFlag;
            DAT_TileMapState::instance.OccupancyLayer[this->units[unitID].tile] |= this->units[unitID].occupancyOrFlag;
            for (int row = 0; row < 8; row += 4) {
                int _rowOffset = ((int*)DAT_TileMapState::instance
                        .ptr_MovementDirectionTranslationMatrix)[this->units[unitID].y * 8 + row];
                DAT_TileMapState::instance.OccupancyLayer[this->units[unitID].tile + _rowOffset - 1]
                    |= this->units[unitID].occupancyOrFlag;
                DAT_TileMapState::instance.OccupancyLayer[this->units[unitID].tile + _rowOffset + 1]
                    |= this->units[unitID].occupancyOrFlag;
                DAT_TileMapState::instance.OccupancyLayer[this->units[unitID].tile + _rowOffset]
                    |= this->units[unitID].occupancyOrFlag;
            }
        }

    }
}
}
