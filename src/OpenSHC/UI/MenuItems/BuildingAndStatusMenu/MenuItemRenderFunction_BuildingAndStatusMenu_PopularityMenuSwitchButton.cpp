#include "OpenSHC/UI/MenuItems/BuildingAndStatusMenu.func.hpp"
#include "OpenSHC/UI/MenuItems/General.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentButtonGmDataIndex.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace BuildingAndStatusMenu {

            // FUNCTION: STRONGHOLDCRUSADER 0x0043F2C0
            void MenuItemRenderFunction_BuildingAndStatusMenu_PopularityMenuSwitchButton(int param_1, ...)
            {
                if (DAT_GameCore::instance.field78_0x148 == 1) {
                    return;
                }
                if (DAT_GameCore::instance.field77_0x144 == 1) {
                    DAT_CurrentButtonGmDataIndex::instance = 0x73;
                }
                MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                        MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
            }

        }
    }
}
}
