#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"

namespace OpenSHC {
namespace Synchrony {

    using OpenSHC::Game::GameMode;

    // FUNCTION: STRONGHOLDCRUSADER 0x00490340
    void GameSynchronyState::throttledMultiplayerSyncUpdate()
    {
        if ((this->currentGameMode != OpenSHC::Game::GM_SOLITARY)
            && (this->currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER)) {
            DWORD _now = timeGetTime();
            if (10 < _now - this->field309_0x109e94) {
                this->field309_0x109e94 = _now;
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::sendPeriodicSyncMessages, this)();
            }
        }
    }

}
}
