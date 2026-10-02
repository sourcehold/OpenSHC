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

        using OpenSHC::Game::GameMode;
        using OpenSHC::Game::GameMode2;

        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0043FBB0
        void BuildingAndStatusMenu::MenuItemActionHandler_BuildingAndStatusMenu_DisableFoodType(int param_1, ...)
        {
            short* psVar1;
            if ((DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY)
                || (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER)) {
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CRUSADER_TUTORIAL) {
                    MACRO_CALL(OpenSHC::UI::Helpers_Func::SetTutorialHintActiveWithTimestamp)();
                }
                psVar1 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                             .isFoodTypeBanned
                    + param_1;
                *psVar1 = *psVar1 ^ 1;
            }
        }

    }
}
}
