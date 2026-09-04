#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"



#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace AI {

using OpenSHC::AI::AICState;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004C6D30
void AICState::wipeAICMemory()

{
AICState *destination;
int iVar1;

destination = this;
iVar1 = 20;
do {
MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(676, '\0', (void *)((int)(destination)));
destination = (AICState *)(destination->aics + 1);
iVar1 = iVar1 + -1;
} while (iVar1 != 0);
return;
}


}
}