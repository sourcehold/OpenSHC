#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Text {

    using OpenSHC::Text::TextAlignment;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00424320
    void TextManager::renderInGameText(char* textAddress, int xParam, int yParam, TextAlignment alignment, uint color1,
        uint color2, int fontSize, BOOLEnum keepOffsetX)
    {
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, this)(
            textAddress, xParam, yParam, alignment, color1, color2, fontSize, keepOffsetX, 0);
    }

}
}
