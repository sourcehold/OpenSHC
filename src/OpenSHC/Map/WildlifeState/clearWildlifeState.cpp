#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/WildlifeState.func.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_WildlifeState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x0052B9F0
    void WildlifeState::clearWildlifeState()
    {
        MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            sizeof(DAT_WildlifeState::instance.grid), 0, DAT_WildlifeState::instance.grid);
    }

}
}
