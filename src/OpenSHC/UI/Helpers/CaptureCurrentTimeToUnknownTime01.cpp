#include "OpenSHC/UI/Helpers.func.hpp"

#include "OpenSHC/Globals/DAT_UnknownTime_01.hpp"

namespace OpenSHC {
namespace UI {
    namespace Helpers {

        // FUNCTION: STRONGHOLDCRUSADER 0x004B9610
        void CaptureCurrentTimeToUnknownTime01() { DAT_UnknownTime_01::instance = timeGetTime(); }

    }
}
}
