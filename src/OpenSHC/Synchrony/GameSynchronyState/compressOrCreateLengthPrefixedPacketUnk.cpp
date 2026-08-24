#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/IO/DecoderState.func.hpp"



#include "OpenSHC/Globals/DAT_DecoderState.hpp"

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


// FUNCTION: STRONGHOLDCRUSADER 0x0047E7E0
int GameSynchronyState::compressOrCreateLengthPrefixedPacketUnk(int size,char *src,void *dst)

{
int iVar1;

iVar1 = MACRO_CALL_MEMBER(OpenSHC::IO::DecoderState_Func::compressRLE, DAT_DecoderState::ptr)(src, dst, size);
return iVar1;
}


}
}