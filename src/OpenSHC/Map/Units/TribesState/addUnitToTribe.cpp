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
            uint _mod16;
            psVar1 = &this->tribes[tribeID].size;
            *psVar1 = *psVar1 + 1;
            /*
              basically, it sets a bit flag for every unitID that is in the selection
             */
            psVar1 = this->tribes[tribeID].unitSelectionBitMasked + ((int)unitID / 16);
            _mod16 = (int)unitID % 16;
            *psVar1 = *psVar1 | DAT_UnitSelectionDefinedData::instance.BitMaskHelper[_mod16];
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
