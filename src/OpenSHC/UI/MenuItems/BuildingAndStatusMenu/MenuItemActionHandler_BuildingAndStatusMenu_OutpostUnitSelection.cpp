#include "OpenSHC/UI.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace UI {
namespace MenuItems {
namespace BuildingAndStatusMenu {

// FUNCTION: STRONGHOLDCRUSADER 0x00466710
void MenuItemActionHandler_BuildingAndStatusMenu_OutpostUnitSelection(int bitIndex, ...)
{
    // Toggle the bit selected by the menu action in the currently selected
    // building's outpost unit-selection mask.
    DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID]
        .outpostRelatedUnk1 ^= (ushort)(1 << bitIndex);
}

}
}
}
}
