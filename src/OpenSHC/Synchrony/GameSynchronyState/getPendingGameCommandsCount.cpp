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
