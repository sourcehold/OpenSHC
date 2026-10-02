#include "../GameplayOptions.func.hpp"

#include "OpenSHC/UI/MenuTextInputState.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00493D80
        void GameplayOptions::MenuItemActionHandler_GameplayOptions_Buttons(int param_1, ...)
        {
            switch (param_1) {
            case 0x11:
                goto switchD_00493d93_caseD_11;
            case 0x12:
                DAT_GameCore::instance.gameSpeedLevel = DAT_MenuTextInputState::instance.field12_0x30;
                DAT_GameCore::instance.settingBubbleHelp = DAT_MenuTextInputState::instance.field14_0x38;
                DAT_GameCore::instance.unusedOption1 = DAT_MenuTextInputState::instance.field15_0x3c;
            switchD_00493d93_caseD_11:
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::popModalDialog, DAT_MenuTextInputState::ptr)();
                return;
            default:
                return;
            case 0x21:
                DAT_MenuTextInputState::instance.field14_0x38 = DAT_MenuTextInputState::instance.field14_0x38 ^ 1;
                return;
            case 0x34:
                DAT_MenuTextInputState::instance.field15_0x3c = DAT_MenuTextInputState::instance.field15_0x3c == 0;
            }
        }

    }
}
}
