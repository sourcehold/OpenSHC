#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitLogicState;

        // FUNCTION: STRONGHOLDCRUSADER 0x00524000
        void TribesState::unsetRallyRelatedFlagOnUnits(int tribeID)
        {
            int _unitID;
            int _unitSelectionIndex = 0;
            if (0 < this->tribes[tribeID].size) {
                do {
                    _unitID = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                        tribeID, _unitSelectionIndex);
                    _unitSelectionIndex = _unitSelectionIndex + 1;
                    if ((DAT_UnitsState::instance.units[_unitID].logicalState == Map::Units::ULS_NORMAL)
                        && (DAT_UnitsState::instance.units[_unitID].dying == 0)) {
                        DAT_UnitsState::instance.units[_unitID].rallyRelatedFlag = 0;
                    }
                } while (_unitSelectionIndex < this->tribes[tribeID].size);
            }
        }

    }
}
}
