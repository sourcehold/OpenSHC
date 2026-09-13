#include "../WideCharMultiByteState.func.hpp"

#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Util {

    // FUNCTION: STRONGHOLDCRUSADER 0x0046B140
    int WideCharMultiByteState::multiByteToWideCharWithSize(
        LPWSTR lpWideCharStr, LPCSTR lpMultiByteStr, int numberOfSymbols)
    {
        int numberOfCharsWritten = MultiByteToWideChar(DAT_TextManagerObject::instance.codePage, MB_PRECOMPOSED,
            lpMultiByteStr, numberOfSymbols, lpWideCharStr, numberOfSymbols);
        lpWideCharStr[numberOfSymbols] = L'\0';
        return numberOfCharsWritten;
    }

}
}
