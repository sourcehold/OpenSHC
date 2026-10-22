#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x004800B0
    void GameSynchronyState::clearGameCommandEntry(int gameCommandID)
    {
        if (gameCommandID < 200) {
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                sizeof(this->DAT_GameCommandArray[gameCommandID]), 0, &this->DAT_GameCommandArray[gameCommandID]);
        }
    }

}
}
