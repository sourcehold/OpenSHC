#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00525280
        void TribesState::setTargetUnitForTribe(int tribeID)
        {
            int _unitSelectionIndex = 0;
            this->tribes[tribeID].selectionTargetUnitID = 0;
            while (_unitSelectionIndex < this->tribes[tribeID].size) {
                int const _unitID = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                    tribeID, _unitSelectionIndex);
                _unitSelectionIndex = _unitSelectionIndex + 1;
                if (DAT_UnitsState::instance.units[_unitID].logicalState == Map::Units::ULS_NORMAL
                    && !DAT_UnitsState::instance.units[_unitID].dying) {
                    short _tribeTargetUnitID = this->tribes[tribeID].selectionTargetUnitID;
                    if (!_tribeTargetUnitID) {
                        this->tribes[tribeID].selectionTargetUnitID = _unitID;
                        DAT_UnitsState::instance.units[_unitID].selectionTargetUnitID = _unitID;
                    } else {
                        DAT_UnitsState::instance.units[_unitID].selectionTargetUnitID = _tribeTargetUnitID;
                    }
                }
            }
        }

    }
}
}
