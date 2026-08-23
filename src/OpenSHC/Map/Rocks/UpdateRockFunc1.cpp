#include "OpenSHC/Map/Rocks.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentRockID.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F2A20
    void Rocks::UpdateRockFunc1() { DAT_LandscapeState::instance.rocks[DAT_CurrentRockID::instance].gfx = 529; }

}
}
