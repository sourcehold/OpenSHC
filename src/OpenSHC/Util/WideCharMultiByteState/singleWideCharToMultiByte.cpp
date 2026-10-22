#include "../WideCharMultiByteState.func.hpp"

namespace OpenSHC {
namespace Util {

    // FUNCTION: STRONGHOLDCRUSADER 0x0046B170
    char WideCharMultiByteState::singleWideCharToMultiByte(WCHAR wideChar)
    {
        char _byteBuffer[12];
        MACRO_CALL_MEMBER(OpenSHC::Util::WideCharMultiByteState_Func::wideCharToMultiByteWithSize, this)(
            _byteBuffer, &wideChar, 1);
        return _byteBuffer[0];
    }

}
}
