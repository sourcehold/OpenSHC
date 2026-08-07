#include "../DecoderState.func.hpp"

#include "OpenSHC/IO/DecoderBuffer.func.hpp"
#include "OpenSHC/OS.func.hpp"

#include "pklib.h"

namespace OpenSHC {
namespace IO {

    // FUNCTION: STRONGHOLDCRUSADER 0x004724C0
    BOOLEnum DecoderState::doImplode(
        int* ptrHash, int* ptrSize, undefined* src, undefined* dst, unsigned int sizeUncompressed)
    {
        BOOLEnum _status = TRUE;
        HGLOBAL hMem = GlobalAlloc(GHND, sizeof(TCmpStruct));
        if (!hMem) {
            return FALSE;
        }
        TCmpStruct* _work_buf = (TCmpStruct*)GlobalLock(hMem);
        if (!_work_buf) {
            GlobalFree(hMem);
            return FALSE;
        }
        Helpers::BufferHelper _param;
        MACRO_CALL(OS_Func::_memset)(&_param, 0, sizeof(Helpers::BufferHelper));
        _param.buffer0.size = sizeUncompressed;
        _param.buffer1.size = sizeUncompressed;
        _param.buffer0.data = src;
        _param.imploding1orexploding2 = 1;
        _param.hash = 0xffffffff;
        _param.buffer1.data = dst;
        unsigned int const _pkware_status = implode(MACRO_CALL(DecoderBuffer_Func::ReadBufferAndComputeHash),
            MACRO_CALL(DecoderBuffer_Func::WriteBufferAndComputeHash), (char*)_work_buf, &_param, &this->implodingType,
            &this->implodingTypeSize);
        if (_pkware_status == CMP_NO_ERROR && _param.underflow == FALSE) {
            _param.hash = ~_param.hash;
            *ptrHash = _param.hash;
            *ptrSize = _param.compressedSize;
        } else {
            _status = CMP_NO_ERROR;
        }
        GlobalUnlock(hMem);
        GlobalFree(hMem);
        return _status;
    }

}
}
