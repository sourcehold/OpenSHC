#include "../TextEditorState.func.hpp"

#include "OpenSHC/UI/MenuModalComposition.func.hpp"

#include "OpenSHC/Globals/DAT_00df2964.hpp"
#include "OpenSHC/Globals/DAT_00df296c.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"
#include "OpenSHC/Globals/INT_00df2968.hpp"
#include "OpenSHC/Globals/INT_00df2970.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00461E50
    void TextEditorState::openCreditsScrollDialog(int sectionId)
    {
        if (!this->isDialogStateInitialized) {
            this->isDialogStateInitialized = TRUE;
            this->helpDialogVariant = 2;
            this->useInGameHelpHandler = FALSE;
            this->helpDialogSubMode = 0;
            this->useAlternateHelpTab = FALSE;
            this->isCustomTextMode = FALSE;
            DAT_UserTextHandlerState::instance.inputBufferIndex = 0;
        }
        this->activeHelpHotspotIndex = 0;
        if (sectionId == -1) {
            MACRO_CALL_MEMBER(TextEditorState_Func::closeHelpDialogAndReturnToMenu, this)();
            return;
        }

        this->isTextHelpDialogMode = TRUE;
        MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog, DAT_MenuModalComposition1::ptr)(
            UI::Enums::MMT_CREDITS_SCROLL, FALSE);

        int modalX;
        int modalY;
        int modalWidth;
        int modalHeight;
        MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::fillWithMenuModalDimensions, DAT_MenuModalComposition1::ptr)(
            &modalX, &modalY, &modalWidth, &modalHeight);

        DAT_00df2964::instance = 0;
        DAT_00df296c::instance = 0;
        INT_00df2968::instance = 0;
        INT_00df2970::instance = 0;
        this->dialogX = modalX;
        this->dialogY = modalY;
        this->dialogWidth = modalWidth;
        this->dialogHeight = modalHeight;

        int const dialogContentX = this->dialogX + DAT_00df2964::instance;
        int const dialogContentY = this->dialogY + DAT_00df296c::instance;
        int const dialogContentHeight = this->dialogHeight - INT_00df2970::instance;
        int const dialogContentWidth = this->dialogWidth - INT_00df2968::instance;
        this->dialogContentX = dialogContentX;
        this->dialogContentY = dialogContentY;
        this->dialogContentHeight = dialogContentWidth;
        this->dialogContentWidth = dialogContentHeight;

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
