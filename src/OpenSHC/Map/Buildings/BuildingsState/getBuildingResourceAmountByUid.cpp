#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"





namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Game::Resources::ResourceType;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00409330
undefined4 BuildingsState::getBuildingResourceAmountByUid(int buildingID,int param_2,ResourceType param_3)

{
if (this->buildings[buildingID].uid != param_2) {
return(undefined4)( 0);
}
return(undefined4)( this->buildings[buildingID].resources[param_3]);
}


}
}
}