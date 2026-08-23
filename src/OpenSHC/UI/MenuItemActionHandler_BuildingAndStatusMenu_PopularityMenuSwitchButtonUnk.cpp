#include "OpenSHC/UI.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0043F2B0
void UI::MenuItemActionHandler_BuildingAndStatusMenu_PopularityMenuSwitchButtonUnk()
{
    DAT_GameCore::instance.field80_0x144 = DAT_GameCore::instance.field80_0x144 ^ 1;
}

}
