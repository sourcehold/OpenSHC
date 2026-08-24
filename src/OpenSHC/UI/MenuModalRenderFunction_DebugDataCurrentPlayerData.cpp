#include "OpenSHC/UI.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"



#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004AAA40
void UI::MenuModalRenderFunction_DebugDataCurrentPlayerData(int x,int y,int width,int height)

{
MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::renderDebugDataCurrentPlayerData, DAT_GameState::ptr)(x, y, width, height);
return;
}


}