#include "OpenSHC/Map/Buildings.func.hpp"



#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace Map {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004184D0
void Buildings::UpdateParadeGround3()

{
int iVar1;

iVar1 = DAT_CurrentBuildingID::instance;
DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 1;
DAT_BuildingsState::instance.buildings[iVar1].animationIncrement = 1;
DAT_BuildingsState::instance.buildings[iVar1].animationFrame = 0x1f;
return;
}


}
}