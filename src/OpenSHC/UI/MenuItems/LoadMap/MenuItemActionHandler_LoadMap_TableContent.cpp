#include "../LoadMap.func.hpp"

#include "OpenSHC/UI/MenuItems/SaveLoadMap.func.hpp"

#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004948C0
        void LoadMap::MenuItemActionHandler_LoadMap_TableContent(int param_1, ...)
        {
            DWORD DVar1;
            DVar1 = timeGetTime();
            if ((int)DAT_MenuTextInputState::instance.menuLoadGameRelativeSelectionOffset + param_1
                < (int)DAT_MenuTextInputState::instance.fileListEntryCount) {
                DAT_MenuTextInputState::instance.menuLoadGameRelativeSelectionIndex = param_1;
                if ((DAT_MenuTextInputState::instance.menuLoadGameRelativeSelectionOffset + param_1
                        == DAT_MenuTextInputState::instance.lastClickedListIndex)
                    && ((int)(DVar1 - DAT_MenuTextInputState::instance.lastListClickTime) < 500)) {
                    MACRO_CALL(OpenSHC::UI::MenuItems::SaveLoadMap_Func::MenuItemActionHandler_SaveLoadMap_Buttons)(2);
                }
                DAT_MenuTextInputState::instance.lastClickedListIndex
                    = DAT_MenuTextInputState::instance.menuLoadGameRelativeSelectionIndex
                    + DAT_MenuTextInputState::instance.menuLoadGameRelativeSelectionOffset;
                DAT_MenuTextInputState::instance.lastListClickTime = DVar1;
            }
        }

    }
}
}
