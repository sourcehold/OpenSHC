#include "../Stopwatch.func.hpp"

namespace OpenSHC {
namespace Util {
    namespace Timing {

        // FUNCTION: STRONGHOLDCRUSADER 0x0046CEC0
        Stopwatch* Stopwatch::Constructor_Stopwatch()
        {
            this->running_0x4 = FALSE;
            this->duration_0x0 = 0;
            return this;
        }

    }
}
}
