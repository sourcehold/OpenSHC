#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00534520
        void UnitsState::writeSixToTileMap1104InAllDirections(int unitID, undefined4 six)
        {
            int _tile = this->units[unitID].tile;
            uchar* _tileMap1104 = DAT_TileMapState::instance.SEC_TileMap1104;
            int _y = this->units[unitID].y;
            uchar _value = (uchar)six;
            uchar* _row = _tileMap1104 + _tile;
            _row[1] = _value;
            _row[-1] = _value;
            _row[0] = _value;
            int* _directionRow
                = (int*)((uchar*)DAT_TileMapState::instance.ptr_MovementDirectionTranslationMatrix + _y * 0x20);
            uchar* _nextRow = _row + _directionRow[0];
            _nextRow[-1] = _value;
            _nextRow[1] = _value;
            _nextRow[0] = _value;
            _row = _row + _directionRow[4];
            _row[-1] = _value;
            _row[1] = _value;
            _row[0] = _value;
        }

    }
}
}
