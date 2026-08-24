#include "OpenSHC/Util/WideCharMultiByteState.func.hpp"

#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {
namespace Util {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */

    // FUNCTION: STRONGHOLDCRUSADER 0x0046B1B0
    void WideCharMultiByteState::multiByteToWideCharThunk2(char const param_1)

    {
        WCHAR local_18[10];
        uint local_4;

        local_4 = MSVC_SecurityCookie::instance ^ (uint)local_18;
        MACRO_CALL_MEMBER(OpenSHC::Util::WideCharMultiByteState_Func::multiByteToWideCharThunk, this)(
            local_18, &param_1, 1);
        ;
        return;
    }

}
}
