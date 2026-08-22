#include "OpenSHC/Map/Rocks.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentRockID.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F2BC0
    void __cdecl Rocks ::UpdateRockFunc14()
    {
        DAT_LandscapeState::instance.rocks[DAT_CurrentRockID::instance].gfx = 0x81;
    }

}
}
