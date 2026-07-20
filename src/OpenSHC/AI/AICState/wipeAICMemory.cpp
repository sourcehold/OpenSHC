#include "OpenSHC/AI/AICState.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004C6D30
    void AICState::wipeAICMemory()
    {
        AICSpecification* destination = this->aics;
        int iVar1 = 20;
        do {
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemoryWithByteValue, DAT_LowLevelMemory::ptr)(676, '\0', destination);
            destination = destination + 1;
            iVar1 = iVar1 + -1;
        } while (iVar1 != 0);
    }
}
}
