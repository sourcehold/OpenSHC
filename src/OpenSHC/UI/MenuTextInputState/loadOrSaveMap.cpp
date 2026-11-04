#include "../MenuTextInputState.func.hpp"

#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MenuItems/SaveLoadMap.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"
#include "OpenSHC/Globals/INT_00b95b64.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::UI::Enums::MenuModalType;

    // FUNCTION: STRONGHOLDCRUSADER 0x00493AC0
    void MenuTextInputState::loadOrSaveMap(MenuModalType dialogType)
    {
        DAT_MouseState::instance.waitCursorToggle = 1;
        MACRO_CALL(OpenSHC::UI::Helpers_Func::SetCursorDependingOnProgramState)();
        MACRO_CALL(OpenSHC::OS_Func::_memset)(
            DAT_MinimapViewState::instance.loadedMiniMap, 0, sizeof(DAT_MinimapViewState::instance.loadedMiniMap));
        INT_00b95b64::instance = 1;
        MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::discoverMapFiles, DAT_ResourceManager::ptr)(
            // "maps\\*.tmp"
            s_maps_tmp_005a75b0);
        MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::mapNames_filterMapsIfMapLock, DAT_ResourceManager::ptr)();
        this->fileListEntryCount = DAT_ResourceManager::instance.mapFileCounter;
        int i = 0;
        // the match needs the counter outside the guard
        if (0 < DAT_ResourceManager::instance.mapFileCounter) {
            for (; i < DAT_ResourceManager::instance.mapFileCounter; ++i) {
                this->DAT_ArrayOfMapIndices[i] = i;
            }
        }
        if (this->fileListEntryCount != 0) {
            this->menuLoadGameRelativeSelectionIndex = 0;
        } else {
            this->menuLoadGameRelativeSelectionIndex = -1;
        }
        this->fileListSortOrder = 0;
        this->menuLoadGameRelativeSelectionOffset = 0;
        DAT_MouseState::instance.waitCursorToggle = 0;
        this->lastListClickTime = 0;
        this->lastClickedListIndex = -1;
        this->DAT_ArrayOfMapU3EndInt2[0] = 1;
        this->fileListVisibleRowCount = 16;
        if (dialogType == OpenSHC::UI::Enums::MMT_LOAD_MAP) {
            MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::activateModalDialogAndClearText, this)(
                OpenSHC::UI::Enums::MMT_LOAD_MAP);
        } else {
            MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::activateModalDialogAndClearText, this)(
                OpenSHC::UI::Enums::MMT_SAVE_MAP);
            DAT_UserTextHandlerState::instance.allowUserTextInput = 0;
            MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(2);
            MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::moveCursorToEnd, DAT_UserTextHandlerState::ptr)();
            DAT_UserTextHandlerState::instance.allowUserTextInput = 1;
        }
        this->previewedListIndex = -1;
        MACRO_CALL(OpenSHC::UI::MenuItems::SaveLoadMap_Func::MenuItemActionHandler_SaveLoadMap_TableHeader)(1);
    }

}
}
