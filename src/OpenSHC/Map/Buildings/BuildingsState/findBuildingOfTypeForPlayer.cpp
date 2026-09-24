#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingLogicalState;

        // FUNCTION: STRONGHOLDCRUSADER 0x0040B4E0
        undefined4 BuildingsState::findBuildingOfTypeForPlayer(int playerID, BuildingType buildingType)
        {
            for (int i = 1; i < this->maxBuildingsCount; ++i) {
                if (this->buildings[i].logicalState != 0 && this->buildings[i].owner == playerID
                    && this->buildings[i].buildingType == buildingType) {
                    return 1;
                }
            }
            return 0;
        }

    }
}
}
