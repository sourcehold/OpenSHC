#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingLogicalState;
        using OpenSHC::Map::Buildings::BuildingType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0040C060
        uint BuildingsState::getArmoryIDIfSpaceLeft(
            uint buildingID, undefined4 resourceID, int playerID, int resourceCount)
        {
            if (this->buildings[buildingID].buildingType != BT_ARMORY) {
                return 0;
            }
            if (this->buildings[buildingID].logicalState != BLS_NORMAL) {
                return 0;
            }
            if (this->buildings[buildingID].owner != playerID) {
                return 0;
            }
            int spaceLeft = 50;
            for (int i = 0; i < 25; ++i) {
                spaceLeft -= this->buildings[buildingID].resources[i];
            }
            return spaceLeft < resourceCount ? 0 : buildingID;
        }

    }
}
}
