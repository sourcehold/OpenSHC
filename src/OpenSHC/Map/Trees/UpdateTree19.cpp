#include "OpenSHC/Map/Trees.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentTreeID.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F29C0
    void Trees::UpdateTree19()
    {
        int const treeID = DAT_CurrentTreeID::instance;
        int const frame = (DAT_LandscapeState::instance.trees[treeID].rng1 & 3) + 7;
        DAT_LandscapeState::instance.trees[treeID].animationFrameUnk = frame;
        if (frame == 10) {
            DAT_LandscapeState::instance.trees[treeID].animationFrameUnk = 9;
        }
        DAT_LandscapeState::instance.trees[treeID].animationFrame2Unk
            = DAT_LandscapeState::instance.trees[treeID].animationFrameUnk;
    }

}
}
