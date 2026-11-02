#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051B290
        void TroopValueState::pruneStaleTentPoints()
        {
            // The original walks slots 1..1999 (end 0x17A52B4): the tent point table really has 2000 entries,
            // tentPointsValues is declared with only 216.
            for (int slot = 1; slot < 2000; ++slot) {
                if (DAT_TroopValueState::instance.attackInfo.tentPointsValues[slot].someCounter
                    != DAT_TroopValueState::instance.attackInfo.someCounter1) {
                    MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                        sizeof(DAT_TroopValueState::instance.attackInfo.tentPointsValues[slot]), 0,
                        &DAT_TroopValueState::instance.attackInfo.tentPointsValues[slot]);
                }
                else {
                    if (DAT_TroopValueState::instance.attackInfo.tentPointsValues[slot].tribeID != 0
                        && MACRO_CALL_MEMBER(TribesState_Func::tribeCorrespondsWithUID, DAT_TribesState::ptr)(
                               DAT_TroopValueState::instance.attackInfo.tentPointsValues[slot].tribeID,
                               DAT_TroopValueState::instance.attackInfo.tentPointsValues[slot].tribeUID)
                            == FALSE) {
                        MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue,
                            DAT_LowLevelMemory::ptr)(sizeof(DAT_TroopValueState::instance.attackInfo.tentPointsValues[slot]),
                            0, &DAT_TroopValueState::instance.attackInfo.tentPointsValues[slot]);
                    }
                    if (DAT_TroopValueState::instance.attackInfo.tentPointsValues[slot].three > 0) {
                        DAT_TroopValueState::instance.attackInfo.tentPointsValues[slot].three--;
                    }
                }
            }
        }

    }
}
}
