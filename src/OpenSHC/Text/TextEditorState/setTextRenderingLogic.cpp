#include "../TextEditorState.func.hpp"

#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"

#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x004613E0
    void TextEditorState::setTextRenderingLogic()
    {
        if (this->helpDialogVariant != 1) {
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::setRenderingRect,
                DAT_TextureRenderCoreObject::ptr)(this->dialogContentX, this->dialogContentY,
                this->dialogContentHeight + this->dialogContentX, this->dialogContentWidth + this->dialogContentY);
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::setScreenMenuSurfaceHeightRange,
                DAT_TextureRenderCoreObject::ptr)(
                this->dialogContentY, this->dialogContentWidth + this->dialogContentY);
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = Rendering::Enums::RT_SCREEN_MENU;
        } else {
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::setRenderingRect,
                DAT_TextureRenderCoreObject::ptr)(this->dialogContentX, this->dialogContentY,
                this->dialogContentHeight + this->dialogContentX, this->dialogContentWidth + this->dialogContentY);
            MACRO_CALL_MEMBER(
                UI::Rendering::TextureRenderCore_Func::setMapSurfaceHeightRange, DAT_TextureRenderCoreObject::ptr)(
                this->dialogContentY, this->dialogContentWidth + this->dialogContentY);
            DAT_TextManagerObject::instance.textSurfaceTarget = Rendering::Enums::RT_MAP_GAME;
            DAT_PencilRenderCore::instance.surfaceTarget = Rendering::Enums::RT_MAP_GAME;
            DAT_TextureRenderCoreObject::instance.currentRenderSurfaceIdentifierUnk_0x8 = Rendering::Enums::RT_MAP_GAME;
        }
        MACRO_CALL_MEMBER(TextEditorState_Func::processHelpRichTextTokens, this)(TRUE);
        MACRO_CALL_MEMBER(TextEditorState_Func::renderHelpImageHotspots, this)();
        if (this->helpDialogVariant != 1) {
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = Rendering::Enums::RT_MAP_GAME;
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::setScreenMenuSurfaceHeightRangeToResolution,
                DAT_TextureRenderCoreObject::ptr)();
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::setRenderingRectToGameResolution,
                DAT_TextureRenderCoreObject::ptr)();
        } else {
            MACRO_CALL_MEMBER(
                UI::Rendering::TextureRenderCore_Func::setMapSurfaceHeightRangeUnk, DAT_TextureRenderCoreObject::ptr)();
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::setRenderingRectToGameResolution,
                DAT_TextureRenderCoreObject::ptr)();
            DAT_TextManagerObject::instance.textSurfaceTarget = Rendering::Enums::RT_SCREEN_MENU;
            DAT_PencilRenderCore::instance.surfaceTarget = Rendering::Enums::RT_SCREEN_MENU;
            DAT_TextureRenderCoreObject::instance.currentRenderSurfaceIdentifierUnk_0x8
                = Rendering::Enums::RT_SCREEN_MENU;
        }
    }

}
}
