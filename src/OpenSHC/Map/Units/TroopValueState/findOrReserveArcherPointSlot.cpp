#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051AF20
        int TroopValueState::findOrReserveArcherPointSlot(int param_1)
        {
            int iVar1;
            int* piVar2;
            int iVar3;
            iVar3 = 0;
            DAT_TroopValueState::instance.attackInfo.archerPointsNext = 0;
            iVar1 = 1;
            piVar2 = (int*)&DAT_TroopValueState::instance.attackInfo.archerPointArray[1].tile;
            do {
                if (*piVar2 == param_1) {
                    return iVar1;
                }
                if ((*piVar2 == 0) && (!iVar3)) {
                    iVar3 = iVar1;
                    DAT_TroopValueState::instance.attackInfo.archerPointsNext = iVar1;
                }
                piVar2 = piVar2 + 8;
                iVar1 = iVar1 + 1;
            } while ((int)piVar2 < 0x17802ac);
            return 0;
        }

    }
}
}
