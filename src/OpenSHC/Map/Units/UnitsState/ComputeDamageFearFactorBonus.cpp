#include "OpenSHC/Map/Units/UnitsState.func.hpp"



#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
namespace Units {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x005311F0
int UnitsState::ComputeDamageFearFactorBonus(int damage,int playerID)

{
return ((DAT_GameState::instance.playerDataArray[playerID].fearFactorLevel + 0x14) * damage * 5) / 100;
}


}
}
}