#include "../FontSizeClass.func.hpp"

#include "OpenSHC/Util/WideCharMultiByteState.func.hpp"

#include "OpenSHC/Globals/DAT_WideCharMultiByteState.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00473830
    int FontSizeClass::renderWideChar(WCHAR wideChar, int xPos, int yPos, int bgr24, int blendStrengthUnk)
    {
        return MACRO_CALL_MEMBER(FontSizeClass_Func::renderCharUnk, this)(
            MACRO_CALL_MEMBER(Util::WideCharMultiByteState_Func::wideCharToByteUnk, DAT_WideCharMultiByteState::ptr)(
                wideChar),
            xPos, yPos, bgr24, blendStrengthUnk);
    }

}
}
