#include "../TextEditorState.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/Menu_UnusedHelpTextEditor.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00462190
    void TextEditorState::openUnusedHelpTextEditorDialog(int sectionId)
    {
        if (this->helpDialogVariant) {
            if (this->helpDialogVariant == 2) {
                MACRO_CALL_MEMBER(TextEditorState_Func::openScenarioHelpDialog, this)(sectionId);
                return;
            }
            if (this->useInGameHelpHandler) {
                MACRO_CALL_MEMBER(TextEditorState_Func::openInGameHelpDialog, this)(sectionId);
                return;
            }
            MACRO_CALL_MEMBER(TextEditorState_Func::openBuildingHelpDialog, this)(sectionId);
            return;
        }

        if (!this->isDialogStateInitialized) {
            this->savedMenuViewType = DAT_GameCore::instance.currentMenuViewType;
            this->savedActiveMenuTab = DAT_GameCore::instance.activeMenuTab.tabType;
            this->savedMenuFlag = DAT_GameCore::instance.unknownAlwaysZero01;
            this->field48_0x23960 = 1;
            this->isDialogStateInitialized = TRUE;
            this->useInGameHelpHandler = FALSE;
            this->helpDialogVariant = 0;
            this->helpDialogSubMode = 0;
            this->useAlternateHelpTab = FALSE;
            this->isCustomTextMode = FALSE;
            this->helpContentScrollX = 0;
            this->helpContentScrollY = 0;
            this->useWideHelpLayout = FALSE;
            DAT_UserTextHandlerState::instance.inputBufferIndex = 0;
        }
        this->activeHelpHotspotIndex = 0;
        if (sectionId == -1) {
            MACRO_CALL_MEMBER(TextEditorState_Func::closeHelpDialogAndReturnToMenu, this)();
            return;
        }
        if (!this->useAlternateHelpTab) {
            this->isTextHelpDialogMode = TRUE;
            DAT_GameCore::instance.menuTabToSwitchTo.tabType = 0;
            MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                UI::Enums::MVT_UNUSED_HELP_TEXT_EDITOR, 0);
        } else {
            this->isTextHelpDialogMode = TRUE;
            DAT_GameCore::instance.menuTabToSwitchTo.tabType = 1;
            MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                UI::Enums::MVT_UNUSED_HELP_TEXT_EDITOR, 0);
        }
        Menu_UnusedHelpTextEditor::instance.thousand = 0;

        int const dialogX = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 80;
        int const dialogY = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 60;
        int const dialogWidth = 640;
        int const dialogHeight = 480;
        this->dialogX = dialogX;
        this->dialogY = dialogY;
        this->dialogWidth = dialogWidth;
        this->dialogHeight = dialogHeight;

        if (!this->useWideHelpLayout) {
            this->dialogContentX = this->dialogX + 10;
            this->dialogContentY = this->dialogY + 10;
            this->dialogContentWidth = 600;
            this->dialogContentHeight = 435;
        } else {
            this->dialogContentX = this->dialogX + 10;
            this->dialogContentY = this->dialogY + 10;
            this->dialogContentWidth = 664;
            this->dialogContentHeight = 291;
        }

        for (int i = 28; i >= 0; --i) {
            this->helpSectionHistoryStack[i + 1] = this->helpSectionHistoryStack[i];
        }
        this->helpSectionHistoryStack[0] = this->currentHelpSectionID;

        this->currentHelpSectionID = sectionId;
        this->helpContentScrollOffsetY = 0;
        MACRO_CALL_MEMBER(TextEditorState_Func::loadAndLayoutHelpContent, this)();
    }

}
}
