#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040B540
        void BuildingsState::removeSiegeBuildings(int attackWave, int playerID)
        {
            for (int buildingID = 1; buildingID < this->maxBuildingsCount; ++buildingID) {
                if (this->buildings[buildingID].logicalState != 0 && this->buildings[buildingID].owner == playerID
                    && this->buildings[buildingID].logicalState != BLS_REMOVE) {
                    if (this->buildings[buildingID].buildingType == BT_TUNNEL) {
                        this->buildings[buildingID].logicalState = BLS_REMOVE;
                    } else if (this->buildings[buildingID].attackWave > 0
                        && this->buildings[buildingID].attackWave == attackWave
                        && (this->buildings[buildingID].buildingType == BT_CATAPULT
                            || this->buildings[buildingID].buildingType == BT_FIREBALLISTA
                            || this->buildings[buildingID].buildingType == BT_TREBUCHET
                            || this->buildings[buildingID].buildingType == BT_BATTERINGRAM
                            || this->buildings[buildingID].buildingType == BT_SIEGETOWER
                            || this->buildings[buildingID].buildingType == BT_SHIELD)) {
                        this->buildings[buildingID].logicalState = BLS_REMOVE;
                    }
                }
            }
        }

    }
}
}
