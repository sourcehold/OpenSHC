#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"

#include "OpenSHC/Globals/DAT_UnitSelectionDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00522590
        void TribesState::addUnitToTribe(uint unitID, int tribeID)
        {
            short* psVar1;
            this->tribes[tribeID].size = this->tribes[tribeID].size + 1;
            /*
              basically, it sets a bit flag for every unitID that is in the selection
             */
            /*
              The remainder is not named, which is a wash on the score (86.7% either way).
              The gap here is a register: the original builds the cursor in a scratch
              register (`mov edx, edi`, `imul edx, edx, 0x19a`, `add edx, eax`,
              `lea eax, [ecx + edx*2 + 0x60]`) where ours needs EBP and so a push and a pop,
              and dropping the local was not enough to free one. Naming the word index
              instead, so the division runs before the multiply as it does in the original
              (`cdq`, `and edx, 0xf`, `add eax, edx`, then `imul edx, edx, 0x19a`, then
              `sar eax, 4`), is flat at 86.7% - MSVC still schedules the multiply first and
              still wants EBP for it.
             */
            psVar1 = this->tribes[tribeID].unitSelectionBitMasked + ((int)unitID / 16);
            *psVar1 = *psVar1 | DAT_UnitSelectionDefinedData::instance.BitMaskHelper[(int)unitID % 16];
            if (this->tribes[tribeID].selectionTargetUnitID == 0) {
                this->tribes[tribeID].selectionTargetUnitID = (short)unitID;
            }
            DAT_UnitsState::instance.units[unitID].selectionTargetUnitID = this->tribes[tribeID].selectionTargetUnitID;
            DAT_UnitsState::instance.units[unitID].tribeID = (short)tribeID;
            DAT_UnitsState::instance.units[unitID].tribeUID = this->tribes[tribeID].uid;
            DAT_UnitsState::instance.units[unitID].idInTribe = this->tribes[tribeID].size;
            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::setWhetherTribeContainsAnyUnits, this)(tribeID);
        }

    }
}
}
