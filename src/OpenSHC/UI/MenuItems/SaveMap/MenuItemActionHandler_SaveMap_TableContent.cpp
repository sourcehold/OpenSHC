#include "../SaveMap.func.hpp"

#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"

#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004932A0
        void SaveMap::MenuItemActionHandler_SaveMap_TableContent(int row, ...)
        {
            if (DAT_MenuTextInputState::instance.menuLoadGameRelativeSelectionOffset + row
                < DAT_MenuTextInputState::instance.fileListEntryCount) {
                DAT_MenuTextInputState::instance.menuLoadGameRelativeSelectionIndex = row;
                char* const mapName
                    = MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::mapNames_getLoadedMapNameForIndex,
                        DAT_ResourceManager::ptr)(DAT_MenuTextInputState::instance
                            .DAT_ArrayOfMapIndices[DAT_MenuTextInputState::instance.menuLoadGameRelativeSelectionOffset
                                + row]);
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::UserTextHandler_Func::copyIntoTextArray, DAT_UserTextHandlerState::ptr)(mapName);
            }
        }

    }
}
}
