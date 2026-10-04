#include "../FontSizeClass.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00469A30
    void FontSizeClass::setupFontSizeClassObject(GmID fontGmID, int numberOfFontStartInGm, FontRenderType renderType,
        int baselineOffset, int lineHeight, int letterSpacing, int whiteSpaceWidth)
    {
        this->fontGmID_0x0 = fontGmID;
        this->renderType_0xc = renderType;
        this->baselineOffset_0x10 = baselineOffset;
        this->lineHeight_0x14 = lineHeight;
        this->letterSpacing_0x18 = letterSpacing;
        this->whiteSpaceWidth_0x1c = whiteSpaceWidth;
        this->numberOfFontStartInGm_0x4 = numberOfFontStartInGm;
        this->fontStartImageId_0x8 = -1;
    }

}
}
