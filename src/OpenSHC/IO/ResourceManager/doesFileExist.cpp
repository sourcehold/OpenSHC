#include "../ResourceManager.func.hpp"

#include "OpenSHC/OS.func.hpp"

namespace OpenSHC {
namespace IO {

    // FUNCTION: STRONGHOLDCRUSADER 0x0046C420
    BOOLEnum ResourceManager::doesFileExist(char* filename)
    {
        int _fileHandle = MACRO_CALL(OS_Func::_ucrt_open)(filename, _O_BINARY, 0);
        if (_fileHandle == -1) {
            return FALSE;
        }
        MACRO_CALL(OS_Func::_ucrt_close)(_fileHandle);
        return TRUE;
    }

} // namespace IO
} // namespace OpenSHC
