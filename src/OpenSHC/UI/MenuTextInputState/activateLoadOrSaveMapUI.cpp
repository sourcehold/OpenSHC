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

    // FUNCTION: STRONGHOLDCRUSADER 0x00493980
    void MenuTextInputState::activateLoadOrSaveMapUI(MenuModalType loadOrSaveMap)
    {
        DAT_MouseState::instance.waitCursorToggle = 1;
        MACRO_CALL(OpenSHC::UI::Helpers_Func::SetCursorDependingOnProgramState)();
        MACRO_CALL(OpenSHC::OS_Func::_memset)(
            DAT_MinimapViewState::instance.loadedMiniMap, 0, sizeof(DAT_MinimapViewState::instance.loadedMiniMap));
        INT_00b95b64::instance = 1;
        MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::discoverMapFiles, DAT_ResourceManager::ptr)(
            // "maps\\*.map"
            s_maps_map_005a64b0);
        MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::mapNames_filterMapsIfMapLock, DAT_ResourceManager::ptr)();
        this->fileListEntryCount = DAT_ResourceManager::instance.mapFileCounter;
        int i = 0;
        // the match needs the counter outside the guard
        if (0 < DAT_ResourceManager::instance.mapFileCounter) {
            for (; i < DAT_ResourceManager::instance.mapFileCounter; ++i) {
                this->DAT_ArrayOfMapIndices[i] = i;
            }
        }
        this->fileListSortOrder = 0;
        this->menuLoadGameRelativeSelectionOffset = 0;
        if (this->fileListEntryCount == 0) {
            this->menuLoadGameRelativeSelectionIndex = -1;
        } else {
            this->menuLoadGameRelativeSelectionIndex = 0;
        }
        this->lastListClickTime = 0;
        this->lastClickedListIndex = -1;
        this->DAT_ArrayOfMapU3EndInt2 = 0;
        DAT_MouseState::instance.waitCursorToggle = 0;
        this->fileListVisibleRowCount = 16;
        if (loadOrSaveMap == OpenSHC::UI::Enums::MMT_LOAD_MAP) {
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
        this->fileListContext = 2;
        if (this->menuLoadGameRelativeSelectionIndex != -1) {
            this->menuLoadGameRelativeSelectionIndex = this->savedListSelection3;
            this->menuLoadGameRelativeSelectionOffset = this->savedListOffset3;
            this->fileListSortOrder = this->savedListSortOrder3;
            if (this->menuLoadGameRelativeSelectionOffset + this->menuLoadGameRelativeSelectionIndex
                >= this->fileListEntryCount) {
                this->menuLoadGameRelativeSelectionIndex = 0;
                this->menuLoadGameRelativeSelectionOffset = 0;
            }
            MACRO_CALL(OpenSHC::UI::MenuItems::SaveLoadMap_Func::MenuItemActionHandler_SaveLoadMap_TableHeader)(
                -1 - this->savedListSortOrder3);
        }
    }

}
}
