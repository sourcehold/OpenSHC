#include "../TextManager.func.hpp"

#include "OpenSHC/Text/FontSizeClass.func.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Text/FontRenderType.hpp"

#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Text {

    using OpenSHC::IO::Graphics::GmID;
    using OpenSHC::Text::FontRenderType;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00469E70
    void TextManager::setupFontSizeClassObjects()
    {
        MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::setupFontSizeClassObject,
            &DAT_TextManagerObject::instance.fontSizeClassArray[0xf])(
            OpenSHC::IO::Graphics::GID_FONT_STRONGHOLD_AA, 0, OpenSHC::Text::FRT_BLENDED_COLOR, 0x20, 46, 1, 5);
        MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::setupFontSizeClassObject,
            &DAT_TextManagerObject::instance.fontSizeClassArray[0x10])(OpenSHC::IO::Graphics::GID_FONT_STRONGHOLD_AA,
            this->sizeOfOneFontSet_0x3c, OpenSHC::Text::FRT_BLENDED_COLOR, 0x16, 0x20, 1, 5);
        MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::setupFontSizeClassObject,
            &DAT_TextManagerObject::instance.fontSizeClassArray[0x11])(OpenSHC::IO::Graphics::GID_FONT_STRONGHOLD_AA,
            this->sizeOfOneFontSet_0x3c * 2, OpenSHC::Text::FRT_BLENDED_COLOR, 0x12, 0x1b, 1, 4);
        MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::setupFontSizeClassObject,
            &DAT_TextManagerObject::instance.fontSizeClassArray[0x12])(OpenSHC::IO::Graphics::GID_FONT_STRONGHOLD_AA,
            this->sizeOfOneFontSet_0x3c * 3, OpenSHC::Text::FRT_BLENDED_COLOR, 0xd, 0x14, 1, 3);
        MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::setupFontSizeClassObject,
            &DAT_TextManagerObject::instance.fontSizeClassArray[0x13])(OpenSHC::IO::Graphics::GID_FONT_STRONGHOLD_AA,
            this->sizeOfOneFontSet_0x3c * 4, OpenSHC::Text::FRT_BLENDED_COLOR, 10, 0x10, 1, 3);
        return;
    }

}
}
