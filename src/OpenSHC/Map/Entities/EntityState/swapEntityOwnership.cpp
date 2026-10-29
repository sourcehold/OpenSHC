#include "../EntityState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x00401B20
        void EntityState::swapEntityOwnership(int playerA, int playerB)
        {
            for (int entityID = 1; entityID < 3000; ++entityID) {
                if (this->entityArray[entityID].logicalState == 2) {
                    if (this->entityArray[entityID].owner == playerA) {
                        this->entityArray[entityID].owner = playerB;
                    }
                    else if (this->entityArray[entityID].owner == playerB) {
                        this->entityArray[entityID].owner = playerA;
                    }
                }
            }
        }

    }
}
}
