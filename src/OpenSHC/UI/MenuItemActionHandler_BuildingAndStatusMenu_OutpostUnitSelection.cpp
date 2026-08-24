#include "OpenSHC/UI.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {

/*
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */

// FUNCTION: STRONGHOLDCRUSADER 0x00466710
void UI::MenuItemActionHandler_BuildingAndStatusMenu_OutpostUnitSelection(int param_1, ...)

{
    short* psVar1;

    psVar1 = &DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID]
                  .outpostRelatedUnk1;
    *psVar1 = *psVar1 ^ (ushort)(1 << ((byte)param_1 & 0x1f));
    return;
}

}
