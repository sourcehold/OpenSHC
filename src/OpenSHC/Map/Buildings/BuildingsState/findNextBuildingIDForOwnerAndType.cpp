#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040AB90
        int BuildingsState::findNextBuildingIDForOwnerAndType(int playerID, int buildingType, int buildingID)
        {
            for (int i = 0; i < this->maxBuildingsCount; ++i) {
                ++buildingID;
                if (buildingID >= this->maxBuildingsCount) {
                    buildingID = 1;
                }
                if (this->buildings[buildingID].logicalState != 0
                    && this->buildings[buildingID].logicalState != BLS_REMOVE
                    && this->buildings[buildingID].owner == playerID
                    && this->buildings[buildingID].buildingType == buildingType) {
                    return buildingID;
                }
            }
            return 0;
        }

    }
}
}
