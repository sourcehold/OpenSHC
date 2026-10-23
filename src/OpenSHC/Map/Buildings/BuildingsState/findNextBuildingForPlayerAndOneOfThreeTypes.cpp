#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040AC00
        int BuildingsState::findNextBuildingForPlayerAndOneOfThreeTypes(
            int playerID, int buildingType1, int buildingType2, int buildingType3, int buildingID)
        {
            for (int i = 0; i < this->maxBuildingsCount; ++i) {
                ++buildingID;
                if (buildingID >= this->maxBuildingsCount) {
                    buildingID = 1;
                }
                if (this->buildings[buildingID].logicalState != 0
                    && this->buildings[buildingID].logicalState != BLS_REMOVE
                    && this->buildings[buildingID].owner == playerID
                    && (this->buildings[buildingID].buildingType == buildingType1
                        || this->buildings[buildingID].buildingType == buildingType2
                        || this->buildings[buildingID].buildingType == buildingType3)) {
                    return buildingID;
                }
            }
            return 0;
        }

    }
}
}
