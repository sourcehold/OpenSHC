#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040AA10
        int BuildingsState::countFarms(int playerID, int param_2)
        {
            int count = 0;
            for (int buildingID = 1; buildingID < this->maxBuildingsCount; ++buildingID) {
                if (this->buildings[buildingID].logicalState == BLS_NORMAL
                    && this->buildings[buildingID].owner == playerID
                    && (this->buildings[buildingID].buildingType == BT_WHEATFARM
                        || this->buildings[buildingID].buildingType == BT_APPLEFARM
                        || this->buildings[buildingID].buildingType == BT_DAIRYFARM)
                    && (param_2 == 0 || this->buildings[buildingID].field202_0x2c8 == 0)) {
                    ++count;
                }
            }
            return count;
        }

    }
}
}
