#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Util/Timing/Stopwatch.func.hpp"

#include "OpenSHC/Globals/DAT_GameLoopStopwatch.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C920
    void Init::Constructor_Stopwatch_Gameloop()
    {
        MACRO_CALL_MEMBER(Util::Timing::Stopwatch_Func::Constructor_Stopwatch, DAT_GameLoopStopwatch::ptr)();
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_Stopwatch_Gameloop::get());
    }

}
}
