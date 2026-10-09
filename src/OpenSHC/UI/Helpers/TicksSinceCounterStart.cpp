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
    undefined4 Helpers::TicksSinceCounterStart()
    {
        undefined4 _now = DAT_00df33ac::instance;
        do {
            if (!DAT_HasNoQueryPerformanceFrequency::instance) {
                QueryPerformanceCounter(DAT_PerformanceCounterFrequency::ptr);
                DAT_00df33ac::instance = DAT_PerformanceCounterFrequency::instance.LowPart;
                _now = DAT_PerformanceCounterFrequency::instance.LowPart;
            }
            if (DAT_HasNoQueryPerformanceFrequency::instance == TRUE) {
                _now = timeGetTime();
                DAT_00df33ac::instance = _now;
            }
        } while (_now - TIME_PreviousQuery::instance < TIME_QueryMargin::instance);
        float fVar1 = (float)TIME_QueryMargin::instance;
        if (TIME_QueryMargin::instance < 0) {
            fVar1 = fVar1 + 4.2949673e+09;
        }
        float fVar2 = (float)(int)(_now - TIME_PreviousQuery::instance);
        if ((int)(_now - TIME_PreviousQuery::instance) < 0) {
            fVar2 = fVar2 + 4.2949673e+09;
        }
        FLOAT_Between1and0dot2::instance = fVar1 / fVar2;
        TIME_PreviousQuery::instance = _now;
        if (0.95 < FLOAT_Between1and0dot2::instance) {
            FLOAT_Between1and0dot2::instance = 1.0;
        }
        if (FLOAT_Between1and0dot2::instance < 0.2) {
            FLOAT_Between1and0dot2::instance = 0.2;
        }
        FLOAT_Between1And5::instance = 1.0 / FLOAT_Between1and0dot2::instance;
        return (undefined4)(1);
    }

}
}
