#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0040B5D0
        void BuildingsState::setBuildingInitialEntryTileTry(int buildingID, undefined4 param_2)
        {
            int direction;
            if (this->buildings[buildingID].buildingVariation == 15) {
                direction = 4;
                if (this->buildings[buildingID].buildingType == BT_TUNNEL
                    || this->buildings[buildingID].buildingType == BT_UNKNOWN4) {
                    direction = 2;
                }
                if (this->buildings[buildingID].buildingType == BT_OXTETHER) {
                    direction = 4;
                }
            } else {
                direction = this->buildings[buildingID].buildingVariation + 4;
                if (direction > 7) {
                    direction -= 8;
                }
            }
            this->buildings[buildingID].entranceAttemptTileIndex
                = (short)(direction / 2) * ((short)this->buildings[buildingID].widthOrHeight + (short)param_2 * 2);
            if (this->buildings[buildingID].buildingType == BT_OXTETHER) {
                this->buildings[buildingID].entranceAttemptTileIndex = 9;
            }
        }

    }
}
}
