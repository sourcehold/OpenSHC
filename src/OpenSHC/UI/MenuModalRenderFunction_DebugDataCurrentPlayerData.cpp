#include "OpenSHC/UI.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x004AAA40
void UI::MenuModalRenderFunction_DebugDataCurrentPlayerData(int x,int y,int width,int height)
{
MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::renderDebugDataCurrentPlayerData, DAT_GameState::ptr)(x, y, width, height);
}

}
