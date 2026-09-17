#include "../ResourceManager.func.hpp"

#include "OpenSHC/OS.func.hpp"

namespace OpenSHC {
namespace IO {

    // FUNCTION: STRONGHOLDCRUSADER 0x0046C4E0
    int ResourceManager::getSimpleFirst1024ByteSumOfFile(char* filename)
    {
        int _byteValueSumUnk = 0;

        int _fileHandle = MACRO_CALL(OS_Func::_ucrt_open)(filename, _O_BINARY, 0);
        if (_fileHandle == -1) {
            _byteValueSumUnk = -1;
        } else {
            char _buf[1024];

            int _lengthUnk;
            do {
                _lengthUnk = MACRO_CALL(OS_Func::_ucrt_read)(_fileHandle, _buf, sizeof(_buf));
                for (int _counter = 0; _counter < _lengthUnk; ++_counter) {
                    _byteValueSumUnk += _buf[_counter];
                }
            } while (_lengthUnk != 0);

            MACRO_CALL(OS_Func::_ucrt_close)(_fileHandle);
        }
        return _byteValueSumUnk;
    }

} // namespace IO
} // namespace OpenSHC
