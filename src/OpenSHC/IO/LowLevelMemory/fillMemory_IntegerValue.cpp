#include "OpenSHC/IO/LowLevelMemory.func.hpp"





namespace OpenSHC {
namespace IO {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00471860
void LowLevelMemory::fillMemory_IntegerValue(size_t size,int value,void *destination)

{
this->size = size;
this->value = value;
this->destination = destination;
MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_setMemoryToValue_0x100, this)();
MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_setMemoryToValue_0x010, this)();
MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_setMemoryToValue_0x004, this)();
return;
}


}
}