#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingLogicalState;

        // FUNCTION: STRONGHOLDCRUSADER 0x0040A9B0
        int BuildingsState::countBuildingsForPlayer(PlayerID playerID, BuildingType buildingType, int includeBool)
        {
            int count = 0;
            for (int i = 1; i < this->maxBuildingsCount; ++i) {
                if (this->buildings[i].logicalState == BLS_NORMAL && this->buildings[i].owner == playerID
                    && this->buildings[i].buildingType == buildingType
                    && (includeBool == 0 || this->buildings[i].field245_0x2c8 == 0)) {
                    ++count;
                }
            }
            return count;
        }

    }
}
}
