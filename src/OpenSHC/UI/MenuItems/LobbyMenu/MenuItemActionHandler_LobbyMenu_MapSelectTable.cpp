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

        using OpenSHC::Commands::GameCommandType;
        using OpenSHC::UI::Enums::MenuModalType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0042B470
        void LobbyMenu::MenuItemActionHandler_LobbyMenu_MapSelectTable(int param_1, ...)
        {
            if ((((DAT_MenuModalComposition1::instance.activeModalDialogID != OpenSHC::UI::Enums::MMT_ROUNDTABLE)
                     && (DAT_MenuModalComposition1::instance.activeModalDialogID
                         != OpenSHC::UI::Enums::MMT_BASIC_AI_LORD_SELECT))
                    && (DAT_MenuModalComposition1::instance.activeModalDialogID
                        != OpenSHC::UI::Enums::MMT_EXTENDED_AI_LORD_SELECT))
                && ((DAT_GameSynchronyState::instance.isHost != FALSE
                    && (DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset + param_1
                        < DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber)))) {
                DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected = param_1;
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                    DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_CHANGE_MAP_SELECTION);
            }
        }

    }
}
}
