#include "../../../Map.func.hpp"
#include "../TribesState.func.hpp"

#include "OpenSHC/Globals/DAT_UnitSelectionDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        /*
          diff_lea.py reports RLEA here - the original keeps &tribes[tribeID] in a register
          where we recompute it - but a `Tribe&` for the repeated subscript is not the way
          to get it: 79.5% -> 58.8% (norm 73.2% -> 58.8%). Measured twice, by quick_diff
          and by reccmp.
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00522630
        void TribesState::removeUnitFromThisTribeIfInTribe(uint unitID, int tribeID)
        {
            /*
              The import had this guard with an empty body; the original returns. Like
              removeUnitFromTribe, unitID is divided and taken modulo as a signed int, and
              the selection-bit test is a 32-bit `test` of a movsx'd field against a
              movzx'd mask.
             */
            if (DAT_UnitsState::instance.units[unitID].tribeID == 0
                && ((int)this->tribes[tribeID].unitSelectionBitMasked[(int)unitID / 16]
                       & (int)DAT_UnitSelectionDefinedData::instance.BitMaskHelper[(int)unitID % 16])
                    == 0) {
                return;
            }
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
                this->tribes[tribeID].selectionTargetUnitID = -1;
            }
        }

    }
}
}
