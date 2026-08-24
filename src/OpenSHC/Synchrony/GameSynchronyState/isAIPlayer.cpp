#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"





namespace OpenSHC {
namespace Synchrony {

using OpenSHC::WindowsHelper::Enums::BOOLEnum;


/* 
  WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
 */

/* 
  WARNING: Enum "DPERRInt": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:56:35.138000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004010B0
BOOLEnum GameSynchronyState::isAIPlayer(int playerID)

{
if (this->currentPlayerFullIDArray[playerID] != -1) {
return FALSE;
}
return (uint)(this->currentAIArray[playerID] != 0);
}


}
}