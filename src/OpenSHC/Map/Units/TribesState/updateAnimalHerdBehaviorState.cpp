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
                          Signed, and tested against 1 rather than 2. The original has
                          `cmp ecx, 1; jg` and derives the second value with `setg`, where
                          a `uint` gives `jae` and `seta`. Written `< 2` the literal does
                          not appear in the compare at all - MSVC puts 2 in a register and
                          emits `cmp ecx, ebx; jge` - so the bound is written as `<= 1`,
                          which is the same test on ints and the instruction the original
                          has. The arms are already the right way round: the original's
                          `jg` skips the nine bytes of the zero store, so that store is
                          its fall-through.
                         */
                        int uVar2 = DAT_UnitsState::instance.units[iVar1].fixedRng & 7;
                        if (uVar2 <= 1) {
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
