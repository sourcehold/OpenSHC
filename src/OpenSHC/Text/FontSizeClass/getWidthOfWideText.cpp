#include "../FontSizeClass.func.hpp"

#include "OpenSHC/Util/WideCharMultiByteState.func.hpp"

#include "OpenSHC/Globals/DAT_WideCharMultiByteState.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00471610
    int FontSizeClass::getWidthOfWideText(LPWSTR wideText, int numberOfChars)
    {
        CHAR _charStringBuffer[3000];
        MACRO_CALL_MEMBER(Util::WideCharMultiByteState_Func::wideCharToMultiByteWithSize,
            DAT_WideCharMultiByteState::ptr)(_charStringBuffer, wideText, numberOfChars);
        return MACRO_CALL_MEMBER(FontSizeClass_Func::getWidthOfText, this)(_charStringBuffer, numberOfChars);
    }

}
}
