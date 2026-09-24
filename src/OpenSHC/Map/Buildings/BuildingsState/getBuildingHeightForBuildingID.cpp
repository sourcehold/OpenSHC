#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x00409DB0
        undefined4 BuildingsState::getBuildingHeightForBuildingID(int buildingID)
        {
            switch (this->buildings[buildingID].buildingType) {
            case BT_MANORHOUSE:
                return 64;
            case BT_STONEKEEP:
                return 92;
            case BT_STRONGHOLD:
                return 190;
            case BT_GATEHOUSELARGE:
            case BT_GATEHOUSESMALL:
                return 128;
            case BT_SIEGETOWER_PLACED:
                return 118;
            case BT_TOWER1:
                return 296;
            case BT_TOWER2:
                return 148;
            case BT_TOWER3:
                return 180;
            case BT_TOWER4:
            case BT_TOWER5:
                return 192;
            default:
                return 0;
            }
        }

    }
}
}
