#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00534520
        void UnitsState::writeSixToTileMap1104InAllDirections(int unitID, undefined4 six)
        {
            uchar* _tileTypes = DAT_TileMapState::instance.SEC_TileMap1104;
            int _tile = this->units[unitID].tile;
            int _y = this->units[unitID].y;
            uchar* _ownRow = _tileTypes + _tile;
            _ownRow[1] = (uchar)six;
            _ownRow[-1] = (uchar)six;
            _ownRow[0] = (uchar)six;
            int* _directionRow
                = (int*)((uchar*)DAT_TileMapState::instance.ptr_MovementDirectionTranslationMatrix + _y * 0x20);
            uchar* _nextRow = _ownRow + _directionRow[0];
            _nextRow[-1] = (uchar)six;
            _nextRow[1] = (uchar)six;
            _nextRow[0] = (uchar)six;
            uchar* _furtherRow = _ownRow + _directionRow[4];
            _furtherRow[-1] = (uchar)six;
            _furtherRow[1] = (uchar)six;
            _furtherRow[0] = (uchar)six;
        }

    }
}
}
