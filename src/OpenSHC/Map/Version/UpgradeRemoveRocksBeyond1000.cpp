#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Version.func.hpp"
#include "OpenSHC/Map/Rocks/Rock.hpp"

#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Rocks::Rock;

    // FUNCTION: STRONGHOLDCRUSADER 0x004F3900
    void Version::UpgradeRemoveRocksBeyond1000()
    {
        for (int i = 2000; i < 4000; i += 1) {
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                32, 0, &DAT_LandscapeState::instance.rocks[i]);
        }
    }

}
}
