#include "../ResourceManager.func.hpp"

#include "OpenSHC/OS.func.hpp"

namespace OpenSHC {
namespace IO {

    // FUNCTION: STRONGHOLDCRUSADER 0x00471DC0
    BOOLEnum ResourceManager::doesFileOfActiveResourceExist()
    {
        char* _Filename = MACRO_CALL_MEMBER(ResourceManager_Func::getFileNameOfCurrentActiveResource, this)();
        int fileDescriptor = MACRO_CALL(OpenSHC::OS_Func::_ucrt_open)(_Filename, _O_BINARY, 0);
        if (fileDescriptor == -1) {
            return FALSE;
        }
        MACRO_CALL(OpenSHC::OS_Func::_ucrt_close)(fileDescriptor);
        return TRUE;
    }

} // namespace IO
} // namespace OpenSHC
