#include "../GameplayOptions.func.hpp"

#include "OpenSHC/UI/MenuTextInputState.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        // FUNCTION: STRONGHOLDCRUSADER 0x00493D80
        void GameplayOptions::MenuItemActionHandler_GameplayOptions_Buttons(int button, ...)
        {
            switch (button) {
            case 33:
                // "Bubble Help"
                DAT_MenuTextInputState::instance.pendingSettingBubbleHelp ^= 1;
                return;
            case 52:
                // "Extreme Scoring"
                DAT_MenuTextInputState::instance.pendingUnusedOption1
                    = !DAT_MenuTextInputState::instance.pendingUnusedOption1;
                return;
            case 18:
                // "Apply": the pending settings go to the game, then the dialog closes as with "Back"
                DAT_GameCore::instance.gameSpeedLevel = DAT_MenuTextInputState::instance.pendingGameSpeedLevel;
                DAT_GameCore::instance.settingBubbleHelp = DAT_MenuTextInputState::instance.pendingSettingBubbleHelp;
                DAT_GameCore::instance.unusedOption1 = DAT_MenuTextInputState::instance.pendingUnusedOption1;
                // falls through
            case 17:
                // "Back"
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::popModalDialog, DAT_MenuTextInputState::ptr)();
                return;
            }
        }

    }
}
}
