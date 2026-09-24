#include "../EntityState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x00401B60
        void EntityState::destroyEntitiesPart2(int playerID)
        {
            for (int entityID = 1; entityID < 3000; ++entityID) {
                if (this->entityArray[entityID].logicalState == 2 && this->entityArray[entityID].owner == playerID) {
                    this->entityArray[entityID].logicalState = 3;
                }
            }
        }

    }
}
}
