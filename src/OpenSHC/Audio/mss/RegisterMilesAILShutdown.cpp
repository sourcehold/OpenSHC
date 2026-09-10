#include "../mss.func.hpp"

#include "OpenSHC/OS.func.hpp"

#include "Mss32.h"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        void AIL_shutdown_proxy() { AIL_shutdown(); }

        // FUNCTION: STRONGHOLDCRUSADER 0x0057E160
        int RegisterMilesAILShutdown()
        {
            MACRO_CALL(OS_Func::_atexit)(AIL_shutdown_proxy);
            return 0;
        }

    }
}
}
