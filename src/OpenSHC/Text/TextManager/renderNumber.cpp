#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Text {

    using OpenSHC::Text::TextAlignment;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00424620
    void TextManager::renderNumber(
        int number, int xPosition, int yPosition, uint color1, uint color2, int fontSize, BOOLEnum keepOffsetX)
    {
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, this)(
            number, xPosition, yPosition, OpenSHC::Text::TTA_LEFT, color1, color2, fontSize, keepOffsetX, 0);
    }

}
}
