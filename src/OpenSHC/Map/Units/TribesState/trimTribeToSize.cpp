#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_CurrentTribeID.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitLogicState;

        // FUNCTION: STRONGHOLDCRUSADER 0x00522EF0
        void TribesState::trimTribeToSize(undefined4 tribeID, int smallerSize)
        {
            UnitLogicStateShort* pUVar1;
            UnitLogicStateShort UVar2;
            int iVar3;
            int unitSelectionIndex;
            int _currentTribeID;
            _currentTribeID = DAT_CurrentTribeID::instance;
            unitSelectionIndex = 0;
            /*
              The size is read through a base taken once, which is what the original does
              (`lea ebp, [eax + edi]` at 0x522f0b, then `[ebp + 0x5c]`); the tribeState test
              above it stays on the subscript, where the original has
              `cmp word ptr [eax + edi + 0x40], si`. Hoisting a pointer to the size field
              itself was tried earlier and cost 1.2 points - that gives `[ptr]` with no
              displacement, not the `+0x5c` the original uses.

              Do not try to predict where this helps. Caching the base the way the original
              does is worth +11.8 here and loses everywhere else it has been measured:
              removeUnitFromTribe -29.9, removeUnitFromThisTribeIfInTribe -34.4,
              updateAnimalHerdBehaviorState -40.8, giveTribeAnInstruction -4.8,
              updateTribeUnitAssignments flat. I thought the discriminator was whether the
              cached base is the function's only addressing base; updateAnimalHerdBehaviorState
              fits that description better than this function does and lost forty points, so
              the rule is wrong. Measure each function on its own.
             */
            TribesState* const _tb
                = (TribesState*)((char*)this + DAT_CurrentTribeID::instance * sizeof(Tribe));
            if (this->tribes[DAT_CurrentTribeID::instance].tribeState != 0
                && (iVar3 = (int)_tb->tribes[0].size, iVar3 >= smallerSize)
                && 0 < iVar3) {
                do {
                    iVar3 = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                        _currentTribeID, unitSelectionIndex);
                    pUVar1 = &DAT_UnitsState::instance.units[iVar3].logicalState;
                    UVar2 = *pUVar1;
                    unitSelectionIndex = unitSelectionIndex + 1;
                    if ((((UVar2 == ((UnitLogicState)1)) || (UVar2 == Map::Units::ULS_NORMAL))
                            || (UVar2 == Map::Units::ULS_TRANSITIONING))
                        && smallerSize <= unitSelectionIndex) {
                        *pUVar1 = Map::Units::ULS_REMOVE;
                    }
                } while (unitSelectionIndex < _tb->tribes[0].size);
            }
        }

    }
}
}
