#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051B0C0
        int TroopValueState::getSupportPointIndex(int tile)
        {
            int* piVar2;
            int iVar3;
            iVar3 = 0;
            DAT_TroopValueState::instance.attackInfo.supportPointsNext = 0;
            int iVar1 = 1;
            piVar2 = &DAT_TroopValueState::instance.attackInfo.supportPointsArray[1].tile;
            do {
                if (*piVar2 == tile) {
                    return iVar1;
                }
                if ((*piVar2 == 0) && (!iVar3)) {
                    iVar3 = iVar1;
                    DAT_TroopValueState::instance.attackInfo.supportPointsNext = iVar1;
                }
                piVar2 = piVar2 + 8;
                iVar1 = iVar1 + 1;
            } while ((int)piVar2 < 0x1795884);
            return 0;
        }

    }
}
}
