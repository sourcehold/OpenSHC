#include "OpenSHC/UI.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"



#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {

using OpenSHC::Game::GameMode2;
using OpenSHC::Commands::GameCommandType;


/* 
  WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
 */

/* 
  WARNING: Enum "DPERRInt": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004660B0
void UI::MenuItemActionHandler_BuildingAndStatusMenu_BuildingSleep()

{
if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CRUSADER_TUTORIAL) {
MACRO_CALL(OpenSHC::UI_Func::SetTutorialHintActiveWithTimestamp)();
return;
}
DAT_GameSynchronyState::instance.DAT_GameCommandParam0 =
(int)(short)DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID].
buildingType;
MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_BUILDING_SLEEP);
return;
}


}