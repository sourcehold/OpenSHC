#include "OpenSHC/Synchrony/Actions.func.hpp"



#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Synchrony {




/* 
  WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
 */

/* 
  WARNING: Enum "DPERRInt": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004285C0
void Actions::RemovePositionOfPlayer(int playerID)

{
int iVar1;

iVar1 = 0;
do {
if ((char)DAT_GameSynchronyState::instance.playerPositionsArray[iVar1] + 1 == playerID) {
/* 
  -10, make spot empty
 */

DAT_GameSynchronyState::instance.playerPositionsArray[iVar1] = 0xf6;
}
iVar1 = iVar1 + 1;
} while (iVar1 < 8);
return;
}


}
}