#include "OpenSHC/IO/LowLevelMemory.func.hpp"





namespace OpenSHC {
namespace IO {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00471890
void LowLevelMemory::fillMemory_ShortValue(size_t size,ushort shortValue,void *dst)

{
this->value = (uint)shortValue * 0x10001;
this->size = size;
this->destination = dst;
MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_setMemoryToValue_0x100, this)();
MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_setMemoryToValue_0x010, this)();
MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_setMemoryToValue_0x002, this)();
return;
}


}
}