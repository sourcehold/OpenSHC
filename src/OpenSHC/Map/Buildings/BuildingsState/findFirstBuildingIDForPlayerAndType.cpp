#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040AAD0
        int BuildingsState::findFirstBuildingIDForPlayerAndType(int playerID, BuildingType buildingType)
        {
            for (int buildingID = 1; buildingID < this->maxBuildingsCount; ++buildingID) {
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
