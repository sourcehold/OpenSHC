#include "../TextManager.func.hpp"

#include "OpenSHC/Text/FontSizeClass.func.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Text/FontRenderType.hpp"

#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00469E70
    void TextManager::setupFontSizeClassObjects()
    {
        MACRO_CALL_MEMBER(FontSizeClass_Func::setupFontSizeClassObject, &this->fontSizeClassArray[15])(
            IO::Graphics::GID_FONT_STRONGHOLD_AA, this->sizeOfOneFontSet_0x3c * 0, FRT_BLENDED_COLOR, 32, 46, 1, 5);
        MACRO_CALL_MEMBER(FontSizeClass_Func::setupFontSizeClassObject, &this->fontSizeClassArray[16])(
            IO::Graphics::GID_FONT_STRONGHOLD_AA, this->sizeOfOneFontSet_0x3c * 1, FRT_BLENDED_COLOR, 22, 32, 1, 5);
        MACRO_CALL_MEMBER(FontSizeClass_Func::setupFontSizeClassObject, &this->fontSizeClassArray[17])(
            IO::Graphics::GID_FONT_STRONGHOLD_AA, this->sizeOfOneFontSet_0x3c * 2, FRT_BLENDED_COLOR, 18, 27, 1, 4);
        MACRO_CALL_MEMBER(FontSizeClass_Func::setupFontSizeClassObject, &this->fontSizeClassArray[18])(
            IO::Graphics::GID_FONT_STRONGHOLD_AA, this->sizeOfOneFontSet_0x3c * 3, FRT_BLENDED_COLOR, 13, 20, 1, 3);
        MACRO_CALL_MEMBER(FontSizeClass_Func::setupFontSizeClassObject, &this->fontSizeClassArray[19])(
            IO::Graphics::GID_FONT_STRONGHOLD_AA, this->sizeOfOneFontSet_0x3c * 4, FRT_BLENDED_COLOR, 10, 16, 1, 3);
    }

}
}
