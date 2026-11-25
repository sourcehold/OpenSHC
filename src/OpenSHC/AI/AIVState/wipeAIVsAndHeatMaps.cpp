#include "../AIVState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004EF090
    void AIVState::wipeAIVsAndHeatMaps()
    {
        this->aivCount = 0;
        for (int aivID = 0; aivID < 9; ++aivID) {
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                sizeof(this->aivs[aivID]), 0, &this->aivs[aivID]);
        }
        MACRO_CALL_MEMBER(AIVState_Func::clearTheHeatmaps, this)();
    }

}
}
