#include "../Meta.func.hpp"

#include "OpenSHC/Global.func.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0059D590
void Meta::Destructor_0059d590()
{
    ((void(__fastcall*)(LowLevelMemory*))MACRO_CALL(Global_Func::DoNothing))(DAT_LowLevelMemory::ptr);
}

}
