#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00534490
        void UnitsState::stampOccupancyFlagOnSurroundingTiles(int unitID)
        {
            int _tile = this->units[unitID].tile;
            uchar* _occupancy = DAT_TileMapState::instance.OccupancyLayer;
            int _y = this->units[unitID].y;
            uchar _value = this->units[unitID].occupancyOrFlag;
            uchar* _row = _occupancy + _tile;
            _row[1] |= _value;
            _row[-1] |= _value;
            _row[0] |= _value;
            int* _directionRow
                = (int*)((uchar*)DAT_TileMapState::instance.ptr_MovementDirectionTranslationMatrix + _y * 0x20);
            uchar* _nextRow = _row + _directionRow[0];
            _nextRow[-1] |= _value;
            _nextRow[1] |= _value;
            _nextRow[0] |= _value;
            uchar* _furtherRow = _row + _directionRow[4];
            _furtherRow[-1] |= _value;
            _furtherRow[1] |= _value;
            _furtherRow[0] |= _value;
        }

    }
}
}
