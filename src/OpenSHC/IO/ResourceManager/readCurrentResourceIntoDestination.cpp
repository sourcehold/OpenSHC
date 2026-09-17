#include "../ResourceManager.func.hpp"

#include "OpenSHC/OS.func.hpp"

namespace OpenSHC {
namespace IO {

    // FUNCTION: STRONGHOLDCRUSADER 0x00471E50
    BOOLEnum ResourceManager::readCurrentResourceIntoDestination(void* destination, size_t size)
    {
        char* _Filename = MACRO_CALL_MEMBER(ResourceManager_Func::getFileNameOfCurrentActiveResource, this)();
        this->fileHandle = MACRO_CALL(OS_Func::_ucrt_open)(_Filename, _O_BINARY, 0);
        if (this->fileHandle == -1) {
            return FALSE;
        }
        this->loadPositionInCurrentResource = MACRO_CALL(OS_Func::_ucrt_read)(this->fileHandle, destination, size);
        MACRO_CALL(OpenSHC::OS_Func::_ucrt_close)(this->fileHandle);
        return TRUE;
    }

} // namespace IO
} // namespace OpenSHC
