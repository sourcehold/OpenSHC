#include "../GameplayOptions.func.hpp"

#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x00491FD0
        void GameplayOptions::MenuItemActionHandler_GameplayOptions_SpeedSlider(
            int param_1, int param_2, int* minValue, int* maxValue, int* currentValue)
        {
            if ((DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY)
                && (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER)) {
                *minValue = 20;
                *maxValue = 90;
                *currentValue = DAT_GameSynchronyState::instance.skirmishGameSpeedLevel;
                return;
            }
            switch (param_2) {
            case 1:
                *minValue = 20;
                *maxValue = 90;
                *currentValue = DAT_MenuTextInputState::instance.pendingGameSpeedLevel;
                return;
            case 2:
            case 3:
                DAT_MenuTextInputState::instance.pendingGameSpeedLevel = *currentValue;
                return;
            case 5:
                --*currentValue;
                DAT_MenuTextInputState::instance.pendingGameSpeedLevel = *currentValue;
                return;
            case 6:
                ++*currentValue;
                DAT_MenuTextInputState::instance.pendingGameSpeedLevel = *currentValue;
            }
        }

    }
}
}
