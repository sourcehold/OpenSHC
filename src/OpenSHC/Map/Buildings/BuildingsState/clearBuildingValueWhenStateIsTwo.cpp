#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040F3F0
        void BuildingsState::clearBuildingValueWhenStateIsTwo()
        {
            for (int buildingID = 1; buildingID < this->maxBuildingsCount; ++buildingID) {
                if (this->buildings[buildingID].logicalState == BLS_NORMAL) {
                    this->buildings[buildingID].animStateCounterTracker = 0;
                }
            }
        }

    }
}
}
