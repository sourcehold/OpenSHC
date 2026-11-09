#include "../SaveLoadMap.func.hpp"

#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x00492BA0
        void SaveLoadMap::MenuItemActionHandler_SaveLoadMap_Scrollbar(
            int unused, int scrollbarEvent, int* minValue, int* maxValue, int* currentValue)
        {
            switch (scrollbarEvent) {
            case 1:
                *minValue = 0;
                *maxValue = DAT_MenuTextInputState::instance.fileListEntryCount
                    - DAT_MenuTextInputState::instance.fileListVisibleRowCount;
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
                *currentValue = DAT_MenuTextInputState::instance.fileListVisibleRowCount - 1;
                return;
            case 5:
                // Stores and returns here rather than through the shared store below, as the original does.
                if (DAT_MenuTextInputState::instance.menuLoadGameRelativeSelectionOffset > 0) {
                    --DAT_MenuTextInputState::instance.menuLoadGameRelativeSelectionOffset;
                    *currentValue = DAT_MenuTextInputState::instance.menuLoadGameRelativeSelectionOffset;
                    return;
                }
                break;
            case 6:
                if (DAT_MenuTextInputState::instance.menuLoadGameRelativeSelectionOffset
                    < DAT_MenuTextInputState::instance.fileListEntryCount
                        - DAT_MenuTextInputState::instance.fileListVisibleRowCount) {
                    ++DAT_MenuTextInputState::instance.menuLoadGameRelativeSelectionOffset;
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
