#include "OpenSHC/UI.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {
namespace UI {
namespace MenuItems {
namespace BuildingAndStatusMenu {

// FUNCTION: STRONGHOLDCRUSADER 0x0043A850
void MenuItemActionHandler_BuildingAndStatusMenu_Unknown_Countdown() { DAT_GameCore::instance.countdown = 1; }

}
}
}
}
