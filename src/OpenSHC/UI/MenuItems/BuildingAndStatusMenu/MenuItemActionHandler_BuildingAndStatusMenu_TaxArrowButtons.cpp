#include "../BuildingAndStatusMenu.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace BuildingAndStatusMenu {

            // FUNCTION: STRONGHOLDCRUSADER 0x004656A0
            void MenuItemActionHandler_BuildingAndStatusMenu_TaxArrowButtons(int action, ...)
            {
                // -2 raises the tax slider and -1 lowers it, within 0 to 11.
                switch (action) {
                case -2:
                    if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .taxesSliderUI
                        < 11) {
                        ++DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                              .taxesSliderUI;
                    }
                    break;
                case -1:
                    if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .taxesSliderUI
                        > 0) {
                        --DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                              .taxesSliderUI;
                    }
                    break;
                }
            }

        }
    }
}
}
