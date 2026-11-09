#include "../IdentityOptions.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/MenuTextInputState.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x00493D30
        void IdentityOptions::MenuItemActionHandler_IdentityOptions_Confirm(int button, ...)
        {
            if (button == 17) {
                DAT_UserTextHandlerState::instance.allowUserTextInput = 0;
                MACRO_CALL_MEMBER(Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(9);
                DAT_UserTextHandlerState::instance.allowUserTextInput = 1;
                MACRO_CALL_MEMBER(UI::MenuTextInputState_Func::popModalDialog, DAT_MenuTextInputState::ptr)();
                if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY) {
                    MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                        Commands::GCT_UNKNOWN_96);
                }
            }
        }

    }
}
}
