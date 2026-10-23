#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingLogicalState;
        using OpenSHC::Map::Buildings::BuildingType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0040F040
        void BuildingsState::setDairyFarmCheeseCounter(int param_1)
        {
            for (int i = 0; i < this->maxBuildingsCount; ++i) {
                if (this->buildings[i].logicalState != 0 && this->buildings[i].owner == param_1
                    && this->buildings[i].buildingType == BT_DAIRYFARM) {
                    this->buildings[i].flagonsOfAleOrCheeseOrReleaseDogs = 1600;
                }
            }
        }

    }
}
}
