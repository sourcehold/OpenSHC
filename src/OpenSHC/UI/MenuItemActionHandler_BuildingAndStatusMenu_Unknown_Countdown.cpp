#include "OpenSHC/UI.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0043A850
void UI::MenuItemActionHandler_BuildingAndStatusMenu_Unknown_Countdown() { DAT_GameCore::instance.countdown = 1; }

}
