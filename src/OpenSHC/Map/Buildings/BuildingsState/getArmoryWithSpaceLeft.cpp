#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00422370
        uint BuildingsState::getArmoryWithSpaceLeft(
            uint targetBuildingID, undefined4 producedItemTypeUnk, int playerID, int resourceToDeposit)
        {
            if (targetBuildingID != 0) {
                return MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getArmoryIDIfSpaceLeft, this)(
                    targetBuildingID, producedItemTypeUnk, playerID, resourceToDeposit);
            }
            for (int i = 1; i < this->maxBuildingsCount; ++i) {
                if (this->buildings[i].buildingType == BT_ARMORY
                    && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::buildingIsAccessible, this)(i, 0)
                        != 0
                    && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getArmoryIDIfSpaceLeft, this)(
                           i, producedItemTypeUnk, playerID, resourceToDeposit)
                        != 0) {
                    return i;
                }
            }
            return 0;
        }

    }
}
}
