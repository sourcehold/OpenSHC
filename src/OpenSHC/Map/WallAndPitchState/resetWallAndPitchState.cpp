#include "OpenSHC/Map/WallAndPitchState.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"



#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_UIDragDropDefinedData.hpp"

namespace OpenSHC {
namespace Map {

using OpenSHC::Game::GameMode2;
using OpenSHC::WindowsHelper::Enums::BOOLEnum;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00500C80
void WallAndPitchState::resetWallAndPitchState()

{
if ((DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SKIRMISH_AND_MULTIPLAYER) &&
(DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SIEGE_THAT)) {
this->state = 4;
this->countdown = 400;
this->index = 0;
this->counter = 0;
DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial = TRUE;
}
return;
}


}
}