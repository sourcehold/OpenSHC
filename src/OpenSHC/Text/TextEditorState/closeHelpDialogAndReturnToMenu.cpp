#include "../TextEditorState.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/Util/WideCharMultiByteState.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuView_TriggerPrepare.hpp"
#include "OpenSHC/Globals/DAT_WideCharMultiByteState.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x0045F240
    void TextEditorState::closeHelpDialogAndReturnToMenu()
    {
        if (!this->isDialogStateInitialized) {
            return;
        }
        MACRO_CALL_MEMBER(TextEditorState_Func::resetHelpStateFields, this)();
        this->isDialogStateInitialized = 0;

        if (this->isCustomTextMode) {
            MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog, DAT_MenuModalComposition1::ptr)(
                UI::Enums::MMT_NONE, FALSE);
            for (int i = 0; i < 20; ++i) {
                this->intArray1[i] = 0;
            }
            if (this->customHelpTextPointer) {
                if (!this->isCustomHelpTextWide) {
                    MACRO_CALL_MEMBER(Util::WideCharMultiByteState_Func::wideCharToMultiByteWithSize,
                        DAT_WideCharMultiByteState::ptr)(this->customHelpTextPointer,
                        this->DAT_PointerToTemporaryTextMemory, this->customHelpTextBufferSize);
                } else {
                    MACRO_CALL(OS_Func::_wcsncpy)((wchar_t*)this->customHelpTextPointer,
                        this->DAT_PointerToTemporaryTextMemory, this->customHelpTextBufferSize);
                }
            }
            DAT_MenuView_TriggerPrepare::instance = TRUE;

        } else if (this->helpDialogVariant == 0) {

            if (this->savedMenuViewType == UI::Enums::MVT_BUILD_MENU) {
                DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType = this->savedActiveMenuTab;
                MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    (UI::Enums::MenuViewType)this->savedMenuViewType, 0);

            } else if (this->savedMenuViewType == UI::Enums::MVT_MAP_EDITOR_LANDSCAPING) {
                DAT_GameCore::instance.landscapingmenuMenuTabToSwitchTo = this->savedActiveMenuTab;
                MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    (UI::Enums::MenuViewType)this->savedMenuViewType, 0);

            } else if (this->savedMenuViewType == UI::Enums::MVT_BUILDING_AND_STATUS_MENU) {
                DAT_GameCore::instance.buildingandstatusmenuMenuTabToSwitchTo = this->savedActiveMenuTab;
                MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    (UI::Enums::MenuViewType)this->savedMenuViewType, 0);

            } else {
                DAT_GameCore::instance.menuTabToSwitchTo.tabType = this->savedActiveMenuTab;
                MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    (UI::Enums::MenuViewType)this->savedMenuViewType, 0);
            }

        } else {
            MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog, DAT_MenuModalComposition1::ptr)(
                UI::Enums::MMT_NONE, FALSE);
            for (int i = 0; i < 20; ++i) {
                this->intArray1[i] = 0;
            }
        }

        this->helpDialogVariant = 0;
    }

}
}
