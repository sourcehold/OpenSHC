#include "OpenSHC/Util/WideCharMultiByteState.func.hpp"

#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Util {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */

    // FUNCTION: STRONGHOLDCRUSADER 0x0046B110
    int WideCharMultiByteState::wideCharToMultiByteWithSize(
        LPSTR lpMultiByteStr, LPWSTR lpWideCharStr, int numOfSymbols)

    {
        int _numOfBytesWritten;

        _numOfBytesWritten = WideCharToMultiByte(DAT_TextManagerObject::instance.codePage, 0, lpWideCharStr,
            numOfSymbols, lpMultiByteStr, numOfSymbols, (CHAR*)0x0, (BOOL*)0x0);
        lpMultiByteStr[numOfSymbols] = '\0';
        return _numOfBytesWritten;
    }

}
}
