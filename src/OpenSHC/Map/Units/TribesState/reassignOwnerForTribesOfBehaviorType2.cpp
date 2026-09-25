#include "../TribesState.func.hpp"

#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00521210
        void TribesState::reassignOwnerForTribesOfBehaviorType2(int fromPlayerID, int toPlayerID)
        {
            // the original reads DAT_TribesState::instance instead of this
            for (int i = 1; i < 1250; ++i) {
                if (DAT_TribesState::instance.tribes[i].tribeState == 2
                    && DAT_TribesState::instance.tribes[i].owner == fromPlayerID) {
                    DAT_TribesState::instance.tribes[i].owner = toPlayerID;
                }
            }
        }

    }
}
}
