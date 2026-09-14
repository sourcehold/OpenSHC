#include "../EntityState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x00401AE0
        void EntityState::reassignEntitiesOwner(int param_1, undefined4 param_2)
        {
            for (int index = 1; index < 3000; index++) {
                if ((this->entityArray[index].logicalState == 2) && (this->entityArray[index].owner == param_1)) {
                    this->entityArray[index].owner = param_2;
                }
            }
        }

    }
}
}
