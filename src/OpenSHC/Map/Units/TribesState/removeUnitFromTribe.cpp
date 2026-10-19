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
            short* psVar1;
            uint uVar2;
            short _size;
            if (DAT_UnitsState::instance.units[unitID].tribeID == 0) {
                uVar2 = unitID & 0x8000000f;
                if ((int)uVar2 < 0) {
                    uVar2 = (uVar2 - 1 | 0xfffffff0) + 1;
                }
                if ((ushort)(DAT_UnitSelectionDefinedData::instance.BitMaskHelper[uVar2]
                        & this->tribes[tribeID].unitSelectionBitMasked[unitID / 16])
                    == 0)
                    goto LAB_00525b56;
            }
            _size = this->tribes[tribeID].size;
            if (0 < _size) {
                this->tribes[tribeID].size = _size + -1;
            }
            if (this->tribes[tribeID].size <= 0) {
                this->tribes[tribeID].tribeState = 3;
            }
            psVar1 = this->tribes[tribeID].unitSelectionBitMasked + (unitID / 16);
            uVar2 = unitID & 0x8000000f;
            if ((int)uVar2 < 0) {
                uVar2 = (uVar2 - 1 | 0xfffffff0) + 1;
            }
            *psVar1 = *psVar1 & DAT_UnitSelectionDefinedData::instance.BitMaskHelper2[uVar2];
            if (DAT_UnitsState::instance.units[unitID].tribeID == tribeID) {
                DAT_UnitsState::instance.units[unitID].selectionTargetUnitID = 0;
                DAT_UnitsState::instance.units[unitID].tribeID = 0;
                DAT_UnitsState::instance.units[unitID].idInTribe = 0;
            }
            if ((int)this->tribes[tribeID].selectionTargetUnitID == unitID) {
                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::setTargetUnitForTribe, this)(tribeID);
            }
        LAB_00525b56:
            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::setWhetherTribeContainsAnyUnits, this)(tribeID);
        }

    }
}
}
