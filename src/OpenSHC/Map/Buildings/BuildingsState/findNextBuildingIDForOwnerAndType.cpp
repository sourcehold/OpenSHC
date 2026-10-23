#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingLogicalState;

        // FUNCTION: STRONGHOLDCRUSADER 0x0040AB90
        int BuildingsState::findNextBuildingIDForOwnerAndType(int param_1, int param_2, int param_3)
        {
            for (int i = 0; i < this->maxBuildingsCount; ++i) {
                ++param_3;
                if (param_3 >= this->maxBuildingsCount) {
                    param_3 = 1;
                }
                if (this->buildings[param_3].logicalState != 0 && this->buildings[param_3].logicalState != BLS_REMOVE
                    && this->buildings[param_3].owner == param_1 && this->buildings[param_3].buildingType == param_2) {
                    return param_3;
                }
            }
            return 0;
        }

    }
}
}
