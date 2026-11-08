#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040A950
        int BuildingsState::getEmptyBuildingCount(int playerID, BuildingType buildingType)
        {
            int count = 0;
            for (int buildingID = 1; buildingID < this->maxBuildingsCount; ++buildingID) {
                if (this->buildings[buildingID].logicalState == BLS_NORMAL
                    && this->buildings[buildingID].owner == playerID
                    && this->buildings[buildingID].buildingType == buildingType
                    && this->buildings[buildingID].currentNumberOfResource <= 0) {
                    ++count;
                }
            }
            return count;
        }

    }
}
}
