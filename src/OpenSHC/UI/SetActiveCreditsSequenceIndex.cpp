#include "OpenSHC/UI.func.hpp"

#include "OpenSHC/Globals/DAT_00ed3120.hpp"
#include "OpenSHC/Globals/DAT_00ed3124.hpp"

namespace OpenSHC {

/*
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */

// FUNCTION: STRONGHOLDCRUSADER 0x004D9270
void __cdecl UI::SetActiveCreditsSequenceIndex(undefined4 param_1)

{
    DAT_00ed3124::instance = param_1;
    DAT_00ed3120::instance = 0;
    return;
}

}
