#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Text {

    using OpenSHC::Rendering::Colors::BGR24;
    using OpenSHC::Text::TextAlignment;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00424360
    void TextManager::renderTextToScreen2(char* textAddress, int xParam, int yParam, TextAlignment alignment,
        BGR24 color, int fontSize, BOOLEnum keepOffsetX)
    {
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, this)(
            textAddress, xParam, yParam, alignment, color, fontSize, keepOffsetX, 0);
    }

}
}
