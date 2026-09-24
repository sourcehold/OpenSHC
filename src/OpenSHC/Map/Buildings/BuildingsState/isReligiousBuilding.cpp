#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0040A4A0
        BOOLEnum BuildingsState::isReligiousBuilding(int buildingID)
        {
            if (this->buildings[buildingID].buildingType == BT_CHAPEL
                || this->buildings[buildingID].buildingType == BT_CHURCH) {
                return TRUE;
            }
            return (BOOLEnum)(this->buildings[buildingID].buildingType == BT_CATHEDRAL);
        }

    }
}
}
