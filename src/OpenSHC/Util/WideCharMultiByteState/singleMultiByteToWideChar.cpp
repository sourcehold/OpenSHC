#include "../WideCharMultiByteState.func.hpp"

namespace OpenSHC {
namespace Util {

    // FUNCTION: STRONGHOLDCRUSADER 0x0046B1B0
    WCHAR WideCharMultiByteState::singleMultiByteToWideChar(char character)
    {
        WCHAR buffer[10];
        MACRO_CALL_MEMBER(OpenSHC::Util::WideCharMultiByteState_Func::multiByteToWideCharWithSize, this)(
            buffer, &character, 1);
        return buffer[0];
    }

}
}
