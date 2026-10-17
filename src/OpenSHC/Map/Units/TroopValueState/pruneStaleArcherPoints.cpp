#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051AF70
        void TroopValueState::pruneStaleArcherPoints()
        {
            BOOLEnum BVar1;
            ArcherAttackPoint* point = &DAT_TroopValueState::instance.attackInfo.archerPointArray[1];
            do {
                if (point->lastSeenCounter != DAT_TroopValueState::instance.attackInfo.someCounter1) {
                    MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                        0x20, '\0', (void*)((int)(point)));
                } else {
                    if (point->tribeID != 0) {
                        BVar1 = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::tribeCorrespondsWithUID,
                            DAT_TribesState::ptr)(point->tribeID, point->tribeUID);
                        if (!BVar1) {
                            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                                0x20, '\0', (void*)((int)(point)));
                        }
                    }
                    if (0 < point->claimCooldown) {
                        point->claimCooldown = point->claimCooldown + -1;
                    }
                }
                point = point + 1;
            } while ((int)point
                < (int)&DAT_TroopValueState::instance.attackInfo.archerPointArray[200]);
        }

    }
}
}
