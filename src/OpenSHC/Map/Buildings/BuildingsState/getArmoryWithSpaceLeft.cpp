#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingType.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x00422370
        uint BuildingsState::getArmoryWithSpaceLeft(
            uint targetBuildingID, undefined4 producedItemTypeUnk, int playerID, int resourceToDeposit)
        {
            if (targetBuildingID != 0) {
                return MACRO_CALL_MEMBER(BuildingsState_Func::getArmoryIDIfSpaceLeft, this)(
                    targetBuildingID, producedItemTypeUnk, playerID, resourceToDeposit);
            }
            for (int buildingID = 1; buildingID < this->maxBuildingsCount; ++buildingID) {
                if (this->buildings[buildingID].buildingType == BT_ARMORY
                    && MACRO_CALL_MEMBER(BuildingsState_Func::buildingIsAccessible, this)(buildingID, 0) != 0
                    && MACRO_CALL_MEMBER(BuildingsState_Func::getArmoryIDIfSpaceLeft, this)(
                           buildingID, producedItemTypeUnk, playerID, resourceToDeposit)
                        != 0) {
                    return buildingID;
                }
            }
            return 0;
        }

    }
}
}
