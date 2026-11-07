#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040B4E0
        BOOLEnum BuildingsState::findBuildingOfTypeForPlayer(int playerID, BuildingType buildingType)
        {
            for (int buildingID = 1; buildingID < this->maxBuildingsCount; ++buildingID) {
                if (this->buildings[buildingID].logicalState != 0 && this->buildings[buildingID].owner == playerID
                    && this->buildings[buildingID].buildingType == buildingType) {
                    return TRUE;
                }
            }
            return FALSE;
        }

    }
}
}
