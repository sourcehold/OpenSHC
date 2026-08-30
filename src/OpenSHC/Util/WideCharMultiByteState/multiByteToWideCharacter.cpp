#include "../WideCharMultiByteState.func.hpp"

#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Util {

    // FUNCTION: STRONGHOLDCRUSADER 0x0046B0D0
    int WideCharMultiByteState::multiByteToWideCharacter(LPWSTR lpWideCharStr, LPCSTR lpMultiByteStr)
    {
        int const numberOfBytes = strlen(lpMultiByteStr) + 1; // includes null terminator
        return MultiByteToWideChar(DAT_TextManagerObject::instance.codePage, MB_PRECOMPOSED, lpMultiByteStr,
            numberOfBytes, lpWideCharStr, numberOfBytes);
    }

}
}
