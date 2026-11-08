#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0041BC10
        void BuildingsState::addResourceToGranary(ResourceType resourceType, int playerID, int amount)
        {
            for (int buildingID = 1; buildingID < this->maxBuildingsCount; ++buildingID) {
                if (this->buildings[buildingID].owner == playerID
                    && this->buildings[buildingID].buildingType == BT_GRANARY) {
                    for (int space = MACRO_CALL_MEMBER(BuildingsState_Func::getResourceCountThatCanBeDeposited, this)(
                             buildingID, resourceType, 250);
                        space != 0; --space) {
                        MACRO_CALL_MEMBER(BuildingsState_Func::addResourceToStockpile, DAT_BuildingsState::ptr)(
                            buildingID, this->buildings[buildingID].uid, resourceType, 1, 250, 1);
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
}
