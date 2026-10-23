#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040CB10
        int BuildingsState::getFarmThatHasTile(int tile)
        {
            for (int buildingID = 1; buildingID < this->maxBuildingsCount; ++buildingID) {
                if (this->buildings[buildingID].logicalState == BLS_NORMAL
                    && (this->buildings[buildingID].buildingType == BT_WHEATFARM
                        || this->buildings[buildingID].buildingType == BT_HOPFARM
                        || this->buildings[buildingID].buildingType == BT_APPLEFARM
                        || this->buildings[buildingID].buildingType == BT_DAIRYFARM)) {
                    for (int tileIndex = 0; tileIndex < 36; ++tileIndex) {
                        if (this->buildings[buildingID].tileRefs[tileIndex] == tile) {
                            return buildingID;
                        }
                    }
                }
            }
            return 0;
        }

    }
}
}
