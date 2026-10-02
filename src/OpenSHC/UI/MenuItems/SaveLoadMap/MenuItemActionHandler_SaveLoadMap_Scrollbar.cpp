#include "../SaveLoadMap.func.hpp"

#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00492BA0
        void SaveLoadMap::MenuItemActionHandler_SaveLoadMap_Scrollbar(
            int param_1, int param_2, int* minValue, int* maxValue, int* currentValue)
        {
            switch (param_2) {
            case 1:
                *minValue = 0;
                *maxValue
                    = DAT_MenuTextInputState::instance.field32_0x74 - DAT_MenuTextInputState::instance.field36_0x84;
                *currentValue = DAT_MenuTextInputState::instance.DAT_MenuLoadGameRelativeSelectionOffset;
                return;
            case 2:
            case 3:
                DAT_MenuTextInputState::instance.DAT_MenuLoadGameRelativeSelectionOffset = *currentValue;
                return;
            case 4:
                *currentValue = DAT_MenuTextInputState::instance.DAT_MenuLoadGameRelativeSelectionOffset;
                return;
            case 5:
                if (0 < DAT_MenuTextInputState::instance.DAT_MenuLoadGameRelativeSelectionOffset) {
                    DAT_MenuTextInputState::instance.DAT_MenuLoadGameRelativeSelectionOffset
                        = DAT_MenuTextInputState::instance.DAT_MenuLoadGameRelativeSelectionOffset + -1;
                    *currentValue = DAT_MenuTextInputState::instance.DAT_MenuLoadGameRelativeSelectionOffset;
                }
                break;
            case 6:
                if (DAT_MenuTextInputState::instance.DAT_MenuLoadGameRelativeSelectionOffset
                    < DAT_MenuTextInputState::instance.field32_0x74 - DAT_MenuTextInputState::instance.field36_0x84) {
                    DAT_MenuTextInputState::instance.DAT_MenuLoadGameRelativeSelectionOffset
                        = DAT_MenuTextInputState::instance.DAT_MenuLoadGameRelativeSelectionOffset + 1;
                }
                break;
            case 7:
                *currentValue = DAT_MenuTextInputState::instance.field36_0x84 + -1;
                return;
            default:
                return;
            }
            *currentValue = DAT_MenuTextInputState::instance.DAT_MenuLoadGameRelativeSelectionOffset;
        }

    }
}
}
