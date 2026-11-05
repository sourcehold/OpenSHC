#include "../Helpers.func.hpp"

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_00df33ac.hpp"
#include "OpenSHC/Globals/DAT_HasNoQueryPerformanceFrequency.hpp"
#include "OpenSHC/Globals/DAT_PerformanceCounterFrequency.hpp"
#include "OpenSHC/Globals/FLOAT_Between1And5.hpp"
#include "OpenSHC/Globals/FLOAT_Between1and0dot2.hpp"
#include "OpenSHC/Globals/TIME_PreviousQuery.hpp"
#include "OpenSHC/Globals/TIME_QueryMargin.hpp"

namespace OpenSHC {
namespace UI {

    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0046CF90
    BOOLEnum Helpers::TicksSinceCounterStart()
    {
        // Wait until at least TIME_QueryMargin ticks have passed since the last call.
        DWORD now = DAT_00df33ac::instance;
        // The exit test stays at the end: a while loop would test before reading the counter, and loses the match.
        for (;;) {
            if (!DAT_HasNoQueryPerformanceFrequency::instance) {
                QueryPerformanceCounter(DAT_PerformanceCounterFrequency::ptr);
                now = DAT_PerformanceCounterFrequency::instance.LowPart;
                DAT_00df33ac::instance = now;
            }
            // Compared with 1, as the binary does, not tested for non-zero.
            if (DAT_HasNoQueryPerformanceFrequency::instance == TRUE) {
                now = timeGetTime();
                DAT_00df33ac::instance = now;
            }
            if (now - TIME_PreviousQuery::instance >= TIME_QueryMargin::instance) {
                break;
            }
        }
        FLOAT_Between1and0dot2::instance = (float)TIME_QueryMargin::instance / (now - TIME_PreviousQuery::instance);
        TIME_PreviousQuery::instance = now;
        // The limits are 0.95f and 0.2f compared as doubles, which is what the binary's constants hold.
        if (FLOAT_Between1and0dot2::instance > (double)0.95f) {
            FLOAT_Between1and0dot2::instance = 1.0f;
        }
        if (FLOAT_Between1and0dot2::instance < (double)0.2f) {
            FLOAT_Between1and0dot2::instance = 0.2f;
        }
        FLOAT_Between1And5::instance = 1.0 / FLOAT_Between1and0dot2::instance;
        return TRUE;
    }

}
}
