#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x00410C40
        undefined4 BuildingsState::playerHasBurningBuilding(int playerID)
        {
            for (int buildingID = 1; buildingID < this->maxBuildingsCount; ++buildingID) {
                if (this->buildings[buildingID].fireDuration != 0 && this->buildings[buildingID].owner == playerID
                    && this->buildings[buildingID].logicalState != 0
                    && this->buildings[buildingID].logicalState != BLS_REMOVE) {
                    return 1;
                }
            }
            return 0;
        }

    }
}
}
