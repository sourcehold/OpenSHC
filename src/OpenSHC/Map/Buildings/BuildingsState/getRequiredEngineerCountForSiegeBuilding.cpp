#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x00410200
        undefined4 BuildingsState::getRequiredEngineerCountForSiegeBuilding(int buildingID)
        {
            if (buildingID == 0) {
                return 2;
            }
            switch (this->buildings[buildingID].buildingType) {
            case BT_FIREBALLISTA:
            case BT_CATAPULT:
                return 2;
            case BT_TREBUCHET:
                return 3;
            case BT_BATTERINGRAM:
            case BT_SIEGETOWER:
                return 4;
            case BT_SHIELD:
                return 1;
            default:
                return 0;
            }
        }

    }
}
}
