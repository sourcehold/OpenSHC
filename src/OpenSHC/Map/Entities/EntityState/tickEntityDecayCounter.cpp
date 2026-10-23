#include "../EntityState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x00401430
        void EntityState::tickEntityDecayCounter(int entityID)
        {
            if (this->entityArray[entityID].unkMinusOne >= 31) {
                this->entityArray[entityID].logicalState = 3;
                return;
            }
            this->entityArray[entityID].unkMinusOne += 1;
        }

    }
}
}
