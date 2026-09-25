#include "../EntityState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x00401AE0
        void EntityState::reassignEntitiesOwner(int fromPlayerID, undefined4 toPlayerID)
        {
            for (int entityID = 1; entityID < 3000; ++entityID) {
                if (this->entityArray[entityID].logicalState == 2
                    && this->entityArray[entityID].owner == fromPlayerID) {
                    this->entityArray[entityID].owner = toPlayerID;
                }
            }
        }

    }
}
}
