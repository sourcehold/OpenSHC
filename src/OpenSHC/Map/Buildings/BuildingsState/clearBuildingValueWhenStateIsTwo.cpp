#include "../BuildingsState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040F3F0
        void BuildingsState::clearBuildingValueWhenStateIsTwo()
        {
            for (int iVar1 = 1; iVar1 < (int)this->maxBuildingsCount; iVar1++) {
                if (this->buildings[iVar1].logicalState == Buildings::BLS_NORMAL) {
                    this->buildings[iVar1].animStateCounterTracker = 0;
                }
            }
        }

    }
}
}
