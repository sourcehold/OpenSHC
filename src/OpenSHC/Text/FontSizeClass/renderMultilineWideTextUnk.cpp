#include "../FontSizeClass.func.hpp"

#include "OpenSHC/Util/WideCharMultiByteState.func.hpp"

#include "OpenSHC/Globals/DAT_WideCharMultiByteState.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00473300
    int FontSizeClass::renderMultilineWideTextUnk(
        LPWSTR _wideText, int xPos, int yPos, int maxWidth, uint color, int blendStrength, int modeUnk)
    {
        CHAR _convertedText[3000];
        MACRO_CALL_MEMBER(OpenSHC::Util::WideCharMultiByteState_Func::wideCharToMultiByteWithSize,
            DAT_WideCharMultiByteState::ptr)(_convertedText, _wideText, wcslen(_wideText));
        return MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::renderMultilineTextUnk, this)(
            _convertedText, xPos, yPos, maxWidth, color, blendStrength, modeUnk);
    }

}
}
