#include "../EntityState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x00401B60
        void EntityState::destroyEntitiesPart2(int param_1)
        {
            for (int iVar1 = 1; iVar1 < 3000; iVar1++) {
                if ((this->entityArray[iVar1].logicalState == 2) && (this->entityArray[iVar1].owner == param_1)) {
                    this->entityArray[iVar1].logicalState = 3;
                }
            }
        }

    }
}
}
