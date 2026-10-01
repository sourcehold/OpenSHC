#include "OpenSHC/UI/BottomLeftTextDisplayState.func.hpp"
#include "OpenSHC/UI/MenuItems/General.func.hpp"

#include "OpenSHC/Globals/DAT_BottomLeftTextDisplayState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace General {

            // FUNCTION: STRONGHOLDCRUSADER 0x004F6A60
            void MenuItemActionHandler_General_DisplayConditionalText(int textID, ...)
            {
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::BottomLeftTextDisplayState_Func::renderCurrentlyDisplayedTextConstructionCost,
                    DAT_BottomLeftTextDisplayState::ptr)(textID);
            }

        }
    }
}
}
