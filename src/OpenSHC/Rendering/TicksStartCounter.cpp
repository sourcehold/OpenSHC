#include "../Rendering.func.hpp"

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_HasNoQueryPerformanceFrequency.hpp"
#include "OpenSHC/Globals/DAT_PerformanceCounterFrequency.hpp"
#include "OpenSHC/Globals/FLOAT_Between1And5.hpp"
#include "OpenSHC/Globals/FLOAT_Between1and0dot2.hpp"
#include "OpenSHC/Globals/TIME_PreviousQuery.hpp"
#include "OpenSHC/Globals/TIME_QueryMargin.hpp"

namespace OpenSHC {

using WindowsHelper::Enums::BOOLEnum;

// FUNCTION: STRONGHOLDCRUSADER 0x0046CF10
void Rendering::TicksStartCounter()
{
    BOOL _success = QueryPerformanceFrequency(DAT_PerformanceCounterFrequency::ptr);
    if (!_success) {
        DAT_HasNoQueryPerformanceFrequency::instance = TRUE;
        TIME_QueryMargin::instance = 0x10;
        TIME_PreviousQuery::instance = timeGetTime();
        FLOAT_Between1and0dot2::instance = 1.0;
        FLOAT_Between1And5::instance = 1.0;
    }
    TIME_QueryMargin::instance = DAT_PerformanceCounterFrequency::instance.LowPart / 0x3c;
    DAT_HasNoQueryPerformanceFrequency::instance = FALSE;
    QueryPerformanceCounter(DAT_PerformanceCounterFrequency::ptr);
    TIME_PreviousQuery::instance = DAT_PerformanceCounterFrequency::instance.LowPart;
    FLOAT_Between1and0dot2::instance = 1.0;
    FLOAT_Between1And5::instance = 1.0;
}

}
