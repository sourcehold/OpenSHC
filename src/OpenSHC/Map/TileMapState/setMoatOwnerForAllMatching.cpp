#include "../TileMapState.func.hpp"

namespace OpenSHC {
namespace Map {

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */

    // FUNCTION: STRONGHOLDCRUSADER 0x00500750
    void TileMapState::setMoatOwnerForAllMatching(int param_1, undefined4 param_2)

    {
        byte* pbVar1;
        int iVar2;

        pbVar1 = &this->moats[1].owner;
        iVar2 = 15999;
        do {
            if ((*pbVar1 != 0) && ((char)*pbVar1 == param_1)) {
                *pbVar1 = (byte)param_2;
            }
            pbVar1 = pbVar1 + 0x10;
            iVar2 = iVar2 + -1;
        } while (iVar2 != 0);
        return;
    }

}
}
