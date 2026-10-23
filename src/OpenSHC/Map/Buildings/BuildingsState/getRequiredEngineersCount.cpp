#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00418EC0
        int BuildingsState::getRequiredEngineersCount(int buildingID)
        {
            if (this->buildings[buildingID].buildingType == BT_TREBUCHET) {
                return 3 - this->buildings[buildingID].currentEmployeeCount;
            }
            if (this->buildings[buildingID].buildingType == BT_CATAPULT) {
                return 2 - this->buildings[buildingID].currentEmployeeCount;
            }
            if (this->buildings[buildingID].buildingType == BT_FIREBALLISTA) {
                return 2 - this->buildings[buildingID].currentEmployeeCount;
            }
            if (this->buildings[buildingID].buildingType == BT_BATTERINGRAM) {
                return 4 - this->buildings[buildingID].currentEmployeeCount;
            }
            if (this->buildings[buildingID].buildingType == BT_SIEGETOWER) {
                return 4 - this->buildings[buildingID].currentEmployeeCount;
            }
            if (this->buildings[buildingID].buildingType == BT_SHIELD) {
                return 1 - this->buildings[buildingID].currentEmployeeCount;
            }
            return 0;
        }

    }
}
}
