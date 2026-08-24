#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"



#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

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


// FUNCTION: STRONGHOLDCRUSADER 0x004800B0
void GameSynchronyState::clearGameCommandEntry(int gameCommandID)

{
if (gameCommandID < 200) {
MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(0x4f8, '\0', (void *)((int)(
this->DAT_GameCommandArray + gameCommandID)));
}
return;
}


}
}