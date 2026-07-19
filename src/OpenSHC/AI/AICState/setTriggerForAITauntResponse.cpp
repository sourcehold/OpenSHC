#include "OpenSHC/AI/AICState.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D1090
    void AICState::setTriggerForAITauntResponse()
    {
        BOOLEnum BVar1 = MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)();
        if (BVar1 != FALSE) {
            this->aiTauntResponseTimeWindow = timeGetTime();
        }
    }
}
}
