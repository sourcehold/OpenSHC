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

    // FUNCTION: STRONGHOLDCRUSADER 0x00473640
    int FontSizeClass::renderCharUnk(byte charId, int xPos, int yPosUnk, int bgr24, int blendStrengthUnk)
    {
        int _xPos = xPos;
        int _yPos = yPosUnk;

        Rendering::Enums::RenderTarget renderTargetTemp
            = (Rendering::Enums::RenderTarget)DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue;

        Rendering::Colors::RGB15 const _fillColorUnk
            = MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::transformBGR24ToScreenColor,
                DAT_TextureRenderCoreObject::ptr)(bgr24);
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = DAT_TextManagerObject::instance.textSurfaceTarget;

        if (this->fontStartImageId_0x8 == -1) {
            this->fontStartImageId_0x8
                = GMTotalPicturesProcessed::instance[this->fontGmID_0x0] + this->numberOfFontStartInGm_0x4 - 1;
        }

        int imageSeqID
            = DAT_TextInputDefinedData::instance
                  .CharToImageSeqIDMapping[DAT_TextManagerObject::instance.alternativeCodePageUsedUnk][charId];

        if (_xPos + this->whiteSpaceWidth_0x1c * 5 > DAT_TextManagerObject::instance.field2_0x8
            && _xPos < DAT_TextManagerObject::instance.field3_0xc) {

            if (imageSeqID == -1) {
                if (charId >= ' ') {
                    if (DAT_TextManagerObject::instance.field6_0x18 != 0) {
                        MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                            _xPos, this->baselineOffset_0x10 + 2 + _yPos, this->whiteSpaceWidth_0x1c + _xPos,
                            this->baselineOffset_0x10 + 2 + _yPos, _fillColorUnk);
                    }
                    _xPos += this->whiteSpaceWidth_0x1c;
                }
            } else {
                imageSeqID += this->fontStartImageId_0x8;
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderTextChar,
                    DAT_TextureRenderCoreObject::ptr)(_xPos, _yPos + this->baselineOffset_0x10, imageSeqID,
                    (FontRenderType)this->renderType_0xc, this->lineHeight_0x14, _fillColorUnk, blendStrengthUnk);
                _xPos += DAT_GMImageHeaders::instance.imh[imageSeqID].width + this->letterSpacing_0x18
                    + DAT_TextureRenderCoreObject::instance.mbr_0x6c;
            }
        } else {
            if (imageSeqID == -1) {
                if (charId >= ' ') {
                    _xPos += this->whiteSpaceWidth_0x1c;
                }
            } else {
                imageSeqID += this->fontStartImageId_0x8;
                _xPos += DAT_GMImageHeaders::instance.imh[imageSeqID].width + this->letterSpacing_0x18;
            }
        }
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = renderTargetTemp;
        return _xPos;
    }

}
}
