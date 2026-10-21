#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitLogicState;

        // FUNCTION: STRONGHOLDCRUSADER 0x00523590
        void TribesState::updateAnimalHerdBehaviorState(int tribeID)
        {
            int iVar1;
            int unitSelectionIndex;
            if (0 < tribeID && this->tribes[tribeID].predatorNearby == 0
                && (unitSelectionIndex = 0, 0 < this->tribes[tribeID].size)) {
                do {
                    iVar1 = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                        tribeID, unitSelectionIndex);
                    unitSelectionIndex = unitSelectionIndex + 1;
                    if (DAT_UnitsState::instance.units[iVar1].logicalState == Map::Units::ULS_NORMAL
                        && DAT_UnitsState::instance.units[iVar1].dying == 0
                        && DAT_UnitsState::instance.units[iVar1].antelopeBasedRngValue == 2) {
                        /*
                          Signed: the original compares against the literal with
                          `cmp ecx, 1; jg` and derives the second value with `setg`, where a
                          `uint` gives `jae` and `seta` against a register holding 1.
                         */
                        int uVar2 = DAT_UnitsState::instance.units[iVar1].fixedRng & 7;
                        if (uVar2 < 2) {
                            DAT_UnitsState::instance.units[iVar1].antelopeBasedRngValue = 0;
                        } else {
                            DAT_UnitsState::instance.units[iVar1].antelopeBasedRngValue = (5 < uVar2) + 1;
                        }
                    }
                } while (unitSelectionIndex < this->tribes[tribeID].size);
            }
        }

    }
}
}
