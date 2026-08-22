#include "../ResourceManager.func.hpp"

#include "OpenSHC/Global.func.hpp"
#include "OpenSHC/OS.func.hpp"

namespace OpenSHC {
namespace IO {

    // FUNCTION: STRONGHOLDCRUSADER 0x00471EB0
    int ResourceManager::getCurrentResourceSize()
    {
        char* _filename = MACRO_CALL_MEMBER(ResourceManager_Func::getFileNameOfCurrentActiveResource, this)();
        this->fileHandle = MACRO_CALL(OS_Func::_ucrt_open)(_filename, _O_BINARY, 0);
        if (this->fileHandle == -1) {
            return 0;
        }
        MACRO_CALL(OS_Func::_ucrt_lseek)(this->fileHandle, 0, FILE_END);
        int _fileSize = MACRO_CALL(OS_Func::_ucrt_tell)(this->fileHandle);
        MACRO_CALL(OS_Func::_ucrt_close)(this->fileHandle);
        return _fileSize;
    }

} // namespace IO
} // namespace OpenSHC
