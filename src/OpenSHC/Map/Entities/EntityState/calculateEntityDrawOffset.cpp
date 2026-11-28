#include "../../../Map.func.hpp"
#include "../EntityState.func.hpp"

#include "OpenSHC/Globals/DAT_EntityDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x004036F0
        void EntityState::calculateEntityDrawOffset(int entityID)
        {
            uint _microYPart;
            int _yOffset;
            uint _microXPart;
            int _xOffset;
            _microXPart = (byte)this->entityArray[entityID].microX & 7;
            _microYPart = (byte)this->entityArray[entityID].microY & 7;
            if (DAT_TileMapState::instance.mapOrientation == 4) {
                _microXPart = 7 - _microXPart;
                _microYPart = 7 - _microYPart;
            } else {
                if (DAT_TileMapState::instance.mapOrientation == 2) {
                    _xOffset = (7 - _microXPart) * 0x10;
                    _yOffset = _microYPart * 2;
                    goto LAB_0040372e;
                }
                if (DAT_TileMapState::instance.mapOrientation == 6) {
                    _xOffset = _microXPart << 4;
                    _yOffset = (7 - _microYPart) * 2;
                    goto LAB_0040372e;
                }
                if (DAT_TileMapState::instance.mapOrientation) {
                    _xOffset = _microXPart << 4;
                    _yOffset = _microYPart * 2;
                    goto LAB_0040372e;
                }
            }
            _xOffset = _microXPart * 2;
            _yOffset = _microYPart << 4;
        LAB_0040372e:
            this->entityArray[entityID].x1 = DAT_EntityDefinedData::instance.EntitySubTileDrawOffsets[_yOffset + _xOffset].x;
            this->entityArray[entityID].y1 = DAT_EntityDefinedData::instance.EntitySubTileDrawOffsets[_yOffset + _xOffset + 1].x;
        }

    }
}
}
