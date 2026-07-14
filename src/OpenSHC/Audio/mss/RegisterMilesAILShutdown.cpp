#include "../mss.func.hpp"

#include "OpenSHC/OS.func.hpp"

#include "Mss32.h"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        void __cdecl AIL_shutdown_proxy() { AIL_shutdown(); }

        // FUNCTION: STRONGHOLDCRUSADER 0x0057E160
        int __cdecl RegisterMilesAILShutdown()
        {
            MACRO_CALL(OS_Func::_atexit)(AIL_shutdown_proxy);
            return 0;
        }

    }
}
}
