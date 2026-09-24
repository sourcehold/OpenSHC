#include "OpenSHC/Map/Trees.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentTreeID.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F28F0
    void Trees::UpdateTree16()
    {
        int const frame = (DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].rng1 & 7U) + 10;
        DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameUnk = frame;
        DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrame2Unk = frame;
    }

}
}
