#include "../FontSizeClass.func.hpp"

#include "OpenSHC/Util/WideCharMultiByteState.func.hpp"

#include "OpenSHC/Globals/DAT_WideCharMultiByteState.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00471670
    dword FontSizeClass::getWideCharWidth(WCHAR wChar)
    {
        return MACRO_CALL_MEMBER(FontSizeClass_Func::getCharWidthUnk, this)(MACRO_CALL_MEMBER(
            Util::WideCharMultiByteState_Func::wideCharToByteUnk, DAT_WideCharMultiByteState::ptr)(wChar));
    }

}
}
