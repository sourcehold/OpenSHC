#include "OpenSHC/AI/AIVState.func.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004EDC90
    void AIVState::clearTheHeatmaps()
    {
        MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            307200, '\0', (void*)((int)(this->heatMaps)));
    }

} // namespace AI
} // namespace OpenSHC
