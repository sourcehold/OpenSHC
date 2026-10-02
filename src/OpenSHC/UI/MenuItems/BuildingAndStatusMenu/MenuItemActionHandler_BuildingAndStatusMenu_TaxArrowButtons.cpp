#include "../BuildingAndStatusMenu.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004656A0
        void BuildingAndStatusMenu::MenuItemActionHandler_BuildingAndStatusMenu_TaxArrowButtons(int param_1, ...)
        {
            int iVar1;
            if (param_1 == -2) {
                iVar1 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .taxesSliderUI;
                if (iVar1 < 0xb) {
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .taxesSliderUI = iVar1 + 1;
                }
            } else if (param_1 == -1) {
                iVar1 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .taxesSliderUI;
                if (0 < iVar1) {
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .taxesSliderUI = iVar1 + -1;
                }
            }
        }

    }
}
}
