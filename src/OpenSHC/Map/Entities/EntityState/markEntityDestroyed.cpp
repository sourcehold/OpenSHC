#include "../EntityState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x00401400
        void EntityState::markEntityDestroyed(int entityID)
        {
            if (entityID > 0) {
                this->entityArray[entityID].logicalState = 3;
                this->entityArray[entityID].someCounter_OR_hitGround = 10;
            }
        }

    }
}
}
