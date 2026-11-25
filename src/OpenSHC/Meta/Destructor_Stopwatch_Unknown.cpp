#include "../Meta.func.hpp"

#include "OpenSHC/Global.func.hpp"

#include "OpenSHC/Globals/DAT_UnknownStopwatch.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0059D5F0
void Meta::Destructor_Stopwatch_Unknown()
{
    ((void(__fastcall*)(Stopwatch*))MACRO_CALL(Global_Func::DoNothing))(DAT_UnknownStopwatch::ptr);
}

}
