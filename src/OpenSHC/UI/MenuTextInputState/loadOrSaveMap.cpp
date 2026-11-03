#include "../MenuTextInputState.func.hpp"

#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MenuItems/SaveLoadMap.func.hpp"
#include "OpenSHC/UI/MenuTextInputState.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"
#include "OpenSHC/Globals/INT_00b95b64.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::UI::Enums::MenuModalType;

    // FUNCTION: STRONGHOLDCRUSADER 0x00493AC0
    void MenuTextInputState::loadOrSaveMap(MenuModalType param_1)
    {
        DAT_MouseState::instance.waitCursorToggle = 1;
        MACRO_CALL(OpenSHC::UI::Helpers_Func::SetCursorDependingOnProgramState)();
        MACRO_CALL(OpenSHC::OS_Func::_memset)(DAT_MinimapViewState::instance.loadedMiniMap, 0, 80000);
        INT_00b95b64::instance = 1;
        MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::discoverMapFiles, DAT_ResourceManager::ptr)("maps\\*.tmp");
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
        this->menuLoadGameRelativeSelectionIndex = this->fileListEntryCount != 0 ? 0 : -1;
        this->fileListSortOrder = 0;
        this->menuLoadGameRelativeSelectionOffset = 0;
        DAT_MouseState::instance.waitCursorToggle = 0;
        this->lastListClickTime = 0;
        this->lastClickedListIndex = 0xffffffff;
        this->field46_0xac = 1;
        this->fileListVisibleRowCount = 0x10;
        if (param_1 == OpenSHC::UI::Enums::MMT_LOAD_MAP) {
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
        MACRO_CALL(OpenSHC::UI::MenuItems::SaveLoadMap_Func::MenuItemActionHandler_SaveLoadMap_TableHeader)(1);
    }

}
}
