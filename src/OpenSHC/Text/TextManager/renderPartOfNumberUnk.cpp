#include "../TextManager.func.hpp"

#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"

#include "OpenSHC/Globals/DAT_GMImageHeaders.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/GMFirstPictureIndex.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x0046A2C0
    void TextManager::renderPartOfNumberUnk(int numberToRenderUnk, int xPosUnk, int yPosUnk, int integerPartToRenderUnk,
        int bgr24, int digitSet, BOOL useCurrentXOffsetUnk)
    {
        int imageOffset = 0;
        Rendering::Colors::RGB15 const fillColor
            = MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::transformBGR24ToScreenColor,
                DAT_TextureRenderCoreObject::ptr)(bgr24);
        if (useCurrentXOffsetUnk == FALSE) {
            this->currentXOffset_0x0 = 0;
        }
        switch (integerPartToRenderUnk) {
        case 0:
            imageOffset = numberToRenderUnk % 10;
            break;
        case 1:
            imageOffset = numberToRenderUnk / 10;
            if (imageOffset == 0) {
                return;
            }
            imageOffset %= 10;
            break;
        case 2:
            imageOffset = numberToRenderUnk / 100;
            if (imageOffset == 0) {
                return;
            }
            imageOffset %= 10;
            break;
        case 3:
            imageOffset = numberToRenderUnk / 1000;
            if (imageOffset == 0) {
                return;
            }
            imageOffset %= 10;
            break;
        case 4:
            imageOffset = numberToRenderUnk / 10000;
            if (imageOffset == 0) {
                return;
            }
            imageOffset %= 10;
            break;
        case 5:
            imageOffset = numberToRenderUnk / 100000;
            if (imageOffset == 0) {
                return;
            }
            imageOffset %= 10;
            break;
        case -1:
            this->currentXOffset_0x0 -= 2;
            xPosUnk += 2;
            imageOffset = 10;
        }
        int glyphHeight = 17;
        if (digitSet == 1) {
            imageOffset += 11;
            glyphHeight = 12;
        } else if (digitSet == 2) {
            imageOffset += 22;
        } else if (digitSet == 3) {
            imageOffset += 33;
            glyphHeight = 12;
        }
        RenderTargetInt const previousDrawBuffer = DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue;
        // the original reads the text surface through the global instance, not through this
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = DAT_TextManagerObject::instance.textSurfaceTarget;
        int const imageID = imageOffset + GMFirstPictureIndex::instance[IO::Graphics::GID_FONT_SLANTED];
        MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderTextChar, DAT_TextureRenderCoreObject::ptr)(
            this->currentXOffset_0x0 + xPosUnk, glyphHeight + yPosUnk, imageID, FRT_BLENDED_COLOR, glyphHeight,
            fillColor, 0);
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = previousDrawBuffer;
        this->currentXOffset_0x0 += DAT_GMImageHeaders::instance.imh[imageID].width - 2;
    }

}
}
