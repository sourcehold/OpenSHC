#include "OpenSHC/UI.func.hpp"

#include "OpenSHC/Globals/DAT_UnknownTime_01.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x004B9610
void UI::CaptureCurrentTimeToUnknownTime01() { DAT_UnknownTime_01::instance = timeGetTime(); }

}
