#include "../EntityState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x00401400
        void EntityState::markEntityDestroyed(int param_1)
        {
            if (0 < param_1) {
                this->entityArray[param_1].logicalState = 3;
                this->entityArray[param_1].someCounter_OR_hitGround = 10;
            }
        }

    }
}
}
