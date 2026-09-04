#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::Game::GameMode;
    using OpenSHC::UI::Enums::MenuModalType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0046BD20
    BOOLEnum GameCore::isGameHaltingMenuOpen()
    {
        if ((DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY)
            && (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER)) {
            return FALSE;
        }
        if (DAT_MenuTextInputState::instance.currentModalDialog != OpenSHC::UI::Enums::MMT_NO_MENU) {
            return TRUE;
        }
        return (
            uint)(DAT_MenuModalComposition1::instance.activeModalDialogID == OpenSHC::UI::Enums::MMT_IN_GAME_HELP_TEXT);
    }

}
}
