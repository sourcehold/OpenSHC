#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingLogicalState;

        // FUNCTION: STRONGHOLDCRUSADER 0x0040AB30
        int BuildingsState::findNextBuildingForPlayerAndType(
            PlayerID playerID, BuildingType buildingType, int buildingID)
        {
            for (int i = buildingID + 1; i < this->maxBuildingsCount; ++i) {
                if (this->buildings[i].logicalState != 0 && this->buildings[i].logicalState != BLS_REMOVE
                    && this->buildings[i].owner == playerID && this->buildings[i].buildingType == buildingType) {
                    return i;
                }
            }
            return 0;
        }

    }
}
}
