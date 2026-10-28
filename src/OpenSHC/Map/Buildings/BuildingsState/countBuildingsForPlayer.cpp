#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040A9B0
        int BuildingsState::countBuildingsForPlayer(int playerID, BuildingType buildingType, int includeBool)
        {
            int count = 0;
            for (int buildingID = 1; buildingID < this->maxBuildingsCount; ++buildingID) {
                if (this->buildings[buildingID].logicalState == BLS_NORMAL
                    && this->buildings[buildingID].owner == playerID
                    && this->buildings[buildingID].buildingType == buildingType
                    && (includeBool == 0 || this->buildings[buildingID].field201_0x2c8 == 0)) {
                    ++count;
                }
            }
            return count;
        }

    }
}
}
