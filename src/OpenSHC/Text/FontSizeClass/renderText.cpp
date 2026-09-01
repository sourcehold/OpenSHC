#include "../FontSizeClass.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"

#include "OpenSHC/Globals/DAT_GMImageHeaders.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextInputDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/GMTotalPicturesProcessed.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00472D60
    int FontSizeClass::renderText(char* text, int textLength, int xPos, int yPos, BGR24 color, int blendStrength)
    {
        int _xPos = xPos;
        int _yPos = yPos;

        Rendering::Colors::RGB15 const fillColor
            = MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::transformBGR24ToScreenColor,
                DAT_TextureRenderCoreObject::ptr)(color);
        Rendering::Enums::RenderTarget const _drawBufferTempUnk
            = (Rendering::Enums::RenderTarget)DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue;

        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = DAT_TextManagerObject::instance.textSurfaceTarget;

        if (this->fontStartImageId_0x8 == -1) {
            this->fontStartImageId_0x8
                = GMTotalPicturesProcessed::instance[this->fontGmID_0x0] + this->numberOfFontStartInGm_0x4 - 1;
        }

        for (int i = 0; i < textLength; ++i) {
            byte const currentChar = text[i];

            int imageSeqId
                = DAT_TextInputDefinedData::instance
                      .CharToImageSeqIDMapping[DAT_TextManagerObject::instance.alternativeCodePageUsedUnk][currentChar];

            if (_xPos + this->whiteSpaceWidth_0x1c * 5 > DAT_TextManagerObject::instance.field2_0x8
                && _xPos < DAT_TextManagerObject::instance.field3_0xc) {

                if (imageSeqId == -1) {
                    if (currentChar >= ' ') {
                        if (DAT_TextManagerObject::instance.field6_0x18) {
                            int const lineY = this->baselineOffset_0x10 + _yPos + 2;
                            MACRO_CALL_MEMBER(
                                UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                                _xPos, lineY, _xPos + this->whiteSpaceWidth_0x1c, lineY, fillColor);
                        }
                        _xPos += this->whiteSpaceWidth_0x1c;
                    } else if (currentChar == '\n') {
                        _yPos += this->baselineOffset_0x10 / 3 + this->baselineOffset_0x10;
                        _xPos = xPos;
                    }

                } else {
                    imageSeqId += this->fontStartImageId_0x8;
                    MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderTextChar,
                        DAT_TextureRenderCoreObject::ptr)(_xPos, this->baselineOffset_0x10 + _yPos, imageSeqId,
                        (FontRenderType)this->renderType_0xc, this->lineHeight_0x14, fillColor, blendStrength);
                    _xPos += DAT_GMImageHeaders::instance.imh[imageSeqId].width + this->letterSpacing_0x18
                        + DAT_TextureRenderCoreObject::instance.mbr_0x6c;
                }
            } else if (imageSeqId == -1) {
                if (currentChar >= ' ') {
                    _xPos += this->whiteSpaceWidth_0x1c;
                } else if (currentChar == '\n') {
                    _yPos += this->baselineOffset_0x10 / 3 + this->baselineOffset_0x10;
                    _xPos = xPos;
                }
            } else {
                _xPos += DAT_GMImageHeaders::instance.imh[this->fontStartImageId_0x8 + imageSeqId].width
                    + this->letterSpacing_0x18;
            }
        }

        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = _drawBufferTempUnk;
        return _xPos;
    }

}
}
