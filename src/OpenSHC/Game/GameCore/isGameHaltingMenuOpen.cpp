#include "../GameCore.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x0046BD20
    BOOLEnum GameCore::isGameHaltingMenuOpen()
    {
        if (DAT_GameSynchronyState::instance.currentGameMode != GM_SOLITARY
            && DAT_GameSynchronyState::instance.currentGameMode != GM_SKIRMISH_SINGLE_PLAYER) {
            return FALSE;
        }
        if (DAT_MenuTextInputState::instance.currentModalDialog != UI::Enums::MMT_NO_MENU) {
            return TRUE;
        }
        return DAT_MenuModalComposition1::instance.activeModalDialogID == UI::Enums::MMT_IN_GAME_HELP_TEXT;
    }

}
}
