#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"





namespace OpenSHC {
namespace Map {
namespace Navigation {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004A94E0
void PathFindingState::clearAllClimbData()

{
int iVar1;

iVar1 = 0;
this->numberOfClimbTeleports = 0;
do {
MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::clearClimbData, this)(iVar1);
iVar1 = iVar1 + 1;
} while (iVar1 < 200);
return;
}


}
}
}