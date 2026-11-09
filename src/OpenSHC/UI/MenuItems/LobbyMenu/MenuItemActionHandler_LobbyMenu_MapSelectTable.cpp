#include "../LobbyMenu.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x0042B470
        void LobbyMenu::MenuItemActionHandler_LobbyMenu_MapSelectTable(int param_1, ...)
        {
            if (DAT_MenuModalComposition1::instance.activeModalDialogID == OpenSHC::UI::Enums::MMT_ROUNDTABLE) {
                return;
            }
            if (DAT_MenuModalComposition1::instance.activeModalDialogID
                == OpenSHC::UI::Enums::MMT_BASIC_AI_LORD_SELECT) {
                return;
            }
            if (DAT_MenuModalComposition1::instance.activeModalDialogID
                == OpenSHC::UI::Enums::MMT_EXTENDED_AI_LORD_SELECT) {
                return;
            }
            if (!DAT_GameSynchronyState::instance.isHost) {
                return;
            }
            if ((int)DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset + param_1
                >= (int)DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber) {
                return;
            }
            DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected = param_1;
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                OpenSHC::Commands::GCT_CHANGE_MAP_SELECTION);
        }

    }
}
}
