#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"



#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {
namespace Map {
namespace Units {

using OpenSHC::Map::Units::Behavior::UnitStanceEnum;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00522C20
void TribesState::setUnitStance(int tribeID,UnitStanceEnum unitStance)

{
this->tribes[tribeID].unitStance = (undefined2)unitStance;
DAT_GameCore::instance.countdown = 1;
return;
}


}
}
}