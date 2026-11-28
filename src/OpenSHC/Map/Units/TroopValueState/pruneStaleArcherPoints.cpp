#include "../TroopValueState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051AF70
        void TroopValueState::pruneStaleArcherPoints()
        {
            for (int slot = 1; slot < countof(DAT_TroopValueState::instance.attackInfo.archerPointArray) - 1; ++slot) {
                if (DAT_TroopValueState::instance.attackInfo.archerPointArray[slot].lastSeenCounter
                    != DAT_TroopValueState::instance.attackInfo.someCounter1) {
                    MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                        sizeof(DAT_TroopValueState::instance.attackInfo.archerPointArray[slot]), 0,
                        &DAT_TroopValueState::instance.attackInfo.archerPointArray[slot]);
                } else {
                    if (DAT_TroopValueState::instance.attackInfo.archerPointArray[slot].tribeID != 0
                        && MACRO_CALL_MEMBER(
                               Map::Units::TribesState_Func::tribeCorrespondsWithUID, DAT_TribesState::ptr)(
                               DAT_TroopValueState::instance.attackInfo.archerPointArray[slot].tribeID,
                               DAT_TroopValueState::instance.attackInfo.archerPointArray[slot].tribeUID)
                            == FALSE) {
                        MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                            sizeof(DAT_TroopValueState::instance.attackInfo.archerPointArray[slot]), 0,
                            &DAT_TroopValueState::instance.attackInfo.archerPointArray[slot]);
                    }
                    if (DAT_TroopValueState::instance.attackInfo.archerPointArray[slot].claimCooldown > 0) {
                        DAT_TroopValueState::instance.attackInfo.archerPointArray[slot].claimCooldown--;
                    }
                }
            }
        }

    }
}
}
