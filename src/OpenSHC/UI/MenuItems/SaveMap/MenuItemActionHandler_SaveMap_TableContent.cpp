#include "../SaveMap.func.hpp"

#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"

#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004932A0
        void SaveMap::MenuItemActionHandler_SaveMap_TableContent(int param_1, ...)
        {
            char* pcVar1;
            if (DAT_MenuTextInputState::instance.DAT_MenuLoadGameRelativeSelectionOffset + param_1
                < DAT_MenuTextInputState::instance.field32_0x74) {
                DAT_MenuTextInputState::instance.DAT_MenuLoadGameRelativeSelectionIndex = param_1;
                pcVar1 = MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::mapNames_getLoadedMapNameForIndex,
                    DAT_ResourceManager::ptr)(DAT_MenuTextInputState::instance
                        .DAT_ArrayOfMapIndices[DAT_MenuTextInputState::instance.DAT_MenuLoadGameRelativeSelectionOffset
                            + param_1 + -1]);
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::UserTextHandler_Func::copyIntoTextArray, DAT_UserTextHandlerState::ptr)(pcVar1);
            }
        }

    }
}
}
