#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingLogicalState;
        using OpenSHC::Map::Buildings::BuildingType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0040CB10
        int BuildingsState::getFarmThatHasTile(int tile)
        {
            for (int i = 1; i < this->maxBuildingsCount; ++i) {
                if (this->buildings[i].logicalState != BLS_NORMAL
                    || (this->buildings[i].buildingType != BT_WHEATFARM && this->buildings[i].buildingType != BT_HOPFARM
                        && this->buildings[i].buildingType != BT_APPLEFARM
                        && this->buildings[i].buildingType != BT_DAIRYFARM)) {
                    continue;
                }
                for (int t = 0; t < 36; ++t) {
                    if ((&this->buildings[i].tileRef1)[t] == tile) {
                        return i;
                    }
                }
            }
            return 0;
        }

    }
}
}
