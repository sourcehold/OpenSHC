#include "../WideCharMultiByteState.func.hpp"

#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Util {

    // FUNCTION: STRONGHOLDCRUSADER 0x0046B080
    int WideCharMultiByteState::wideCharToMultiByteComplete(LPSTR charOut, LPCWSTR wideCharIn)
    {
        int numberOfWideChars = wcslen(wideCharIn) + 1; // +1 for null terminator
        return WideCharToMultiByte(DAT_TextManagerObject::instance.codePage, NULL, wideCharIn, numberOfWideChars,
            charOut, numberOfWideChars, NULL, NULL);
    }

}
}
