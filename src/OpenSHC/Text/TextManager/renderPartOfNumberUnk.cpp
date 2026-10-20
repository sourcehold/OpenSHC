#include "../TextManager.func.hpp"

#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"

#include "OpenSHC/Globals/DAT_GMImageHeaders.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/GMTotalPicturesProcessed.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x0046A2C0
    void TextManager::renderPartOfNumberUnk(int numberToRenderUnk, int xPosUnk, int yPosUnk, int integerPartToRenderUnk,
        int bgr24, int digitSet, BOOL useCurrentXOffsetUnk)
    {
        int _decimalNumberToRenderAndImageOffset = 0;
        Rendering::Colors::RGB15 fillColor
            = MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::transformBGR24ToScreenColor,
                DAT_TextureRenderCoreObject::ptr)(bgr24);
        if (useCurrentXOffsetUnk == 0) {
            this->currentXOffset_0x0 = 0;
        }
        switch (integerPartToRenderUnk) {
        case 0:
            _decimalNumberToRenderAndImageOffset = numberToRenderUnk % 10;
            break;
        case 1:
            _decimalNumberToRenderAndImageOffset = numberToRenderUnk / 10;
            if (_decimalNumberToRenderAndImageOffset == 0) {
                return;
            }
            _decimalNumberToRenderAndImageOffset %= 10;
            break;
        case 2:
            _decimalNumberToRenderAndImageOffset = numberToRenderUnk / 100;
            if (_decimalNumberToRenderAndImageOffset == 0) {
                return;
            }
            _decimalNumberToRenderAndImageOffset %= 10;
            break;
        case 3:
            _decimalNumberToRenderAndImageOffset = numberToRenderUnk / 1000;
            if (_decimalNumberToRenderAndImageOffset == 0) {
                return;
            }
            _decimalNumberToRenderAndImageOffset %= 10;
            break;
        case 4:
            _decimalNumberToRenderAndImageOffset = numberToRenderUnk / 10000;
            if (_decimalNumberToRenderAndImageOffset == 0) {
                return;
            }
            _decimalNumberToRenderAndImageOffset %= 10;
            break;
        case 5:
            _decimalNumberToRenderAndImageOffset = numberToRenderUnk / 100000;
            if (_decimalNumberToRenderAndImageOffset == 0) {
                return;
            }
            _decimalNumberToRenderAndImageOffset %= 10;
            break;
        case -1:
            this->currentXOffset_0x0 -= 2;
            xPosUnk += 2;
            _decimalNumberToRenderAndImageOffset = 10;
        }

        int hightAdjust = 17;
        if (digitSet == 1) {
            _decimalNumberToRenderAndImageOffset += 11;
            hightAdjust = 12;
        } else if (digitSet == 2) {
            _decimalNumberToRenderAndImageOffset += 22;
        } else if (digitSet == 3) {
            _decimalNumberToRenderAndImageOffset += 33;
            hightAdjust = 12;
        }

        RenderTargetInt _tempRenderTargetHolder = DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue;
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = DAT_TextManagerObject::instance.textSurfaceTarget;
        int const _imageId = _decimalNumberToRenderAndImageOffset + GMTotalPicturesProcessed::instance[146];
        MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderTextChar, DAT_TextureRenderCoreObject::ptr)(
            this->currentXOffset_0x0 + xPosUnk, hightAdjust + yPosUnk, _imageId, FRT_BLENDED_COLOR, hightAdjust,
            fillColor, 0);
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = _tempRenderTargetHolder;
        this->currentXOffset_0x0 += DAT_GMImageHeaders::instance.imh[_imageId].width - 2;
    }

}
}
