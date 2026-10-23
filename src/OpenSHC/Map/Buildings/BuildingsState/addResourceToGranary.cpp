#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0041BC10
        void BuildingsState::addResourceToGranary(ResourceType resourceType, int playerID, int amount)
        {
            for (int i = 1; i < this->maxBuildingsCount; ++i) {
                if (this->buildings[i].owner != playerID || this->buildings[i].buildingType != BT_GRANARY) {
                    continue;
                }
                for (int space = MACRO_CALL_MEMBER(
                         OpenSHC::Map::Buildings::BuildingsState_Func::getResourceCountThatCanBeDeposited, this)(
                         i, resourceType, 250);
                    space != 0; --space) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::addResourceToStockpile,
                        DAT_BuildingsState::ptr)(i, this->buildings[i].uid, resourceType, 1, 250, 1);
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
