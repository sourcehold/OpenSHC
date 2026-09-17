#include "../TextEditorState.func.hpp"

#include "OpenSHC/Text/TextEditorState.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"

#include "OpenSHC/Globals/DAT_00df2964.hpp"
#include "OpenSHC/Globals/DAT_00df296c.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"
#include "OpenSHC/Globals/INT_00df2968.hpp"
#include "OpenSHC/Globals/INT_00df2970.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00461A20
    void TextEditorState::openBuildingHelpDialog(int sectionId)
    {
        if (!this->isDialogStateInitialized) {
            this->isDialogStateInitialized = TRUE;
            this->helpDialogVariant = 1;
            this->useInGameHelpHandler = 0;
            this->helpDialogSubMode = 0;
            this->useAlternateHelpTab = 0;
            this->isCustomTextMode = 0;
            DAT_UserTextHandlerState::instance.inputBufferIndex = 0;
            this->helpContentScrollX = 0;
            this->helpContentScrollY = 0;
        } else if (sectionId == this->currentHelpSectionID) {
            return;
        }

        this->activeHelpHotspotIndex = 0;
        if (sectionId == -1) {
            MACRO_CALL_MEMBER(TextEditorState_Func::closeHelpDialogAndReturnToMenu, this)();
            return;
        }

        this->isTextHelpDialogMode = 1;
        MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog, DAT_MenuModalComposition1::ptr)(
            UI::Enums::MMT_BUILDING_HELP_TEXT, FALSE);

        int modalX;
        int modalY;
        int modalWidth;
        int modalHeight;
        MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::fillWithMenuModalDimensions, DAT_MenuModalComposition1::ptr)(
            &modalX, &modalY, &modalWidth, &modalHeight);
        // Likely also some rect structure
        DAT_00df2964::instance = 15;
        DAT_00df296c::instance = 13;
        INT_00df2968::instance = 60;
        INT_00df2970::instance = 65;
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
