#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingLogicalState;

        // FUNCTION: STRONGHOLDCRUSADER 0x0040BEE0
        void BuildingsState::extendResourceCountdownForPlayerBuildingsOfType(
            BuildingType buildingType, int someCountdown, int playerID)
        {
            for (int i = 1; i < this->maxBuildingsCount; ++i) {
                if (this->buildings[i].logicalState == BLS_NORMAL && this->buildings[i].buildingType == buildingType
                    && this->buildings[i].owner == playerID
                    && this->buildings[i].resourceRelatedCountDown <= someCountdown) {
                    this->buildings[i].resourceRelatedCountDown = someCountdown;
                }
            }
        }

    }
}
}
