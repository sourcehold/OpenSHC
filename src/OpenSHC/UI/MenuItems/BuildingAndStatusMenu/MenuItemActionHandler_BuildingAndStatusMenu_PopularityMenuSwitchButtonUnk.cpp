#include "OpenSHC/UI/MenuItems/BuildingAndStatusMenu.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace BuildingAndStatusMenu {

            // FUNCTION: STRONGHOLDCRUSADER 0x0043F2B0
            void MenuItemActionHandler_BuildingAndStatusMenu_PopularityMenuSwitchButtonUnk()
            {
                DAT_GameCore::instance.field77_0x144 ^= 1;
            }

        }
    }
}
}
