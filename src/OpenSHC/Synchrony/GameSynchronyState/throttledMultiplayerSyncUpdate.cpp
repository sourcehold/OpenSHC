#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Synchrony {

    using OpenSHC::Game::GameMode;

    // FUNCTION: STRONGHOLDCRUSADER 0x00490340
    void GameSynchronyState::throttledMultiplayerSyncUpdate()
    {
        if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY
            || DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
            return;
        }
        DWORD const now = timeGetTime();
        if (now - this->field309_0x109e94 > 10) {
            this->field309_0x109e94 = now;
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::sendPeriodicSyncMessages, this)();
        }
    }

}
}
