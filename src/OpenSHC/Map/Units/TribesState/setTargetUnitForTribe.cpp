#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitLogicState;

        // FUNCTION: STRONGHOLDCRUSADER 0x00525280
        void TribesState::setTargetUnitForTribe(int tribeID)
        {
            int _unitID;
            int _unitSelectionIndex = 0;
            short _tribeSize = this->tribes[tribeID].size;
            this->tribes[tribeID].selectionTargetUnitID = 0;
            if (0 < _tribeSize) {
                do {
                    _unitID = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                        tribeID, _unitSelectionIndex);
                    _unitSelectionIndex = _unitSelectionIndex + 1;
                    if ((DAT_UnitsState::instance.units[_unitID].logicalState == Map::Units::ULS_NORMAL)
                        && (DAT_UnitsState::instance.units[_unitID].dying == 0)) {
                        short _tribeTargetUnitID = this->tribes[tribeID].selectionTargetUnitID;
                        if (!_tribeTargetUnitID) {
                            this->tribes[tribeID].selectionTargetUnitID = (short)_unitID;
                            DAT_UnitsState::instance.units[_unitID].selectionTargetUnitID = (short)_unitID;
                        } else {
                            DAT_UnitsState::instance.units[_unitID].selectionTargetUnitID = _tribeTargetUnitID;
                        }
                    }
                } while (_unitSelectionIndex < this->tribes[tribeID].size);
            }
        }

    }
}
}
