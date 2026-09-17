#include "OpenSHC/Global.func.hpp"
#include "OpenSHC/OS.func.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0045D060
void Global::PrintToDestination(wchar_t* destination, wchar_t* format, ...)
{
    va_list args;
    va_start(args, format);
    MACRO_CALL(OpenSHC::OS_Func::__vswprintf)(destination, format, args);
}

}
