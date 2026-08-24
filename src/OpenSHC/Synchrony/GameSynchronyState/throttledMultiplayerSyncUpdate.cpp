#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"





namespace OpenSHC {
namespace Synchrony {

using OpenSHC::Game::GameMode;


/* 
  WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
 */

/* 
  WARNING: Enum "DPERRInt": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00490340
void GameSynchronyState::throttledMultiplayerSyncUpdate()

{
DWORD DVar1;

if ((this->currentGameMode != OpenSHC::Game::GM_SOLITARY) &&
(this->currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER)) {
DVar1 = timeGetTime();
if (10 < DVar1 - this->field309_0x109e94) {
this->field309_0x109e94 = DVar1;
MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::sendPeriodicSyncMessages, this)();
return;
}
}
return;
}


}
}