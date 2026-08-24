#include "OpenSHC/IO/LowLevelMemory.func.hpp"





namespace OpenSHC {
namespace IO {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004718C0
void LowLevelMemory::fillMemory_ByteValue(size_t size,uchar value,void *destination)

{
this->value = (uint)value * 0x1010101;
this->size = size;
this->destination = destination;
MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_setMemoryToValue_0x100, this)();
MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_setMemoryToValue_0x010, this)();
MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_setMemoryToValue_0x001, this)();
return;
}


}
}