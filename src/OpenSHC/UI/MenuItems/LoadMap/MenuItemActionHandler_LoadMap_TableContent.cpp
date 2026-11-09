#include "../LoadMap.func.hpp"

#include "OpenSHC/UI/MenuItems/SaveLoadMap.func.hpp"

#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004948C0
        void LoadMap::MenuItemActionHandler_LoadMap_TableContent(int row, ...)
        {
            DWORD const clickTime = timeGetTime();
            if (DAT_MenuTextInputState::instance.menuLoadGameRelativeSelectionOffset + row
                < DAT_MenuTextInputState::instance.fileListEntryCount) {
                DAT_MenuTextInputState::instance.menuLoadGameRelativeSelectionIndex = row;
                if ((DAT_MenuTextInputState::instance.menuLoadGameRelativeSelectionOffset + row
                        == DAT_MenuTextInputState::instance.lastClickedListIndex)
                    && ((int)(clickTime - DAT_MenuTextInputState::instance.lastListClickTime) < 500)) {
                    MACRO_CALL(OpenSHC::UI::MenuItems::SaveLoadMap_Func::MenuItemActionHandler_SaveLoadMap_Buttons)(2);
                }
                DAT_MenuTextInputState::instance.lastClickedListIndex
                    = DAT_MenuTextInputState::instance.menuLoadGameRelativeSelectionIndex
                    + DAT_MenuTextInputState::instance.menuLoadGameRelativeSelectionOffset;
                DAT_MenuTextInputState::instance.lastListClickTime = clickTime;
            }
        }

    }
}
}
