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

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00493980
    void MenuTextInputState::activateLoadOrSaveMapUI(int loadOrSaveMap)
    {
        int iVar1;
        int* piVar2;
        DAT_MouseState::instance.waitCursorToggle = 1;
        MACRO_CALL(OpenSHC::UI::Helpers_Func::SetCursorDependingOnProgramState)();
        MACRO_CALL(OpenSHC::OS_Func::_memset)(DAT_MinimapViewState::instance.loadedMiniMap, 0, 80000);
        INT_00b95b64::instance = 1;
        MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::discoverMapFiles, DAT_ResourceManager::ptr)("maps\\*.map");
        MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::mapNames_filterMapsIfMapLock, DAT_ResourceManager::ptr)();
        this->field32_0x74 = DAT_ResourceManager::instance.mapFileCounter;
        iVar1 = 0;
        if (0 < DAT_ResourceManager::instance.mapFileCounter) {
            piVar2 = (int*)(&this->DAT_MapSelectionPreloadMapIndexMapping);
            do {
                *piVar2 = iVar1;
                iVar1 = iVar1 + 1;
                piVar2 = piVar2 + 1;
            } while (iVar1 < DAT_ResourceManager::instance.mapFileCounter);
        }
        this->field33_0x78 = 0;
        this->DAT_MenuLoadGameRelativeSelectionOffset = 0;
        if (this->field32_0x74 == 0) {
            this->DAT_MenuLoadGameRelativeSelectionIndex = -1;
        } else {
            this->DAT_MenuLoadGameRelativeSelectionIndex = 0;
        }
        this->field39_0x90 = 0;
        this->field38_0x8c = 0xffffffff;
        this->field49_0xac = 0;
        DAT_MouseState::instance.waitCursorToggle = 0;
        this->field36_0x84 = 0x10;
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
        this->field43_0xa0 = 0xffffffff;
        this->field0_0x0 = 2;
        if (this->DAT_MenuLoadGameRelativeSelectionIndex != -1) {
            this->DAT_MenuLoadGameRelativeSelectionOffset = this->field7_0x1c;
            this->DAT_MenuLoadGameRelativeSelectionIndex = this->field8_0x20;
            this->field33_0x78 = this->field9_0x24;
            if (this->field32_0x74 <= this->field7_0x1c + this->field8_0x20) {
                this->DAT_MenuLoadGameRelativeSelectionIndex = 0;
                this->DAT_MenuLoadGameRelativeSelectionOffset = 0;
            }
            MACRO_CALL(OpenSHC::UI::MenuItems::SaveLoadMap_Func::MenuItemActionHandler_SaveLoadMap_TableHeader)(
                -1 - this->field9_0x24);
        }
    }

}
}
