#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingLogicalState;

        // FUNCTION: STRONGHOLDCRUSADER 0x0040F3F0
        void BuildingsState::clearBuildingValueWhenStateIsTwo()
        {
            for (int i = 1; i < this->maxBuildingsCount; ++i) {
                if (this->buildings[i].logicalState == BLS_NORMAL) {
                    this->buildings[i].animStateCounterTracker = 0;
                }
            }
        }

    }
}
}
