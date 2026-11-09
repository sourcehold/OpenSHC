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
            case 5: {
                int const taxesSliderValue
                    = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                          .taxesSliderUI;
                int* const taxesSlider
                    = &DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                           .taxesSliderUI;
                if (0 < taxesSliderValue) {
                    *taxesSlider = taxesSliderValue - 1;
                }
                *currentValue = *taxesSlider;
                return;
            }
            case 6: {
                int const taxesSliderValue
                    = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                          .taxesSliderUI;
                int* const taxesSlider
                    = &DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                           .taxesSliderUI;
                if (taxesSliderValue < 11) {
                    *taxesSlider = taxesSliderValue + 1;
                }
                *currentValue = *taxesSlider;
                break;
            }
            default:
                break;
            }
        }

    }
}
}
