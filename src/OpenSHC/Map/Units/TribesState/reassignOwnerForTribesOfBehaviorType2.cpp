#include "OpenSHC/Map/Units/TribesState.func.hpp"

#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00521210
        void TribesState::reassignOwnerForTribesOfBehaviorType2(int param_1, int param_2)
        {
            for (int i = 1; i < 1250; i++) {
                // DAT_TribesState::instance is required instead of this for there to be 100% match
                if (DAT_TribesState::instance.tribes[i].tribeState == 2
                    && DAT_TribesState::instance.tribes[i].owner == param_1) {
                    DAT_TribesState::instance.tribes[i].owner = param_2;
                }
            }
        }

    }
}
}
