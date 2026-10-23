#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingLogicalState;

        // FUNCTION: STRONGHOLDCRUSADER 0x0040AA80
        int BuildingsState::findFirstBuildingOfType(int playerID, BuildingType buildingType)
        {
            for (int i = 1; i < this->maxBuildingsCount; ++i) {
                if (this->buildings[i].logicalState == BLS_NORMAL && this->buildings[i].owner == playerID
                    && this->buildings[i].buildingType == buildingType) {
                    return i;
                }
            }
            return 0;
        }

    }
}
}
