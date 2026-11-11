#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00523590
        void TribesState::updateAnimalHerdBehaviorState(int tribeID)
        {
            if (tribeID <= 0 || this->tribes[tribeID].predatorNearby > 0) {
                return;
            }
            int unitSelectionIndex = 0;
            while (unitSelectionIndex < this->tribes[tribeID].size) {
                int const unitID = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                    tribeID, unitSelectionIndex);
                unitSelectionIndex = unitSelectionIndex + 1;
                if (DAT_UnitsState::instance.units[unitID].logicalState == Map::Units::ULS_NORMAL
                    && !DAT_UnitsState::instance.units[unitID].dying
                    && DAT_UnitsState::instance.units[unitID].antelopeBasedRngValue == 2) {
                    int rngBucket = DAT_UnitsState::instance.units[unitID].fixedRng & 7;
                    if (rngBucket <= 1) {
                        DAT_UnitsState::instance.units[unitID].antelopeBasedRngValue = 0;
                    } else if (rngBucket <= 5) {
                        DAT_UnitsState::instance.units[unitID].antelopeBasedRngValue = 1;
                    } else {
                        DAT_UnitsState::instance.units[unitID].antelopeBasedRngValue = 2;
                    }
                }
            }
        }

    }
}
}
