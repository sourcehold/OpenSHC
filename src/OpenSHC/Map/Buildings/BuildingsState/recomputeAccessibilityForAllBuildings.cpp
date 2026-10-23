#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x00424220
        void BuildingsState::recomputeAccessibilityForAllBuildings()
        {
            for (int buildingID = 1; buildingID < this->maxBuildingsCount; ++buildingID) {
                if (this->buildings[buildingID].logicalState != 0
                    && this->buildings[buildingID].logicalState != BLS_REMOVE) {
                    MACRO_CALL_MEMBER(BuildingsState_Func::buildingIsAccessible, DAT_BuildingsState::ptr)(
                        buildingID, 0);
                }
            }
        }

    }
}
}
