#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingLogicalState;

        // FUNCTION: STRONGHOLDCRUSADER 0x00424220
        void BuildingsState::recomputeAccessibilityForAllBuildings()
        {
            for (int i = 1; i < this->maxBuildingsCount; ++i) {
                if (this->buildings[i].logicalState != 0 && this->buildings[i].logicalState != BLS_REMOVE) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::buildingIsAccessible,
                        DAT_BuildingsState::ptr)(i, 0);
                }
            }
        }

    }
}
}
