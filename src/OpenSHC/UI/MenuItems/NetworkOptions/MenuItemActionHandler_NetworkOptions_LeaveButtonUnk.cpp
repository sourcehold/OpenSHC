#include "OpenSHC/UI/MenuItems/NetworkOptions.func.hpp"
#include "OpenSHC/UI/MenuTextInputState.func.hpp"

#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace NetworkOptions {

            // FUNCTION: STRONGHOLDCRUSADER 0x004941F0
            void MenuItemActionHandler_NetworkOptions_LeaveButtonUnk(int action, ...)
            {
                if (action == 17) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::MenuTextInputState_Func::popModalDialog, DAT_MenuTextInputState::ptr)();
                }
            }

        }
    }
}
}
