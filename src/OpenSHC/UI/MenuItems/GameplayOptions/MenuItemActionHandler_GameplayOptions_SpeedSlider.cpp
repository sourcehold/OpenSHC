#include "../GameplayOptions.func.hpp"

#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Game::GameMode;

        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00491FD0
        void GameplayOptions::MenuItemActionHandler_GameplayOptions_SpeedSlider(
            int param_1, int param_2, int* minValue, int* maxValue, int* currentValue)
        {
            if ((DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY)
                && (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER)) {
                *minValue = 0x14;
                *maxValue = 0x5a;
                *currentValue = DAT_GameSynchronyState::instance.skirmishGameSpeedLevel;
            }
            switch (param_2) {
            case 1:
                *minValue = 0x14;
                *maxValue = 0x5a;
                *currentValue = DAT_MenuTextInputState::instance.field12_0x30;
                return;
            case 2:
            case 3:
                DAT_MenuTextInputState::instance.field12_0x30 = *currentValue;
                return;
            case 5:
                *currentValue = *currentValue + -1;
                DAT_MenuTextInputState::instance.field12_0x30 = *currentValue;
                return;
            case 6:
                *currentValue = *currentValue + 1;
                DAT_MenuTextInputState::instance.field12_0x30 = *currentValue;
            }
        }

    }
}
}
