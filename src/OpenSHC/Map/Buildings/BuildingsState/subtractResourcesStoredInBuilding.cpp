#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0041BF50
        void BuildingsState::subtractResourcesStoredInBuilding(int buildingID)
        {
            if (this->buildings[buildingID].buildingType != BT_STOCKPILE
                && this->buildings[buildingID].buildingType != BT_GRANARY
                && this->buildings[buildingID].buildingType != BT_ARMORY) {
                return;
            }

            int playerID = this->buildings[buildingID].owner;
            for (int i = 1; i < 25; ++i) {
                if (this->buildings[buildingID].resources[i] != 0) {
                    DAT_GameState::instance.playerDataArray[playerID].currentResources[i]
                        -= this->buildings[buildingID].resources[i];
                    if (DAT_GameState::instance.playerDataArray[playerID].currentResources[i] < 0) {
                        DAT_GameState::instance.playerDataArray[playerID].currentResources[i] = 0;
                    }
                }
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::countPlayerResources, this)(playerID);
        }

    }
}
}
