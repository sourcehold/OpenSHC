#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"



#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace Map {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00419340
void Buildings::UpdateBadBuildingRackFlogging()

{
int buildingID;

buildingID = DAT_CurrentBuildingID::instance;
DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 0;
DAT_BuildingsState::instance.buildings[buildingID].displayOwnerFlag = 0;
MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(buildingID);
return;
}


}
}