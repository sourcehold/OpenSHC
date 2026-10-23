#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0041BCA0
        void BuildingsState::addResourceToArmory(ResourceType resourceType, int playerID, int amount)
        {
            int buildingCount = this->maxBuildingsCount;
            for (int i = 1; i < buildingCount; ++i) {
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getArmoryIDIfSpaceLeft, this)(
                        i, resourceType, playerID, amount)
                    != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::addResourceToStockpile,
                        DAT_BuildingsState::ptr)(i, this->buildings[i].uid, resourceType, amount, 50, 1);
                    return;
                }
            }

            // No single armory has enough space, spread the resources one by one
            for (int i = 1; i < this->maxBuildingsCount; ++i) {
                while (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getArmoryIDIfSpaceLeft, this)(
                           i, resourceType, playerID, 1)
                    != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::addResourceToStockpile,
                        DAT_BuildingsState::ptr)(i, this->buildings[i].uid, resourceType, 1, 50, 1);
                    --amount;
                    if (amount == 0) {
                        return;
                    }
                }
            }
        }

    }
}
}
