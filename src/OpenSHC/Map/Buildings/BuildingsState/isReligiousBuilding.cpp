#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeShort.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingType;
        using OpenSHC::Map::Buildings::BuildingTypeShort;

        // FUNCTION: STRONGHOLDCRUSADER 0x0040A4A0
        uint BuildingsState::isReligiousBuilding(int buildingID)
        {
            // fixme: logic is correct but original is written differently apparently.
            return this->buildings[buildingID].buildingType == Buildings::BT_CHAPEL
                || this->buildings[buildingID].buildingType == Buildings::BT_CHURCH
                || this->buildings[buildingID].buildingType == Buildings::BT_CATHEDRAL;
        }

    }
}
}
