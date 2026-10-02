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
            if (DAT_MenuTextInputState::instance.DAT_MenuLoadGameRelativeSelectionOffset + param_1
                < DAT_MenuTextInputState::instance.field32_0x74) {
                DAT_MenuTextInputState::instance.DAT_MenuLoadGameRelativeSelectionIndex = param_1;
                if ((DAT_MenuTextInputState::instance.DAT_MenuLoadGameRelativeSelectionOffset + param_1
                        == DAT_MenuTextInputState::instance.field38_0x8c)
                    && ((int)(DVar1 - DAT_MenuTextInputState::instance.field39_0x90) < 500)) {
                    MACRO_CALL(OpenSHC::UI::MenuItems::SaveLoadMap_Func::MenuItemActionHandler_SaveLoadMap_Buttons)(2);
                }
                DAT_MenuTextInputState::instance.field38_0x8c
                    = DAT_MenuTextInputState::instance.DAT_MenuLoadGameRelativeSelectionIndex
                    + DAT_MenuTextInputState::instance.DAT_MenuLoadGameRelativeSelectionOffset;
                DAT_MenuTextInputState::instance.field39_0x90 = DVar1;
            }
        }

    }
}
}
