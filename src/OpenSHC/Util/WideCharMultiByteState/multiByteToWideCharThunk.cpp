#include "OpenSHC/Util/WideCharMultiByteState.func.hpp"

#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Util {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */

    // FUNCTION: STRONGHOLDCRUSADER 0x0046B140
    void WideCharMultiByteState::multiByteToWideCharThunk(LPWSTR param_1, LPCSTR param_2, int param_3)

    {
        MultiByteToWideChar(DAT_TextManagerObject::instance.codePage, 1, param_2, param_3, param_1, param_3);
        param_1[param_3] = L'\0';
        return;
    }

}
}
