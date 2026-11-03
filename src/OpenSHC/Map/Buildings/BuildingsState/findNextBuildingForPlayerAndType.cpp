#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040AB30
        int BuildingsState::findNextBuildingForPlayerAndType(int playerID, BuildingType buildingType, int buildingID)
        {
            for (int nextID = buildingID + 1; nextID < this->maxBuildingsCount; ++nextID) {
                if (this->buildings[nextID].logicalState != 0 && this->buildings[nextID].logicalState != BLS_REMOVE
                    && this->buildings[nextID].owner == playerID
                    && this->buildings[nextID].buildingType == buildingType) {
                    return nextID;
                }
            }
            return 0;
        }

    }
}
}
