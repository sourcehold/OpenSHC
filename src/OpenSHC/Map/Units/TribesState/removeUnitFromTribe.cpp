#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"

#include "OpenSHC/Globals/DAT_UnitSelectionDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00525A70
        void TribesState::removeUnitFromTribe(uint unitID, int tribeID)
        {
            /*
              unitID is divided and taken modulo as a signed int: the original biases the
              dividend (`cdq; and edx, 0xf; add; sar 4`) and repairs the negative remainder
              (`and -0x7ffffff1; jns; dec; or -0x10; inc`), neither of which an unsigned
              operand needs.
             */
            if (DAT_UnitsState::instance.units[unitID].tribeID != 0
                || ((int)this->tribes[tribeID].unitSelectionBitMasked[(int)unitID / 16]
                        & (int)DAT_UnitSelectionDefinedData::instance.BitMaskHelper[(int)unitID % 16])
                    != 0) {
                /*
                  The base is NOT taken once here, although the original does take it
                  (`lea ebp, [eax + ebx]`) and read the size, the tribe state and the
                  target unit through it as `[ebp + 0x5c]`, `[ebp + 0x40]` and `[ebp + 0x5a]`.
                  Mirroring that - shifted TribesState pointer, bitmask accesses left on the
                  subscript where the original also keeps them - costs 29.9 points
                  (67.1% -> 37.2%). The same change is worth +11.8 in trimTribeToSize, which
                  differs in having only the two size reads on the base; here a second
                  addressing base is live for the bitmask and the two fight over registers.
                 */
                short const _size = this->tribes[tribeID].size;
                if (0 < _size) {
                    this->tribes[tribeID].size = _size + -1;
                }
                if (this->tribes[tribeID].size <= 0) {
                    this->tribes[tribeID].tribeState = 3;
                }
                short* psVar1 = this->tribes[tribeID].unitSelectionBitMasked + ((int)unitID / 16);
                *psVar1 = *psVar1 & DAT_UnitSelectionDefinedData::instance.BitMaskHelper2[(int)unitID % 16];
                if (DAT_UnitsState::instance.units[unitID].tribeID == tribeID) {
                    DAT_UnitsState::instance.units[unitID].selectionTargetUnitID = 0;
                    DAT_UnitsState::instance.units[unitID].tribeID = 0;
                    DAT_UnitsState::instance.units[unitID].idInTribe = 0;
                }
                if ((int)this->tribes[tribeID].selectionTargetUnitID == unitID) {
                    MACRO_CALL_MEMBER(Map::Units::TribesState_Func::setTargetUnitForTribe, this)(tribeID);
                }
            }
            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::setWhetherTribeContainsAnyUnits, this)(tribeID);
        }

    }
}
}
