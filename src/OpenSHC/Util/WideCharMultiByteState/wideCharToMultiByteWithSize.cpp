#include "../WideCharMultiByteState.func.hpp"

#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Util {

    // FUNCTION: STRONGHOLDCRUSADER 0x0046B110
    int WideCharMultiByteState::wideCharToMultiByteWithSize(
        LPSTR lpMultiByteStr, LPWSTR lpWideCharStr, int numOfSymbols)
    {
        int const _numOfBytesWritten = WideCharToMultiByte(DAT_TextManagerObject::instance.codePage, NULL,
            lpWideCharStr, numOfSymbols, lpMultiByteStr, numOfSymbols, NULL, NULL);
        lpMultiByteStr[numOfSymbols] = '\0';
        return _numOfBytesWritten;
    }

}
}
