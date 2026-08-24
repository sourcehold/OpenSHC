#include "OpenSHC/Synchrony/Actions.func.hpp"



#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace Synchrony {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004652A0
void Actions::SetBuildingProductionType(undefined4 playerID,int buildingID,ushort producedItemType,int buildingUID)

{
if (DAT_BuildingsState::instance.buildings[buildingID].uid == buildingUID) {
DAT_BuildingsState::instance.buildings[buildingID].producedItemType = producedItemType;
}
return;
}


}
}