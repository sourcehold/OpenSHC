#include "../../Synchrony.func.hpp"
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
        GameCommandStateByte* _statePtr;
        int _pending = 0;
        int _firstCommand = this->gameCommandID;
        if (_firstCommand < 200) {
            _statePtr = &this->DAT_GameCommandArray[_firstCommand].stateUnk;
            int _remaining = 200 - _firstCommand;
            // Measured: the counted do-while over a walking pointer is what the original compiles to.
            // A for loop costs the match (100.0% -> 91.7%), a while loop adds an instruction, and
            // indexing DAT_GameCommandArray per iteration loses three, so this shape stays.
            do {
                if (*_statePtr != (GameCommandState)0 && (char)*_statePtr < '\n') {
                    _pending = _pending + 1;
                }
                _statePtr = _statePtr + 1272;
                _remaining = _remaining + -1;
            } while (_remaining);
        }
        return _pending;
    }

}
}
