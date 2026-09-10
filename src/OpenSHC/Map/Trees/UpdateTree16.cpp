#include "OpenSHC/Map/Trees.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentTreeID.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F28F0
    void Trees::UpdateTree16()
    {
        int iVar2 = (DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].rng1 & 7U) + 10;
        DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameUnk = iVar2;
        DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrame2Unk = iVar2;
    }

}
}
