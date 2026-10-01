#include "../Stopwatch.func.hpp"

namespace OpenSHC {
namespace Util {
    namespace Timing {

        // FUNCTION: STRONGHOLDCRUSADER 0x0046CED0
        void Stopwatch::start()
        {
            this->startTime_0x8 = timeGetTime();
            this->running_0x4 = TRUE;
        }

    }
}
}
