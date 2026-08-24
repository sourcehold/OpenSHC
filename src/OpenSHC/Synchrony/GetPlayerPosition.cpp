#include "OpenSHC/Synchrony.func.hpp"



#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {




/* 
  WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
 */

/* 
  WARNING: Enum "DPERRInt": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0042AC60
int Synchrony::GetPlayerPosition(int playerID)

{
byte *pbVar1;
int iVar2;

iVar2 = 0;
do {
pbVar1 = DAT_GameSynchronyState::instance.playerPositionsArray + iVar2;
iVar2 = iVar2 + 1;
if ((char)*pbVar1 + 1 == playerID) {
return iVar2;
}
} while (iVar2 < 8);
return 0;
}


}