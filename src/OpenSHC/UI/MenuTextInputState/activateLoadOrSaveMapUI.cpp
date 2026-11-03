#include "../MenuTextInputState.func.hpp"

#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MenuItems/SaveLoadMap.func.hpp"
#include "OpenSHC/UI/MenuTextInputState.func.hpp"
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

    // FUNCTION: STRONGHOLDCRUSADER 0x00493980
    void MenuTextInputState::activateLoadOrSaveMapUI(int loadOrSaveMap)
    {
        DAT_MouseState::instance.waitCursorToggle = 1;
        MACRO_CALL(OpenSHC::UI::Helpers_Func::SetCursorDependingOnProgramState)();
        MACRO_CALL(OpenSHC::OS_Func::_memset)(DAT_MinimapViewState::instance.loadedMiniMap, 0, 80000);
        INT_00b95b64::instance = 1;
        MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::discoverMapFiles, DAT_ResourceManager::ptr)(
            s_maps_map_005a64b0);
        MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::mapNames_filterMapsIfMapLock, DAT_ResourceManager::ptr)();
        this->fileListEntryCount = DAT_ResourceManager::instance.mapFileCounter;
        // The header has DAT_MapSelectionPreloadMapIndexMapping as one dword, but the list of map indices starts
        // there: one entry per map file.
        int i = 0;
        if (0 < DAT_ResourceManager::instance.mapFileCounter) {
            int* mapIndex = (int*)&this->DAT_MapSelectionPreloadMapIndexMapping;
            do {
                *mapIndex = i;
                i = i + 1;
                mapIndex = mapIndex + 1;
            } while (i < DAT_ResourceManager::instance.mapFileCounter);
        }
        this->fileListSortOrder = 0;
        this->menuLoadGameRelativeSelectionOffset = 0;
        if (this->fileListEntryCount == 0) {
            this->menuLoadGameRelativeSelectionIndex = -1;
        } else {
            this->menuLoadGameRelativeSelectionIndex = 0;
        }
        this->lastListClickTime = 0;
        this->lastClickedListIndex = 0xffffffff;
        this->field46_0xac = 0;
        DAT_MouseState::instance.waitCursorToggle = 0;
        this->fileListVisibleRowCount = 0x10;
        if (loadOrSaveMap == 9) {
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
        this->previewedListIndex = 0xffffffff;
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
