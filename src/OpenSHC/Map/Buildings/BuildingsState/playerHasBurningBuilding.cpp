#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingLogicalState;

        // FUNCTION: STRONGHOLDCRUSADER 0x00410C40
        undefined4 BuildingsState::playerHasBurningBuilding(int playerID)
        {
            for (int i = 1; i < this->maxBuildingsCount; ++i) {
                if (this->buildings[i].fireDuration != 0 && this->buildings[i].owner == playerID
                    && this->buildings[i].logicalState != 0 && this->buildings[i].logicalState != BLS_REMOVE) {
                    return 1;
                }
            }
            return 0;
        }

    }
}
}
