#include "../TextManager.func.hpp"

#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Rendering/Colors/RGB15.hpp"
#include "OpenSHC/Text/FontRenderType.hpp"

#include "OpenSHC/Globals/DAT_GMImageHeaders.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/GMTotalPicturesProcessed.hpp"

namespace OpenSHC {
namespace Text {

    using OpenSHC::Text::FontRenderType;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0046A2C0
    int TextManager::renderPartOfNumberUnk(int numberToRenderUnk, int xPosUnk, int yPosUnk, int integerPartToRenderUnk,
        int bgr24, int digitSet, BOOL useCurrentXOffsetUnk)
    {
        int iVar2;
        int _decimalNumberToRender = 0;
        OpenSHC::Rendering::Colors::RGB15 fillColor
            = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::transformBGR24ToScreenColor,
                DAT_TextureRenderCoreObject::ptr)(bgr24);
        RenderTargetInt RVar1 = DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue;
        if (useCurrentXOffsetUnk == 0) {
            this->currentXOffset_0x0 = 0;
        }
        switch (integerPartToRenderUnk) {
        case 0:
            _decimalNumberToRender = numberToRenderUnk % 10;
            break;
        case 1:
            _decimalNumberToRender = numberToRenderUnk / 10;
            if (_decimalNumberToRender == 0) {
                return numberToRenderUnk * 0x66666667;
            }
            iVar2 = (int)((ulonglong)((longlong)_decimalNumberToRender * -0x66666667) >> 0x20);
            _decimalNumberToRender = _decimalNumberToRender + ((iVar2 >> 2) - (iVar2 >> 0x1f)) * 10;
            break;
        case 2:
            _decimalNumberToRender = numberToRenderUnk / 100;
            if (_decimalNumberToRender == 0) {
                return numberToRenderUnk * 0x51eb851f;
            }
            iVar2 = (int)((ulonglong)((longlong)_decimalNumberToRender * -0x66666667) >> 0x20);
            _decimalNumberToRender = _decimalNumberToRender + ((iVar2 >> 2) - (iVar2 >> 0x1f)) * 10;
            break;
        case 3:
            _decimalNumberToRender = numberToRenderUnk / 1000;
            if (_decimalNumberToRender == 0) {
                return numberToRenderUnk * 0x10624dd3;
            }
            iVar2 = (int)((ulonglong)((longlong)_decimalNumberToRender * -0x66666667) >> 0x20);
            _decimalNumberToRender = _decimalNumberToRender + ((iVar2 >> 2) - (iVar2 >> 0x1f)) * 10;
            break;
        case 4:
            _decimalNumberToRender = numberToRenderUnk / 10000;
            if (_decimalNumberToRender == 0) {
                return numberToRenderUnk * 0x68db8bad;
            }
            iVar2 = (int)((ulonglong)((longlong)_decimalNumberToRender * -0x66666667) >> 0x20);
            _decimalNumberToRender = _decimalNumberToRender + ((iVar2 >> 2) - (iVar2 >> 0x1f)) * 10;
            break;
        case 5:
            _decimalNumberToRender = numberToRenderUnk / 100000;
            if (_decimalNumberToRender == 0) {
                return numberToRenderUnk * 0x14f8b589;
            }
            iVar2 = (int)((ulonglong)((longlong)_decimalNumberToRender * -0x66666667) >> 0x20);
            _decimalNumberToRender = _decimalNumberToRender + ((iVar2 >> 2) - (iVar2 >> 0x1f)) * 10;
            break;
        case -1:
            this->currentXOffset_0x0 = this->currentXOffset_0x0 + -2;
            xPosUnk = xPosUnk + 2;
            _decimalNumberToRender = 10;
        }
        iVar2 = 0x11;
        if (digitSet == 1) {
            _decimalNumberToRender = _decimalNumberToRender + 0xb;
        } else {
            if (digitSet == 2) {
                _decimalNumberToRender = _decimalNumberToRender + 0x16;
                goto LAB_0046a45a;
            }
            if (digitSet != 3)
                goto LAB_0046a45a;
            _decimalNumberToRender = _decimalNumberToRender + 0x21;
        }
        iVar2 = 0xc;
    LAB_0046a45a:
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = this->textSurfaceTarget;
        int _imageId = _decimalNumberToRender + GMTotalPicturesProcessed::instance[0x92];
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderTextChar,
            DAT_TextureRenderCoreObject::ptr)(this->currentXOffset_0x0 + xPosUnk, iVar2 + yPosUnk, _imageId,
            OpenSHC::Text::FRT_BLENDED_COLOR, iVar2, (ushort)(fillColor), 0);
        int _widthOfRenderedNumber = DAT_GMImageHeaders::instance.imh[_imageId].width + -2;
        this->currentXOffset_0x0 = this->currentXOffset_0x0 + _widthOfRenderedNumber;
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = RVar1;
        return _widthOfRenderedNumber;
    }

}
}
