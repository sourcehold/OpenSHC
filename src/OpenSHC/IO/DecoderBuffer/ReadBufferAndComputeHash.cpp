#include "../DecoderBuffer.func.hpp"

#include "OpenSHC/OS.func.hpp"

#include "pklib.h"

namespace OpenSHC {
namespace IO {
    namespace DecoderBuffer {

        // FUNCTION: STRONGHOLDCRUSADER 0x0046D270
        unsigned int ReadBufferAndComputeHash(char* buf, unsigned int* size, void* param)
        {
            uint bytesToLoad = *size;
            BufferHelper* bufferHelper = (BufferHelper*)param;
            if (bufferHelper->underflow == 1) {
                return 0;
            }

            Helpers::Buffer* _buffer = &bufferHelper->buffer0;
            if (bufferHelper->imploding1orexploding2 != 1) {
                _buffer = &bufferHelper->buffer1;
            }

            unsigned int result;
            if (_buffer->offset < _buffer->size) {
                uint _count = _buffer->size - _buffer->offset;
                if (_count < bytesToLoad) {
                    bytesToLoad = _count;
                }
                MACRO_CALL(OS_Func::_memcpy)(buf, _buffer->data + _buffer->offset, bytesToLoad);
                _buffer->offset += bytesToLoad;
                result = bytesToLoad;
            } else {
                result = 0;
            }
            if (bufferHelper->imploding1orexploding2 == 1) {
                bufferHelper->hash = crc32_pklib(buf, &result, &bufferHelper->hash);
            }
            return result;
        }

    }
}
}
