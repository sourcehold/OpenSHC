#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040BEE0
        void BuildingsState::extendResourceCountdownForPlayerBuildingsOfType(
            BuildingType buildingType, int someCountdown, int playerID)
        {
            for (int buildingID = 1; buildingID < this->maxBuildingsCount; ++buildingID) {
                if (this->buildings[buildingID].logicalState == BLS_NORMAL
                    && this->buildings[buildingID].buildingType == buildingType
                    && this->buildings[buildingID].owner == playerID
                    && this->buildings[buildingID].resourceRelatedCountDown <= someCountdown) {
                    this->buildings[buildingID].resourceRelatedCountDown = someCountdown;
                }
            }
        }

    }
}
}
