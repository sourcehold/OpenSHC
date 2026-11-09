#include "../SaveLoadMap.func.hpp"

#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x00492BA0
        void SaveLoadMap::MenuItemActionHandler_SaveLoadMap_Scrollbar(
            int param_1, int param_2, int* minValue, int* maxValue, int* currentValue)
        {
            switch (param_2) {
            case 1:
                *minValue = 0;
                *maxValue
                    = DAT_MenuTextInputState::instance.fileListEntryCount - DAT_MenuTextInputState::instance.fileListVisibleRowCount;
                *currentValue = DAT_MenuTextInputState::instance.menuLoadGameRelativeSelectionOffset;
                return;
            case 2:
            case 3:
                DAT_MenuTextInputState::instance.menuLoadGameRelativeSelectionOffset = *currentValue;
                return;
            case 4:
                *currentValue = DAT_MenuTextInputState::instance.menuLoadGameRelativeSelectionOffset;
                return;
            case 7:
                *currentValue = DAT_MenuTextInputState::instance.fileListVisibleRowCount + -1;
                return;
            case 5:
                if (0 < (int)DAT_MenuTextInputState::instance.menuLoadGameRelativeSelectionOffset) {
                    DAT_MenuTextInputState::instance.menuLoadGameRelativeSelectionOffset
                        = DAT_MenuTextInputState::instance.menuLoadGameRelativeSelectionOffset + -1;
                    *currentValue = DAT_MenuTextInputState::instance.menuLoadGameRelativeSelectionOffset;
                    return;
                }
                break;
            case 6:
                if ((int)DAT_MenuTextInputState::instance.menuLoadGameRelativeSelectionOffset
                    < (int)DAT_MenuTextInputState::instance.fileListEntryCount - DAT_MenuTextInputState::instance.fileListVisibleRowCount) {
                    DAT_MenuTextInputState::instance.menuLoadGameRelativeSelectionOffset
                        = DAT_MenuTextInputState::instance.menuLoadGameRelativeSelectionOffset + 1;
                }
                break;
            default:
                return;
            }
            *currentValue = DAT_MenuTextInputState::instance.menuLoadGameRelativeSelectionOffset;
        }

    }
}
}
