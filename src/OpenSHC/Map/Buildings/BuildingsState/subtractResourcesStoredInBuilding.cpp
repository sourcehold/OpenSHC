#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0041BF50
        void BuildingsState::subtractResourcesStoredInBuilding(int buildingID)
        {
            if (this->buildings[buildingID].buildingType != BT_STOCKPILE
                && this->buildings[buildingID].buildingType != BT_GRANARY
                && this->buildings[buildingID].buildingType != BT_ARMORY) {
                return;
            }
            int const owner = this->buildings[buildingID].owner;
            for (int resourceType = 1; resourceType < 25; ++resourceType) {
                int const amount = this->buildings[buildingID].resources[resourceType];
                if (amount != 0) {
                    DAT_GameState::instance.playerDataArray[owner].currentResources[resourceType] -= amount;
                    if (DAT_GameState::instance.playerDataArray[owner].currentResources[resourceType] < 0) {
                        DAT_GameState::instance.playerDataArray[owner].currentResources[resourceType] = 0;
                    }
                }
            }
            MACRO_CALL_MEMBER(BuildingsState_Func::countPlayerResources, this)(owner);
        }

    }
}
}
