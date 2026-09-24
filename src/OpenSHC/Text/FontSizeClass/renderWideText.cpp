#include "../FontSizeClass.func.hpp"

#include "OpenSHC/Util/WideCharMultiByteState.func.hpp"

#include "OpenSHC/Globals/DAT_WideCharMultiByteState.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x004737B0
    int FontSizeClass::renderWideText(
        LPWSTR wideText, int textLength, int xPos, int yPos, BGR24 color, int blendStrength)
    {
        CHAR _text[3000];
        MACRO_CALL_MEMBER(OpenSHC::Util::WideCharMultiByteState_Func::wideCharToMultiByteWithSize,
            DAT_WideCharMultiByteState::ptr)(_text, wideText, textLength);
        return MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::renderText, this)(
            _text, textLength, xPos, yPos, color, blendStrength);
    }

}
}
