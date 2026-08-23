#include "OpenSHC/Util/Timing/Stopwatch.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Util {
    namespace Timing {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0046CED0
        void Stopwatch::start()
        {
            DWORD _currentTime = timeGetTime();
            this->startTime_0x8 = _currentTime;
            this->running_0x4 = TRUE;
        }

    }
}
}
