#include "OpenSHC/Map/Units/TribesState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00521210
        void TribesState::reassignOwnerForTribesOfBehaviorType2(int param_1, int param_2)
        {
            for (int i = 1; i < 1250; i++) {
                if (this->tribes[i].tribeState == 2 && this->tribes[i].owner == param_1) {
                    this->tribes[i].owner = param_2;
                }
            }
        }

    }
}
}
