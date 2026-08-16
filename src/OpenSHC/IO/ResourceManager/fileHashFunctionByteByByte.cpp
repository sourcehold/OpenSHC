#include "../ResourceManager.func.hpp"

#include "OpenSHC/OS.func.hpp"

namespace OpenSHC {
namespace IO {

    // FUNCTION: STRONGHOLDCRUSADER 0x00472180
    int ResourceManager::fileHashFunctionByteByByte()
    {
        int _total = 0;

        char* _fileName = MACRO_CALL_MEMBER(ResourceManager_Func::getFileNameOfCurrentActiveResource, this)();
        int _fileHandle = MACRO_CALL(OS_Func::_ucrt_open)(_fileName, _O_BINARY, 0);
        if (_fileHandle == -1) {
            return -1;
        }

        char _first1024chars[1024];
        int _numReadUnk;
        do {
            _numReadUnk = MACRO_CALL(OS_Func::_ucrt_read)(_fileHandle, _first1024chars, sizeof(_first1024chars));

            for (int i = 0; i < _numReadUnk; ++i) {
                _total += _first1024chars[i];
            }
        } while (_numReadUnk != 0);
        MACRO_CALL(OS_Func::_ucrt_close)(_fileHandle);
        return _total;
    }

} // namespace IO
} // namespace OpenSHC
