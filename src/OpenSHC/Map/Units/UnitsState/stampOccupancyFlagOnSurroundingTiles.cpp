#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00534490
        void UnitsState::stampOccupancyFlagOnSurroundingTiles(int unitID)
        {
            uchar* _occupancy = DAT_TileMapState::instance.OccupancyLayer;
            int _tile = this->units[unitID].tile;
            int _y = this->units[unitID].y;
            uchar _flag = this->units[unitID].occupancyOrFlag;
            uchar* _ownRow = _occupancy + _tile;
            _ownRow[1] |= _flag;
            _ownRow[-1] |= _flag;
            _ownRow[0] |= _flag;
            int* _directionRow
                = (int*)((uchar*)DAT_TileMapState::instance.ptr_MovementDirectionTranslationMatrix + _y * 0x20);
            uchar* _nextRow = _ownRow + _directionRow[0];
            _nextRow[-1] |= _flag;
            _nextRow[1] |= _flag;
            _nextRow[0] |= _flag;
            uchar* _furtherRow = _ownRow + _directionRow[4];
            _furtherRow[-1] |= _flag;
            _furtherRow[1] |= _flag;
            _furtherRow[0] |= _flag;
        }

    }
}
}
