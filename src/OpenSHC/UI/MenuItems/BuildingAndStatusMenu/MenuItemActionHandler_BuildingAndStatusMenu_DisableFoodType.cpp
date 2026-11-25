#include "../BuildingAndStatusMenu.func.hpp"

#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x0043FBB0
        void BuildingAndStatusMenu::MenuItemActionHandler_BuildingAndStatusMenu_DisableFoodType(int foodType, ...)
        {
            if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY
                && DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
                return;
            }
            if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CRUSADER_TUTORIAL) {
                MACRO_CALL(OpenSHC::UI::Helpers_Func::SetTutorialHintActiveWithTimestamp)();
                return;
            }
            DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .isFoodTypeBanned[foodType] ^= 1;
        }

    }
}
}
