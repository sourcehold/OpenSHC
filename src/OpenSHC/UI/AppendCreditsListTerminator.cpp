#include "OpenSHC/UI.func.hpp"

#include "OpenSHC/Globals/DAT_ARRAY_00eb9b68.hpp"
#include "OpenSHC/Globals/DAT_UnknownBinkCount.hpp"

namespace OpenSHC {

/*
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */

// FUNCTION: STRONGHOLDCRUSADER 0x004DA810
void UI::AppendCreditsListTerminator()

{
    if (DAT_UnknownBinkCount::instance < 288) {
        DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].field0_0x0 = 0x20;
        DAT_UnknownBinkCount::instance = DAT_UnknownBinkCount::instance + 1;
    }
    return;
}

}
