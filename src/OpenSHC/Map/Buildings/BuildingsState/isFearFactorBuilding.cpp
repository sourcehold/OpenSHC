#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0040A400
        uint BuildingsState::isFearFactorBuilding(int buildingID)
        {
            if (this->buildings[buildingID].buildingType == BT_GALLOWS) {
                return 1;
            }
            if (this->buildings[buildingID].buildingType == BT_STOCKS) {
                return 1;
            }
            if (this->buildings[buildingID].buildingType == BT_WITCHHOIST) {
                return 1;
            }
            if (this->buildings[buildingID].buildingType == BT_CESSPIT) {
                return 1;
            }
            if (this->buildings[buildingID].buildingType == BT_BURNINGSTAKE) {
                return 1;
            }
            if (this->buildings[buildingID].buildingType == BT_GIBBET) {
                return 1;
            }
            if (this->buildings[buildingID].buildingType == BT_DUNGEON) {
                return 1;
            }
            if (this->buildings[buildingID].buildingType == BT_STRETCHINGRACK) {
                return 1;
            }
            if (this->buildings[buildingID].buildingType == BT_RACKFLOGGING) {
                return 1;
            }
            if (this->buildings[buildingID].buildingType == BT_CHOPPINGBLOCK) {
                return 1;
            }
            if (this->buildings[buildingID].buildingType == BT_DUNKINGSTOOL) {
                return 1;
            }
            if (this->buildings[buildingID].buildingType == BT_MAYPOLE) {
                return 1;
            }
            if (this->buildings[buildingID].buildingType == BT_GARDEN) {
                return 1;
            }
            if (this->buildings[buildingID].buildingType == BT_STATUE) {
                return 1;
            }
            if (this->buildings[buildingID].buildingType == BT_SHRINE) {
                return 1;
            }
            if (this->buildings[buildingID].buildingType == BT_DANCINGBEAR) {
                return 1;
            }
            if (this->buildings[buildingID].buildingType == BT_POND) {
                return 1;
            }
            if (this->buildings[buildingID].buildingType == BT_WELL) {
                return 1;
            }
            return this->buildings[buildingID].buildingType == BT_BEEHIVE;
        }

    }
}
}
