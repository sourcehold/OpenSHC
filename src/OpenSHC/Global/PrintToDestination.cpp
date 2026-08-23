#include "OpenSHC/Global.func.hpp"
#include "OpenSHC/OS.func.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0045D060
void Global::PrintToDestination(wchar_t* destination, wchar_t* format, va_list args)
{
    // fixme: The calls that call PrintToDestination() use 2, 3, or 4 arguments, but the original assembly
    // always uses add esp, 0xc suggesting three parameters. Currently this optimizes to a jump directly.
    MACRO_CALL(OpenSHC::OS_Func::__vswprintf)(destination, format, args);
}

}
