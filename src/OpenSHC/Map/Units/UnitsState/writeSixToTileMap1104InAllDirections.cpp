#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00534520
        void UnitsState::writeSixToTileMap1104InAllDirections(int unitID, undefined4 six)
        {
            DAT_TileMapState::instance.SEC_TileMap1104[this->units[unitID].tile + 1] = (uchar)six;
            DAT_TileMapState::instance.SEC_TileMap1104[this->units[unitID].tile - 1] = (uchar)six;
            DAT_TileMapState::instance.SEC_TileMap1104[this->units[unitID].tile] = (uchar)six;
            for (int row = 0; row < 8; row += 4) {
                int _rowOffset = ((int*)DAT_TileMapState::instance
                        .ptr_MovementDirectionTranslationMatrix)[this->units[unitID].y * 8 + row];
                DAT_TileMapState::instance.SEC_TileMap1104[this->units[unitID].tile + _rowOffset - 1] = (uchar)six;
                DAT_TileMapState::instance.SEC_TileMap1104[this->units[unitID].tile + _rowOffset + 1] = (uchar)six;
                DAT_TileMapState::instance.SEC_TileMap1104[this->units[unitID].tile + _rowOffset] = (uchar)six;
            }
        }

    }
}
}
