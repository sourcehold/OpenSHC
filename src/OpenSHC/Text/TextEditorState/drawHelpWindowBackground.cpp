#include "../TextEditorState.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/COL_DARK_CYAN_GREY.hpp"
#include "OpenSHC/Globals/COL_VERY_DARK_GREY.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x0045D740
    void TextEditorState::drawHelpWindowBackground()
    {
        if (this->helpDialogVariant != 1) {
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = Rendering::Enums::RT_SCREEN_MENU;
        } else {
            DAT_TextManagerObject::instance.textSurfaceTarget = Rendering::Enums::RT_MAP_GAME;
            DAT_PencilRenderCore::instance.surfaceTarget = Rendering::Enums::RT_MAP_GAME;
        }
        if (this->isCustomTextMode) {
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawBoxWithRoundedEdges, DAT_PencilRenderCore::ptr)(
                this->dialogX, this->dialogY, this->dialogWidth + this->dialogX, this->dialogHeight + this->dialogY,
                UI::Enums::RBERL_SLIGHT);
        } else if (!this->useAlternateHelpTab) {
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
                this->dialogX, this->dialogY, this->dialogWidth + this->dialogX, this->dialogHeight + this->dialogY,
                COL_BLACK::instance.shortValue);
        } else if (this->helpDialogVariant != 2) {
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
                this->dialogX, this->dialogY, this->dialogWidth + this->dialogX, this->dialogHeight + this->dialogY,
                COL_VERY_DARK_GREY::instance.shortValue);
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
                this->dialogContentX, this->dialogContentY, this->dialogContentHeight + this->dialogContentX,
                this->dialogContentWidth + this->dialogContentY, COL_BLACK::instance.shortValue);
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
                this->dialogX, this->dialogY + this->dialogHeight, this->dialogWidth + this->dialogX,
                this->dialogY + this->dialogHeight + 60, COL_DARK_CYAN_GREY::instance.shortValue);
        }
        if (this->helpDialogVariant != 1) {
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = Rendering::Enums::RT_MAP_GAME;
        } else {
            DAT_TextManagerObject::instance.textSurfaceTarget = Rendering::Enums::RT_SCREEN_MENU;
            DAT_PencilRenderCore::instance.surfaceTarget = Rendering::Enums::RT_SCREEN_MENU;
        }
    }

}
}
