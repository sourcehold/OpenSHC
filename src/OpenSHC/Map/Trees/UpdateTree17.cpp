#include "OpenSHC/Map/Trees.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentTreeID.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"

namespace OpenSHC {
namespace Map {

    // Fixed frame 1..3: (rng1 & 3) + 1, the value 4 is clamped to 3; both frame fields get it.
    // FUNCTION: STRONGHOLDCRUSADER 0x004F2920
    void Trees::UpdateTree17()
    {
        int const treeID = DAT_CurrentTreeID::instance;
        int const frame = (DAT_LandscapeState::instance.trees[treeID].rng1 & 3U) + 1;
        DAT_LandscapeState::instance.trees[treeID].animationFrameUnk = frame;
        if (frame == 4) {
            DAT_LandscapeState::instance.trees[treeID].animationFrameUnk = 3;
        }
        DAT_LandscapeState::instance.trees[treeID].animationFrame2Unk = DAT_LandscapeState::instance.trees[treeID].animationFrameUnk;
    }

}
}
