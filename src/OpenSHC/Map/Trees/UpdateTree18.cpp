#include "OpenSHC/Map/Trees.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentTreeID.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"

namespace OpenSHC {
namespace Map {

    // Fixed frame 4..6: (rng1 & 3) + 4, the value 7 is clamped to 6; both frame fields get it.
    // FUNCTION: STRONGHOLDCRUSADER 0x004F2970
    void Trees::UpdateTree18()
    {
        int const treeID = DAT_CurrentTreeID::instance;
        int const frame = (DAT_LandscapeState::instance.trees[treeID].rng1 & 3U) + 4;
        DAT_LandscapeState::instance.trees[treeID].animationFrameUnk = frame;
        if (frame == 7) {
            DAT_LandscapeState::instance.trees[treeID].animationFrameUnk = 6;
        }
        DAT_LandscapeState::instance.trees[treeID].animationFrame2Unk = DAT_LandscapeState::instance.trees[treeID].animationFrameUnk;
    }

}
}
