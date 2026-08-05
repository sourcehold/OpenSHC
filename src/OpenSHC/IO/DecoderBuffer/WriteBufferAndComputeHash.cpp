#include "../DecoderBuffer.func.hpp"

#include "OpenSHC/OS.func.hpp"

#include "pklib.h"

namespace OpenSHC {
namespace IO {
    namespace DecoderBuffer {

        // FUNCTION: STRONGHOLDCRUSADER 0x0046D300
        void __cdecl WriteBufferAndComputeHash(char* buf, unsigned int* size, void* param)
        {
            uint bytesToWrite = *size;
            BufferHelper* bufferHelper = (BufferHelper*)param;
            if (bufferHelper->underflow == 1) {
                return;
            }
            Helpers::Buffer* _buffer;
            if (bufferHelper->imploding1orexploding2 == 1) {
                bufferHelper->compressedSize += bytesToWrite;
                _buffer = &bufferHelper->buffer1;
            } else {
                _buffer = &bufferHelper->buffer2;
            }

            if (_buffer->offset < _buffer->size) {
                if (_buffer->size - _buffer->offset < bytesToWrite) {
                    bufferHelper->underflow = 1;
                    return;
                }
                MACRO_CALL(OS_Func::_memcpy)(_buffer->data + _buffer->offset, buf, bytesToWrite);
                _buffer->offset += bytesToWrite;
            } else if (bytesToWrite > 0) {
                bufferHelper->underflow = 1;
                return;
            }

            if (bufferHelper->imploding1orexploding2 == 2) {
                bufferHelper->hash = crc32_pklib(buf, &bytesToWrite, &bufferHelper->hash);
            }
        }

    }
}
}
