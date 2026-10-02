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
        // FUNCTION: STRONGHOLDCRUSADER 0x00465560
        void BuildingAndStatusMenu::MenuItemActionHandler_BuildingAndStatusMenu_TaxSlider(
            int param_1, int param_2, int* minValue, int* maxValue, int* currentValue)
        {
            int* piVar1;
            int iVar2;
            switch (param_2) {
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
            case 5:
                iVar2 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .taxesSliderUI;
                piVar1 = &DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                              .taxesSliderUI;
                if (0 < iVar2) {
                    *piVar1 = iVar2 + -1;
                }
                *currentValue = *piVar1;
                return;
            case 6:
                iVar2 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .taxesSliderUI;
                piVar1 = &DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                              .taxesSliderUI;
                if (iVar2 < 0xb) {
                    *piVar1 = iVar2 + 1;
                }
                *currentValue = *piVar1;
                break;
            default:
                break;
            }
        }

    }
}
}
