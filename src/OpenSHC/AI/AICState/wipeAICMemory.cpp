#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/AI/AICState.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004C6D30
    void AICState::wipeAICMemory()
    {
        for (int i = 0; i < 20; i++) {
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemoryWithByteValue, DAT_LowLevelMemory::ptr)(
                676, '\0', &this->aics[i]);
        }
    }
}
}
