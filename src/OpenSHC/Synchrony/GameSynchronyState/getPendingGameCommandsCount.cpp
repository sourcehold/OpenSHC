#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/Commands/GameCommandState.hpp"
#include "OpenSHC/Commands/GameCommandStateByte.hpp"

namespace OpenSHC {
namespace Synchrony {

    using Commands::GameCommandState;
    using Commands::GameCommandStateByte;

    // FUNCTION: STRONGHOLDCRUSADER 0x00480580
    int GameSynchronyState::getPendingGameCommandsCount()
    {
        int _pending = 0;
        // A command slot holds 0 while empty, and GCS_UNPROCESSED..GCS_PROCESSED - 1 while it
        // still waits to be run. Measured: this plain index loop ties the walking-pointer
        // do-while Ghidra produced, so the 1272-byte stride and the pointer are both gone.
        for (int _command = this->gameCommandID; _command < 200; ++_command) {
            GameCommandStateByte _state = this->DAT_GameCommandArray[_command].stateUnk;
            if (_state != 0 && _state < Commands::GCS_PROCESSED) {
                ++_pending;
            }
        }
        return _pending;
    }

}
}
