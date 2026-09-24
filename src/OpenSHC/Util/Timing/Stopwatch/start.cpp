#include "OpenSHC/Util/Timing/Stopwatch.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Util {
    namespace Timing {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0046CED0
        void Stopwatch::start()
        {
            this->startTime_0x8 = timeGetTime();
            this->running_0x4 = TRUE;
        }

    }
}
}
