#include "OpenSHC/UI/MenuItems/BuildingAndStatusMenu.func.hpp"

#include "OpenSHC/Globals/DAT_00b95b68.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace BuildingAndStatusMenu {

            // FUNCTION: STRONGHOLDCRUSADER 0x0043FC80
            void MenuItemActionHandler_BuildingAndStatusMenu_ArmySwitchButton()
            {
                DAT_00b95b68::instance += 1;
                if ((int)DAT_00b95b68::instance > 2) {
                    DAT_00b95b68::instance = 0;
                }
            }

        }
    }
}
}
