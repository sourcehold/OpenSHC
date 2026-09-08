#include "../TextEditorState.func.hpp"

#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"

#include "OpenSHC/Globals/COL_GREYISH_YELLOW.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x0045D430
    void TextEditorState::renderHelpImageHotspots()
    {
        for (int i = 0; i < this->imageHotspotCount; ++i) {
            int _gfxIndex = 99 - this->imageHotspotTable[i].imageRelated;
            if ((this->useInGameHelpHandler || this->helpDialogVariant == 1)
                && !MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::checkIfGfxTgxStartsWithTransparentPixels,
                    DAT_TextureRenderCoreObject::ptr)(_gfxIndex)) {
                int x1 = this->imageHotspotTable[i].xPos + this->dialogContentX - 2;
                int y1 = this->imageHotspotTable[i].yPos - this->helpContentScrollOffsetY + this->dialogContentY - 2;
                int width = DAT_TextureRenderCoreObject::instance.loadedGfxArray[_gfxIndex].width + 3;
                int height = DAT_TextureRenderCoreObject::instance.loadedGfxArray[_gfxIndex].height + 3;
                if (y1 < this->dialogContentY) {
                    height += y1 - this->dialogContentY;
                    y1 = this->dialogContentY;
                }
                // Does the naming "dialogContentWidth" fit? Is it related to width?
                if (height + y1 > this->dialogContentY + this->dialogContentWidth) {
                    height = this->dialogContentWidth * 2 - y1;
                }
                int const y2 = y1 + height;
                if (y2 >= this->dialogContentY && y1 < this->dialogContentY + this->dialogContentWidth) {
                    int const x2 = x1 + width;
                    MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                        x1, y1, x2, y1, COL_GREYISH_YELLOW::instance.shortValue);
                    MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                        x1, y1 + 1, x2, y1 + 1, COL_GREYISH_YELLOW::instance.shortValue);
                    MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                        x1, y2, x2, y2, COL_GREYISH_YELLOW::instance.shortValue);
                    MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                        x1, y2 + -1, x2, y2 + -1, COL_GREYISH_YELLOW::instance.shortValue);
                    MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                        x1, y1, x1, y2, COL_GREYISH_YELLOW::instance.shortValue);
                    MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                        x1 + 1, y1, x1 + 1, y2, COL_GREYISH_YELLOW::instance.shortValue);
                    MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                        x2, y1, x2, y2, COL_GREYISH_YELLOW::instance.shortValue);
                    MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                        x2 + -1, y1, x2 + -1, y2, COL_GREYISH_YELLOW::instance.shortValue);
                }
            }
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::drawGfxOnFlaggedSurface,
                DAT_TextureRenderCoreObject::ptr)(_gfxIndex, this->imageHotspotTable[i].xPos + this->dialogContentX,
                this->imageHotspotTable[i].yPos - this->helpContentScrollOffsetY + this->dialogContentY);

            int const boxHeight = DAT_TextureRenderCoreObject::instance.loadedGfxArray[_gfxIndex].height;
            int const boxWidth = DAT_TextureRenderCoreObject::instance.loadedGfxArray[_gfxIndex].width;
            if (MACRO_CALL_MEMBER(Input::MouseState_Func::isMouseInsideBox, DAT_MouseState::ptr)(
                    this->imageHotspotTable[i].xPos - this->helpContentScrollX + this->dialogContentX,
                    this->imageHotspotTable[i].yPos - this->helpContentScrollY + this->dialogContentY
                        - this->helpContentScrollOffsetY,
                    boxWidth, boxHeight)) {
                this->unknown_0x23968 = this->imageHotspotTable[i].unknown3;
            }
        }
    }

}
}
