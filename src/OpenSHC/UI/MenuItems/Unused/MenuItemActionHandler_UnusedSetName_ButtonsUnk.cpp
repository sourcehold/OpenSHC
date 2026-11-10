#include "../Unused.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/Text/TextArrayIndexType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004267F0
        void Unused::MenuItemActionHandler_UnusedSetName_ButtonsUnk(int button, ...)
        {
            switch (button) {
            case 8:
                // "OK": confirms the title, as Return does, and goes to the main menu
                MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(
                    OpenSHC::Text::TAIT_NINE__FILTER_B);
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_MAIN_MENU, 0);
                return;
            case 25:
                // "Change Your Title, Lord?": the player types a new title
                DAT_GameCore::instance.isNameEntryActive = FALSE;
                MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(
                    OpenSHC::Text::TAIT_ZERO);
                return;
            }
        }

    }
}
}
