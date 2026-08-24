#include "OpenSHC/UI.func.hpp"

#include "OpenSHC/Globals/DAT_ButtonUnknownZero.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {

/*
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */

// FUNCTION: STRONGHOLDCRUSADER 0x00439390
void UI::MenuItemRenderFunction_BuildMenu_CurrentlySelectedTroopsDeselectHelper(int param_1, ...)

{
    if ((DAT_UnitsState::instance.nHasOwnedUnitInSelection == 0)
        || (DAT_ButtonUnknownZero::instance = 0, DAT_UnitsState::instance.selectionSlots[param_1 + -0x14] == -1)) {
        DAT_ButtonUnknownZero::instance = 1;
    }
    return;
}

}
