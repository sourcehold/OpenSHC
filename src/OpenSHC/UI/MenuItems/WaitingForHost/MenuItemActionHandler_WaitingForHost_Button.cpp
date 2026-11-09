#include "../WaitingForHost.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using UI::Enums::MenuModalType;
        using UI::Enums::MenuViewType;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0047E3E0
        void WaitingForHost::MenuItemActionHandler_WaitingForHost_Button(int param_1, ...)
        {
            if (param_1 == 3) {
                MACRO_CALL_MEMBER(
                    Synchrony::GameSynchronyState_Func::disconnectDPlay, DAT_GameSynchronyState::ptr)();
                MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition1::ptr)(UI::Enums::MMT_NONE, FALSE);
                MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    UI::Enums::MVT_MAIN_MENU, 0);
                MACRO_CALL_MEMBER(Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
            }
        }

    }
}
}
