#include "OpenSHC/Map/Rocks.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentRockID.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F2BE0
    void Rocks::UpdateRockFunc15() { DAT_LandscapeState::instance.rocks[DAT_CurrentRockID::instance].gfx = 0xc1; }

}
}
