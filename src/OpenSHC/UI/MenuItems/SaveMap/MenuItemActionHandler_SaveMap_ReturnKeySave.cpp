#include "OpenSHC/UI/MenuItems/SaveLoadMap.func.hpp"
#include "OpenSHC/UI/MenuItems/SaveMap.func.hpp"

#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace SaveMap {

            // FUNCTION: STRONGHOLDCRUSADER 0x00494920
            void MenuItemActionHandler_SaveMap_ReturnKeySave(int param_1, ...)
            {
                int const returnPressed = DAT_UserTextHandlerState::instance.returnPressed;
                DAT_UserTextHandlerState::instance.returnPressed = 0;
                if (returnPressed != 0) {
                    MACRO_CALL(OpenSHC::UI::MenuItems::SaveLoadMap_Func::MenuItemActionHandler_SaveLoadMap_Buttons)(3);
                }
            }

        }
    }
}
}
