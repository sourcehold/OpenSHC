#include "OpenSHC/Util/Timing/Stopwatch.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Util {
    namespace Timing {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0046CEF0
        void Stopwatch::stop()
        {
            if (this->running_0x4 == FALSE) {
                return;
            }
            this->stopTime_0xc = timeGetTime();
            this->running_0x4 = FALSE;
            this->duration_0x0 = this->stopTime_0xc - this->startTime_0x8;
        }

    }
}
}
