#include "../BuildingAndStatusMenu.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x00465560
        void BuildingAndStatusMenu::MenuItemActionHandler_BuildingAndStatusMenu_TaxSlider(
            int unused, int scrollbarEvent, int* minValue, int* maxValue, int* currentValue)
        {
            switch (scrollbarEvent) {
            case 1:
                *minValue = 0;
                *maxValue = 11;
                // falls through: the first event also reads the current value
            case 4:
                *currentValue
                    = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                          .taxesSliderUI;
                return;
            case 2:
            case 3:
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .taxesSliderUI = *currentValue;
                return;
            case 5:
                if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .taxesSliderUI
                    > 0) {
                    --DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                          .taxesSliderUI;
                }
                *currentValue
                    = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                          .taxesSliderUI;
                return;
            case 6:
                if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .taxesSliderUI
                    < 11) {
                    ++DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                          .taxesSliderUI;
                }
                *currentValue
                    = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                          .taxesSliderUI;
                return;
            }
        }

    }
}
}
