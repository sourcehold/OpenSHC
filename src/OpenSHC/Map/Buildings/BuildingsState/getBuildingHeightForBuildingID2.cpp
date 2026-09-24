#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x00409E80
        undefined4 BuildingsState::getBuildingHeightForBuildingID2(int buildingID)
        {
            if (this->buildings[buildingID].field62_0xb0 == 0) {
                return 0;
            }
            switch (this->buildings[buildingID].buildingType) {
            case BT_MANORHOUSE:
                return 56;
            case BT_STONEKEEP:
                return 74;
            case BT_STRONGHOLD:
                return 145;
            case BT_TOWER1:
                return 276;
            case BT_TOWER2:
                return 128;
            case BT_TOWER3:
                return 150;
            case BT_TOWER4:
            case BT_TOWER5:
                return 172;
            case BT_GATEHOUSELARGE:
            case BT_GATEHOUSESMALL:
                return 108;
            }
            return 0;
        }

    }
}
}
