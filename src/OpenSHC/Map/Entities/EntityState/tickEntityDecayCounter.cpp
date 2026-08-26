#include "../EntityState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x00401430
        void EntityState::tickEntityDecayCounter(int param_1)
        {
            short sVar1 = this->entityArray[param_1].unkMinusOne;
            if (0x1f <= sVar1) {
                this->entityArray[param_1].logicalState = 3;
                return;
            }
            this->entityArray[param_1].unkMinusOne = sVar1 + 1;
        }

    }
}
}
