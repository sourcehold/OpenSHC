#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // The tribe size is re-read every iteration (0x524906).
        // FUNCTION: STRONGHOLDCRUSADER 0x00524890
        undefined4 TribesState::stopTribeMovementAndCheckIdle(int tribeID)
        {
            short* const tribeSize = &this->tribes[tribeID].size;
            int unitSelectionIndex = 0;
            int busyUnitCount = 0;
            if (*tribeSize > 0) {
                do {
                    int const unitID
                        = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                            tribeID, unitSelectionIndex);
                    ++unitSelectionIndex;
                    if (DAT_UnitsState::instance.units[unitID].logicalState == ULS_NORMAL
                        && DAT_UnitsState::instance.units[unitID].dying == 0) {
                        if (DAT_UnitsState::instance.units[unitID].usingTeleport != 0
                            || DAT_UnitsState::instance.units[unitID].field303_0x413 != 0) {
                            ++busyUnitCount;
                        } else if (DAT_UnitsState::instance.units[unitID].state.generic
                            == States::US_MOVE_TO_DESTINATION) {
                            MACRO_CALL_MEMBER(UnitsState_Func::makeUnitStopWalkingByClearingPathProgressState,
                                DAT_UnitsState::ptr)(unitID);
                            ++busyUnitCount;
                        }
                    }
                } while (unitSelectionIndex < *tribeSize);
                if (busyUnitCount != 0) {
                    return 0;
                }
            }
            return 1;
        }

    }
}
}
