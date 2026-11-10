#include "../Meta.func.hpp"

#include "OpenSHC/Global.func.hpp"

#include "OpenSHC/Globals/DAT_WindowInformation.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0059D4F0
void Meta::Destructor_0059d4f0()
{
    ((void(__fastcall*)(WindowInformation*))MACRO_CALL(Global_Func::DoNothing))(DAT_WindowInformation::ptr);
}

}
