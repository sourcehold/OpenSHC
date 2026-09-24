#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingLogicalState;

        // FUNCTION: STRONGHOLDCRUSADER 0x0040A950
        int BuildingsState::getEmptyBuildingCount(int playerID, BuildingType buildingType)
        {
            int count = 0;
            for (int i = 1; i < this->maxBuildingsCount; ++i) {
                if (this->buildings[i].logicalState == BLS_NORMAL && this->buildings[i].owner == playerID
                    && this->buildings[i].buildingType == buildingType
                    && this->buildings[i].currentNumberOfResource <= 0) {
                    ++count;
                }
            }
            return count;
        }

    }
}
}
