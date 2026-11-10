#include "../Meta.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0059D5A0
void Meta::Destructor_GameCoreAndRendering()
{
    MACRO_CALL_MEMBER(Game::GameCore_Func::setViewOnExitUnk, DAT_GameCore::ptr)();
}

}
