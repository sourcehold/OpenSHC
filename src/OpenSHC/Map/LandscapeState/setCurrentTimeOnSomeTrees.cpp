#include "OpenSHC/Map/LandscapeState.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentTreeID.hpp"
#include "OpenSHC/Globals/g_treeUpdateTime.hpp"

namespace OpenSHC {
namespace Map {

    // The loop counter is the global DAT_CurrentTreeID (left at 2000); trees in state 0 (free) or 3 are skipped.
    // FUNCTION: STRONGHOLDCRUSADER 0x004F20E0
    void LandscapeState::setCurrentTimeOnSomeTrees()
    {
        g_treeUpdateTime::instance = timeGetTime();
        for (DAT_CurrentTreeID::instance = 1; (int)DAT_CurrentTreeID::instance < 2000; DAT_CurrentTreeID::instance++) {
            short const state = this->trees[DAT_CurrentTreeID::instance].state;
            if (state != 0 && state != 3) {
                this->trees[DAT_CurrentTreeID::instance].field8_0x14 = g_treeUpdateTime::instance;
            }
        }
    }

}
}
