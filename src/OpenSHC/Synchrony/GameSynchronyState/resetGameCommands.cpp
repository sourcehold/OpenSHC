#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x00480050
    void GameSynchronyState::resetGameCommands()
    {
        this->DAT_CurrentGameCommandID = 0;
        this->gameCommandID = 0;
        this->DAT_GameCommandArrayIndex = 0;
        MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            sizeof(this->DAT_GameCommandArray), '\0', this->DAT_GameCommandArray);
        for (int _player = 0; _player < 9; ++_player) {
            this->DAT_LagIndicatorPerPlayer[_player] = 1000;
        }
    }

}
}
