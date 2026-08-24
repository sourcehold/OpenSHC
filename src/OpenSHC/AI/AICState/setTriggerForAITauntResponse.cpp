#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/Game/GameCore.func.hpp"



#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {
namespace AI {

using OpenSHC::WindowsHelper::Enums::BOOLEnum;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004D1090
void AICState::setTriggerForAITauntResponse()

{
BOOLEnum BVar1;

BVar1 = MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)();
if (BVar1 != FALSE) {
this->aiTauntResponseTimeWindow = timeGetTime();
}
return;
}


}
}