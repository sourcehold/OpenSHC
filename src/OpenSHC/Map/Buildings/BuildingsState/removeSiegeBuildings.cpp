#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingLogicalState;
        using OpenSHC::Map::Buildings::BuildingType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0040B540
        void BuildingsState::removeSiegeBuildings(int attackWave, int playerID)
        {
            // Removes the tunnels and the siege engines of the given attack wave
            for (int i = 1; i < this->maxBuildingsCount; ++i) {
                if (this->buildings[i].logicalState != 0 && this->buildings[i].owner == playerID
                    && this->buildings[i].logicalState != BLS_REMOVE
                    && (this->buildings[i].buildingType == BT_TUNNEL
                        || (this->buildings[i].attackWave > 0 && this->buildings[i].attackWave == attackWave
                            && (this->buildings[i].buildingType == BT_CATAPULT
                                || this->buildings[i].buildingType == BT_FIREBALLISTA
                                || this->buildings[i].buildingType == BT_TREBUCHET
                                || this->buildings[i].buildingType == BT_BATTERINGRAM
                                || this->buildings[i].buildingType == BT_SIEGETOWER
                                || this->buildings[i].buildingType == BT_SHIELD)))) {
                    this->buildings[i].logicalState = BLS_REMOVE;
                }
            }
        }

    }
}
}
