#include "../Meta.func.hpp"

#include "OpenSHC/Global.func.hpp"

#include "OpenSHC/Globals/DAT_GameLoopStopwatch.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0059D5E0
void Meta::Destructor_Stopwatch_Gameloop()
{
    ((void(__fastcall*)(Stopwatch*))MACRO_CALL(Global_Func::DoNothing))(DAT_GameLoopStopwatch::ptr);
}

}
