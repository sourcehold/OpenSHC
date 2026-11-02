#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // Counts living members with tunnelerFinishedDigging == 2 against the other living members (signed jl at
        // 0x524C7A): 100 if none at 2, 50 if they are not the majority, else 1 if others exist, 0 if all at 2.
        // FUNCTION: STRONGHOLDCRUSADER 0x00524BF0
        int TribesState::getTribeAliveStatus(int tribeID)
        {
            int const tribeSize = this->tribes[tribeID].size;
            int counts[2]; // [0] tunnelerFinishedDigging == 2, [1] other
            counts[1] = 0;
            counts[0] = 0;
            for (int unitSelectionIndex = 0; unitSelectionIndex < tribeSize;) {
                int const unitID = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(tribeID, unitSelectionIndex);
                ++unitSelectionIndex;
                if (DAT_UnitsState::instance.units[unitID].logicalState == ULS_NORMAL
                    && DAT_UnitsState::instance.units[unitID].dying == 0) {
                    if (DAT_UnitsState::instance.units[unitID].tunnelerFinishedDigging == 2) {
                        ++counts[0];
                    } else {
                        ++counts[1];
                    }
                }
            }
            if (counts[0] == 0) {
                return 100;
            }
            if (counts[1] >= counts[0]) {
                return 50;
            }
            return counts[1] != 0;
        }

    }
}
}
