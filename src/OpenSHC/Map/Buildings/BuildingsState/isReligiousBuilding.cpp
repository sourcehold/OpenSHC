#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingType.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040A4A0
        BOOLEnum BuildingsState::isReligiousBuilding(int buildingID)
        {
            if (this->buildings[buildingID].buildingType == BT_CHAPEL) {
                return TRUE;
            }
            if (this->buildings[buildingID].buildingType == BT_CHURCH) {
                return TRUE;
            }
            return this->buildings[buildingID].buildingType == BT_CATHEDRAL;
        }

    }
}
}
