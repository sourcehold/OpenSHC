#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0040A400
        uint BuildingsState::isFearFactorBuilding(int buildingID)
        {
            if (this->buildings[buildingID].buildingType == BT_GALLOWS
                || this->buildings[buildingID].buildingType == BT_STOCKS
                || this->buildings[buildingID].buildingType == BT_WITCHHOIST
                || this->buildings[buildingID].buildingType == BT_CESSPIT
                || this->buildings[buildingID].buildingType == BT_BURNINGSTAKE
                || this->buildings[buildingID].buildingType == BT_GIBBET
                || this->buildings[buildingID].buildingType == BT_DUNGEON
                || this->buildings[buildingID].buildingType == BT_STRETCHINGRACK
                || this->buildings[buildingID].buildingType == BT_RACKFLOGGING
                || this->buildings[buildingID].buildingType == BT_CHOPPINGBLOCK
                || this->buildings[buildingID].buildingType == BT_DUNKINGSTOOL
                || this->buildings[buildingID].buildingType == BT_MAYPOLE
                || this->buildings[buildingID].buildingType == BT_GARDEN
                || this->buildings[buildingID].buildingType == BT_STATUE
                || this->buildings[buildingID].buildingType == BT_SHRINE
                || this->buildings[buildingID].buildingType == BT_DANCINGBEAR
                || this->buildings[buildingID].buildingType == BT_POND
                || this->buildings[buildingID].buildingType == BT_WELL) {
                return 1;
            }
            return this->buildings[buildingID].buildingType == BT_BEEHIVE;
        }

    }
}
}
