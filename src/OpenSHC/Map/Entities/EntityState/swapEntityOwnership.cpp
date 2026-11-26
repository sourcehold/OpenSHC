#include "../EntityState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x00401B20
        void EntityState::swapEntityOwnership(int param_1, int param_2)
        {
            for (int i = 1; i < 3000; ++i) {
                if (this->entityArray[i].logicalState == 2) {
                    if (this->entityArray[i].owner == param_1) {
                        this->entityArray[i].owner = static_cast<short>(param_2);
                    } else if (this->entityArray[i].owner == param_2) {
                        this->entityArray[i].owner = static_cast<short>(param_1);
                    }
                }
            }
        }

    } // namespace Entities
} // namespace Map
} // namespace OpenSHC
