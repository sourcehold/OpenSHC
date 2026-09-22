#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/AI/AICState.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D1090
    void AICState::setTriggerForAITauntResponse()
    {
        if (MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)() != FALSE) {
            this->aiTauntResponseTimeWindow = timeGetTime();
        }
    }
}
}
