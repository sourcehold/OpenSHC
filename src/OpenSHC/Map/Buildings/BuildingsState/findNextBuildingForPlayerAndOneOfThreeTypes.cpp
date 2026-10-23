#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingLogicalState;

        // FUNCTION: STRONGHOLDCRUSADER 0x0040AC00
        int BuildingsState::findNextBuildingForPlayerAndOneOfThreeTypes(
            int param_1, int param_2, int param_3, int param_4, int param_5)
        {
            for (int i = 0; i < this->maxBuildingsCount; ++i) {
                ++param_5;
                if (param_5 >= this->maxBuildingsCount) {
                    param_5 = 1;
                }
                if (this->buildings[param_5].logicalState == 0 || this->buildings[param_5].logicalState == BLS_REMOVE
                    || this->buildings[param_5].owner != param_1) {
                    continue;
                }
                if (this->buildings[param_5].buildingType == param_2) {
                    return param_5;
                }
                if (this->buildings[param_5].buildingType == param_3) {
                    return param_5;
                }
                if (this->buildings[param_5].buildingType == param_4) {
                    return param_5;
                }
            }
            return 0;
        }

    }
}
}
