#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"



#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {
namespace Map {

using OpenSHC::Game::GameMode2;


/* 
  Returns 1 always in editor mode. Otherwise returns SEC_MercRecruitable[param_1 - 0x38] from
   MapPropertiesState, indicating whether the mercenary unit type associated with this building
   offset is recruitable in the current map configuration.
   
   renamed by: Claude Sonnet 4.6
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004BB0B0
int MapPropertiesState::isMercRecruitableForBuildingType(int param_1)

{
int iVar1;

iVar1 = 1;
if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR) {
iVar1 = (int)this->SEC_MercRecruitable[param_1 + -0x38];
}
return iVar1;
}


}
}