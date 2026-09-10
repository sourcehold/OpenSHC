#include "OpenSHC/UI.func.hpp"

#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace SaveMap {

            // FUNCTION: STRONGHOLDCRUSADER 0x00494920
            void MenuItemActionHandler_SaveMap_ReturnKeySave(int param_1, ...)
            {
                bool bVar1;

                bVar1 = DAT_UserTextHandlerState::instance.returnPressed != 0;
                DAT_UserTextHandlerState::instance.returnPressed = 0;
                if (bVar1) {
                    MACRO_CALL(OpenSHC::UI_Func::MenuItemActionHandler_SaveLoadMap_Buttons)(3);
                    return;
                }
            }

        }
    }
}
}
