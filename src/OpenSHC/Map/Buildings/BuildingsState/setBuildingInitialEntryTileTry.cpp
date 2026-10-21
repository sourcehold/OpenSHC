#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingType.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040B5D0
        void BuildingsState::setBuildingInitialEntryTileTry(int buildingID, undefined4 param_2)
        {
            uint const rowStride = this->buildings[buildingID].widthOrHeight + param_2 * 2;
            int entrySide;
            if (this->buildings[buildingID].buildingVariation == 15) {
                entrySide = 4;
                if (this->buildings[buildingID].buildingType == BT_TUNNEL
                    || this->buildings[buildingID].buildingType == BT_UNKNOWN4) {
                    entrySide = 2;
                }
                if (this->buildings[buildingID].buildingType == BT_OXTETHER) {
                    entrySide = 4;
                }
            } else {
                entrySide = this->buildings[buildingID].buildingVariation + 4;
            }
            if (entrySide >= 8) {
                entrySide -= 8;
            }
            this->buildings[buildingID].entranceAttemptTileIndex = entrySide / 2 * rowStride;
            if (this->buildings[buildingID].buildingType == BT_OXTETHER) {
                this->buildings[buildingID].entranceAttemptTileIndex = 9;
            }
        }

    }
}
}
