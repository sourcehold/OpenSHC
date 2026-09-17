#include "OpenSHC/UI.func.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace BuildingAndStatusMenu {

            // FUNCTION: STRONGHOLDCRUSADER 0x0043FCA0
            void MenuItemRenderFunction_BuildingAndStatusMenu_ArmyStatusSwitchButton()
            {
                MACRO_CALL(OpenSHC::UI_Func::
                        MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
            }

        }
    }
}
}
