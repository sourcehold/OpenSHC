#include "../BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0041BCA0
        void BuildingsState::addResourceToArmory(ResourceType resourceType, int playerID, int amount)
        {
            for (int buildingID = 1; buildingID < this->maxBuildingsCount; ++buildingID) {
                if (MACRO_CALL_MEMBER(BuildingsState_Func::getArmoryIDIfSpaceLeft, this)(
                        buildingID, resourceType, playerID, amount)
                    != 0) {
                    MACRO_CALL_MEMBER(BuildingsState_Func::addResourceToStockpile, DAT_BuildingsState::ptr)(
                        buildingID, this->buildings[buildingID].uid, resourceType, amount, 50, 1);
                    return;
                }
            }
            for (int buildingID = 1; buildingID < this->maxBuildingsCount; ++buildingID) {
                while (MACRO_CALL_MEMBER(BuildingsState_Func::getArmoryIDIfSpaceLeft, this)(
                           buildingID, resourceType, playerID, 1)
                    != 0) {
                    MACRO_CALL_MEMBER(BuildingsState_Func::addResourceToStockpile, DAT_BuildingsState::ptr)(
                        buildingID, this->buildings[buildingID].uid, resourceType, 1, 50, 1);
                    amount -= 1;
                    if (amount == 0) {
                        return;
                    }
                }
            }
        }

    }
}
}
