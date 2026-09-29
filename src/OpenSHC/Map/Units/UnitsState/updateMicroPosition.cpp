#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00534030
        void UnitsState::updateMicroPosition(int unitID)
        {
            uint _microPartX = (byte)this->units[unitID].microXPosition & 7;
            uint _microPartY = (byte)this->units[unitID].microYPosition & 7;
            switch (DAT_TileMapState::instance.mapOrientation) {
            case 0:
                _microPartX = _microPartX * 2;
                _microPartY = _microPartY << 4;
                break;
            case 2:
                _microPartX = (7 - _microPartX) * 16;
                _microPartY = _microPartY * 2;
                break;
                _microPartY = (7 - _microPartY) * 16;
            case 4:
                _microPartX = (7 - _microPartX) * 2;
                break;
            case 6:
                _microPartY = (7 - _microPartY) * 2;
                _microPartX = _microPartX << 4;
            }
            this->units[unitID].orientationRelatedPositionX
                = (short)DAT_UnitPropertiesDefinedData::instance.field77_0x10f4c[0][_microPartX + _microPartY];
            this->units[unitID].orientationRelatedPositionY
                = (short)DAT_UnitPropertiesDefinedData::instance.field77_0x10f4c[0][_microPartX + _microPartY + 1];
        }

    }
}
}
