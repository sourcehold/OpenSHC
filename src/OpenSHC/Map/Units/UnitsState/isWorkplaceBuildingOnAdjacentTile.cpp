#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00534380
        undefined4 UnitsState::isWorkplaceBuildingOnAdjacentTile(int unitID)
        {
            if (this->units[unitID].workplaceBuildingID_1 == 0) {
                return 0;
            }
            for (int direction = 0; direction < 8; ++direction) {
                if (DAT_TileMapState::instance.BuildingLayer
                        [DAT_TileMapState::instance.directionTranslationMatrix[this->units[unitID].y][direction]
                            + this->units[unitID].tile]
                    == this->units[unitID].workplaceBuildingID_1) {
                    return 1;
                }
            }
            return 0;
        }

    }
}
}
