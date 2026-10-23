#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040A400
        BOOLEnum BuildingsState::isFearFactorBuilding(int buildingID)
        {
            if (this->buildings[buildingID].buildingType == BT_GALLOWS) {
                return TRUE;
            }
            if (this->buildings[buildingID].buildingType == BT_STOCKS) {
                return TRUE;
            }
            if (this->buildings[buildingID].buildingType == BT_WITCHHOIST) {
                return TRUE;
            }
            if (this->buildings[buildingID].buildingType == BT_CESSPIT) {
                return TRUE;
            }
            if (this->buildings[buildingID].buildingType == BT_BURNINGSTAKE) {
                return TRUE;
            }
            if (this->buildings[buildingID].buildingType == BT_GIBBET) {
                return TRUE;
            }
            if (this->buildings[buildingID].buildingType == BT_DUNGEON) {
                return TRUE;
            }
            if (this->buildings[buildingID].buildingType == BT_STRETCHINGRACK) {
                return TRUE;
            }
            if (this->buildings[buildingID].buildingType == BT_RACKFLOGGING) {
                return TRUE;
            }
            if (this->buildings[buildingID].buildingType == BT_CHOPPINGBLOCK) {
                return TRUE;
            }
            if (this->buildings[buildingID].buildingType == BT_DUNKINGSTOOL) {
                return TRUE;
            }
            if (this->buildings[buildingID].buildingType == BT_MAYPOLE) {
                return TRUE;
            }
            if (this->buildings[buildingID].buildingType == BT_GARDEN) {
                return TRUE;
            }
            if (this->buildings[buildingID].buildingType == BT_STATUE) {
                return TRUE;
            }
            if (this->buildings[buildingID].buildingType == BT_SHRINE) {
                return TRUE;
            }
            if (this->buildings[buildingID].buildingType == BT_DANCINGBEAR) {
                return TRUE;
            }
            if (this->buildings[buildingID].buildingType == BT_POND) {
                return TRUE;
            }
            if (this->buildings[buildingID].buildingType == BT_WELL) {
                return TRUE;
            }
            return this->buildings[buildingID].buildingType == BT_BEEHIVE;
        }

    }
}
}
