#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingLogicalState;
        using OpenSHC::Map::Buildings::BuildingType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0040AA10
        int BuildingsState::countFarms(PlayerID playerID, int param_2)
        {
            int count = 0;
            for (int i = 1; i < this->maxBuildingsCount; ++i) {
                if (this->buildings[i].logicalState == BLS_NORMAL && this->buildings[i].owner == playerID
                    && (this->buildings[i].buildingType == BT_WHEATFARM
                        || this->buildings[i].buildingType == BT_APPLEFARM
                        || this->buildings[i].buildingType == BT_DAIRYFARM)
                    && (param_2 == 0 || this->buildings[i].field245_0x2c8 == 0)) {
                    ++count;
                }
            }
            return count;
        }

    }
}
}
